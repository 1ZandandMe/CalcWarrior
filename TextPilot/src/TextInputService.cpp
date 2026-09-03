#include "TextInputService.h"
#include "ClipboardManager.h"
#include "SimpleLogger.h"
#include "../include/httplib.h"
#include "../include/json.hpp"
#include <iostream>
#include <thread>

// ============================================================
// 构造 & 析构
// ============================================================

TextInputService::TextInputService(const Config& config)
    : m_config(config)
    , m_history(config.historySize)
{
    m_keyboard.setCharDelay(m_config.charDelayMs);
}

TextInputService::~TextInputService() {
    stop();
}

// ============================================================
// start / stop
// ============================================================

bool TextInputService::start() {
    try {
        m_server = std::make_unique<httplib::Server>();

        // 所有路由注册
        m_server->Post("/api/input", [this](const httplib::Request& req, httplib::Response& res) {
            handleInput(req, res);
        });
        m_server->Get("/api/ping", [this](const httplib::Request& req, httplib::Response& res) {
            handlePing(req, res);
        });
        m_server->Options("/api/input", [](const httplib::Request&, httplib::Response& res) {
            res.status = 204;
        });
        m_server->Get("/api/history", [this](const httplib::Request& req, httplib::Response& res) {
            handleGetHistory(req, res);
        });
        m_server->Get("/api/clipboard", [this](const httplib::Request& req, httplib::Response& res) {
            handleGetClipboard(req, res);
        });
        m_server->Post("/api/clipboard", [this](const httplib::Request& req, httplib::Response& res) {
            handlePostClipboard(req, res);
        });

        m_startTime = std::chrono::steady_clock::now();
        int port = m_config.port;

        std::thread([this, port]() {
            m_running.store(true);
            Logger::instance().info("HTTP server started on 0.0.0.0:{}", port);
            if (!m_server->listen("0.0.0.0", port)) {
                Logger::instance().error("Failed to bind port {}", port);
                m_running.store(false);
            }
        }).detach();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return m_running.load();

    } catch (const std::exception& e) {
        Logger::instance().error("Start failed: {}", e.what());
        return false;
    }
}

void TextInputService::stop() {
    if (m_running.load()) {
        m_running.store(false);
        if (m_server) m_server->stop();
        Logger::instance().info("Server stopped");
    }
}

// ============================================================
// 辅助
// ============================================================

static void setJson(httplib::Response& res, int status, const std::string& body) {
    res.status = status;
    res.set_content(body, "application/json; charset=utf-8");
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

static std::string errJson(const char* msg) {
    return R"({"status":"error","error":")" + std::string(msg) + "\"}";
}

// ============================================================
// POST /api/input
// ============================================================

void TextInputService::handleInput(const httplib::Request& req, httplib::Response& res) {
    try {
        auto j = nlohmann::json::parse(req.body);

        if (!j.contains("text") || !j["text"].is_string()) {
            setJson(res, 400, errJson("missing 'text' field"));
            return;
        }
        std::string text = j["text"].get<std::string>();
        bool autoEnter = j.value("autoEnter", false);
        std::string mode = j.value("mode", "char");

        if (mode == "clipboard") {
            if (!setClipboardText(text)) {
                setJson(res, 500, errJson("clipboard write failed"));
                return;
            }
            Sleep(80);
            m_keyboard.pasteFromClipboard();
            if (autoEnter) {
                m_keyboard.pressEnter();
            }
        } else {
            int len = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), (int)text.size(), nullptr, 0);
            std::wstring wtext(len, L'\0');
            MultiByteToWideChar(CP_UTF8, 0, text.c_str(), (int)text.size(), &wtext[0], len);

            bool ok = m_keyboard.typeText(wtext);
            if (ok && autoEnter) {
                m_keyboard.pressEnter();
            }

            if (!ok) {
                setJson(res, 500, errJson("SendInput failed"));
                return;
            }
        }

        m_history.push(text, autoEnter);

        std::cout << "\n┌─ #" << m_history.size() << " ─────────────────────\n"
                  << "│ " << text << "\n"
                  << "└─ chars=" << text.size()
                  << (autoEnter ? " +Enter" : "")
                  << ", from=" << req.remote_addr
                  << std::endl;

        Logger::instance().info("{}: {} chars{} from {}",
            m_history.size(), text.size(), autoEnter ? " +Enter" : "", req.remote_addr);

        nlohmann::json resp;
        resp["status"] = "ok";
        resp["chars"] = text.size();
        if (autoEnter) resp["autoEnter"] = true;
        setJson(res, 200, resp.dump());

    } catch (const nlohmann::json::parse_error& e) {
        Logger::instance().warn("JSON parse error from {}: {}", req.remote_addr, e.what());
        setJson(res, 400, errJson("invalid JSON"));
    } catch (const std::exception& e) {
        Logger::instance().error("Internal error: {}", e.what());
        setJson(res, 500, errJson(e.what()));
    }
}

