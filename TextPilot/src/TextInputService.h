#pragma once
#include <memory>
#include <chrono>
#include <atomic>
#include "KeyboardSimulator.h"
#include "HistoryBuffer.h"
#include "config.h"

namespace httplib {
    class Server;
    struct Request;
    struct Response;
}

class TextInputService {
public:
    explicit TextInputService(const Config& config);
    ~TextInputService();

    TextInputService(const TextInputService&) = delete;
    TextInputService& operator=(const TextInputService&) = delete;

    bool start();
    void stop();
    bool isRunning() const { return m_running.load(); }

private:
    // 路由处理器
    void handleInput(const httplib::Request& req, httplib::Response& res);
    void handlePing(const httplib::Request& req, httplib::Response& res);
    void handleGetHistory(const httplib::Request& req, httplib::Response& res);
    void handleGetClipboard(const httplib::Request& req, httplib::Response& res);
    void handlePostClipboard(const httplib::Request& req, httplib::Response& res);

    Config m_config;
    KeyboardSimulator m_keyboard;
    HistoryBuffer m_history;
    std::unique_ptr<httplib::Server> m_server;
    std::chrono::steady_clock::time_point m_startTime;
    std::atomic<bool> m_running{false};
};