// ============================================================
// GET /api/ping
// ============================================================

void TextInputService::handlePing(const httplib::Request&, httplib::Response& res) {
    auto now = std::chrono::steady_clock::now();
    auto uptime = std::chrono::duration_cast<std::chrono::seconds>(now - m_startTime).count();

    nlohmann::json j;
    j["status"] = "alive";
    j["version"] = "3.0.0";
    j["uptime"] = uptime;
    j["historyCount"] = (int)m_history.size();
    setJson(res, 200, j.dump());
}

// ============================================================
// GET /api/history?count=N
// ============================================================

void TextInputService::handleGetHistory(const httplib::Request& req, httplib::Response& res) {
    int count = 50;
    if (req.has_param("count")) {
        try {
            count = std::stoi(req.get_param_value("count"));
            if (count < 1) count = 1;
            if (count > (int)m_history.size()) count = (int)m_history.size();
        } catch (...) {}
    }

    auto entries = m_history.getRecent((size_t)count);

    nlohmann::json j;
    j["history"] = nlohmann::json::array();
    for (const auto& e : entries) {
        nlohmann::json item;
        item["id"] = e.id;
        item["time"] = e.timestamp;
        item["text"] = e.text;
        if (e.autoEnter) item["autoEnter"] = true;
        j["history"].push_back(item);
    }

    setJson(res, 200, j.dump());
}

// ============================================================
// GET /api/clipboard  (修复：真正读取剪贴板)
// ============================================================

void TextInputService::handleGetClipboard(const httplib::Request&, httplib::Response& res) {
    std::string text;
    if (getClipboardText(text)) {
        nlohmann::json j;
        j["status"] = "ok";
        j["text"] = text;
        j["length"] = (int)text.size();
        setJson(res, 200, j.dump());
        Logger::instance().info("Clipboard read: {} chars", text.size());
    } else {
        setJson(res, 500, errJson("Failed to open or read clipboard"));
        Logger::instance().warn("Clipboard read failed (maybe empty or locked)");
    }
}

// ============================================================
// POST /api/clipboard  (修复：真正写入剪贴板)
// ============================================================

void TextInputService::handlePostClipboard(const httplib::Request& req, httplib::Response& res) {
    try {
        auto j = nlohmann::json::parse(req.body);
        std::string text = j.value("text", "");
        
        if (text.empty()) {
            setJson(res, 400, errJson("'text' field is empty or missing"));
            return;
        }

        if (setClipboardText(text)) {
            nlohmann::json resp;
            resp["status"] = "ok";
            resp["chars"] = (int)text.size();
            setJson(res, 200, resp.dump());
            Logger::instance().info("Clipboard write: {} chars from {}", text.size(), req.remote_addr);
        } else {
            setJson(res, 500, errJson("Clipboard write failed (OpenClipboard/Empty failed)"));
        }
    } catch (const nlohmann::json::parse_error& e) {
        setJson(res, 400, errJson("invalid JSON"));
    } catch (const std::exception& e) {
        setJson(res, 500, errJson(e.what()));
    }
}