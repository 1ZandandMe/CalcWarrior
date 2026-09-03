#include "HttpServer.h"
#include <sstream>
#include <iostream>
#include <vector>

HttpServer::HttpServer(int port) : m_port(port) {}

HttpServer::~HttpServer() {
    stop();
}

void HttpServer::setHandler(const std::string& method, const std::string& path, RequestHandler handler) {
    if (method == "GET") {
        m_getHandlers[path] = std::move(handler);
    } else if (method == "POST") {
        m_postHandlers[path] = std::move(handler);
    }
}

bool HttpServer::start() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "[TextPilot] WSAStartup failed." << std::endl;
        return false;
    }

    m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_listenSocket == INVALID_SOCKET) {
        std::cerr << "[TextPilot] socket() failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    int opt = 1;
    setsockopt(m_listenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;  // 绑定所有网络接口
    addr.sin_port = htons(m_port);

    if (bind(m_listenSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "[TextPilot] bind() failed on port " << m_port
                  << ": " << WSAGetLastError() << std::endl;
        closesocket(m_listenSocket);
        WSACleanup();
        return false;
    }

    if (listen(m_listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "[TextPilot] listen() failed: " << WSAGetLastError() << std::endl;
        closesocket(m_listenSocket);
        WSACleanup();
        return false;
    }

    m_running.store(true);
    m_acceptThread = std::thread(&HttpServer::acceptLoop, this);

    std::cout << "[TextPilot] HTTP server listening on port " << m_port << std::endl;
    return true;
}

void HttpServer::stop() {
    m_running.store(false);
    if (m_listenSocket != INVALID_SOCKET) {
        closesocket(m_listenSocket);
        m_listenSocket = INVALID_SOCKET;
    }
    if (m_acceptThread.joinable()) {
        m_acceptThread.join();
    }
    WSACleanup();
}

void HttpServer::acceptLoop() {
    while (m_running.load()) {
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(m_listenSocket, &readSet);

        timeval timeout{1, 0};  // 1秒超时，用于检查 m_running
        int result = select(0, &readSet, nullptr, nullptr, &timeout);
        if (result == SOCKET_ERROR) {
            break;
        }
        if (result == 0) continue;

        SOCKET client = accept(m_listenSocket, nullptr, nullptr);
        if (client == INVALID_SOCKET) continue;

        handleClient(client);
    }
}

void HttpServer::handleClient(SOCKET clientSocket) {
    const size_t bufSize = 8192;
    std::vector<char> buf(bufSize);
    std::string rawRequest;

    // 读取请求头（直到 \r\n\r\n）
    bool headerDone = false;
    int contentLength = 0;
    std::string headers;

    while (m_running.load()) {
        int bytes = recv(clientSocket, buf.data(), bufSize - 1, 0);
        if (bytes <= 0) break;

        buf[bytes] = '\0';
        rawRequest.append(buf.data(), bytes);

        if (!headerDone) {
            auto pos = rawRequest.find("\r\n\r\n");
            if (pos != std::string::npos) {
                headerDone = true;
                headers = rawRequest.substr(0, pos);

                // 解析 Content-Length
                auto clPos = headers.find("Content-Length:");
                if (clPos != std::string::npos) {
                    auto end = headers.find("\r\n", clPos);
                    auto val = headers.substr(clPos + 15, end - clPos - 15);
                    while (!val.empty() && val.front() == ' ') val.erase(0, 1);
                    contentLength = std::stoi(val);
                }

                // 如果 body 已经收够，跳出
                size_t bodyStart = pos + 4;
                size_t receivedBody = rawRequest.size() - bodyStart;
                if (receivedBody >= (size_t)contentLength) {
                    break;
                }
            }
        } else {
            size_t bodyStart = rawRequest.find("\r\n\r\n") + 4;
            size_t receivedBody = rawRequest.size() - bodyStart;
            if (receivedBody >= (size_t)contentLength) {
                break;
            }
        }
    }

    HttpRequest req = parseRequest(rawRequest);
    HttpResponse resp;
    resp.contentType = "application/json; charset=utf-8";

    // 路由分发
    RequestHandler* matchedHandler = nullptr;
    if (req.method == "GET") {
        auto it = m_getHandlers.find(req.path);
        if (it != m_getHandlers.end()) matchedHandler = &it->second;
    } else if (req.method == "POST") {
        auto it = m_postHandlers.find(req.path);
        if (it != m_postHandlers.end()) matchedHandler = &it->second;
    }

    if (matchedHandler) {
        resp = (*matchedHandler)(req);
    } else {
        resp.statusCode = 404;
        resp.statusText = "Not Found";
        resp.body = R"({"error":"not found"})";
    }

    std::string responseStr = buildResponse(resp);
    send(clientSocket, responseStr.data(), responseStr.size(), 0);
    closesocket(clientSocket);
}

HttpRequest HttpServer::parseRequest(const std::string& raw) const {
    HttpRequest req;
    std::istringstream stream(raw);
    std::string line;

    // 请求行: METHOD /path HTTP/1.1
    if (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        auto p1 = line.find(' ');
        auto p2 = line.rfind(' ');
        if (p1 != std::string::npos && p2 != std::string::npos && p2 > p1) {
            req.method = line.substr(0, p1);
            req.path = line.substr(p1 + 1, p2 - p1 - 1);
        }
    }

    // 请求头
    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) break;
        auto colon = line.find(':');
        if (colon != std::string::npos) {
            std::string key = line.substr(0, colon);
            std::string val = line.substr(colon + 1);
            if (!val.empty() && val.front() == ' ') val.erase(0, 1);
            req.headers[key] = val;
        }
    }

    // Body
    auto bodyPos = raw.find("\r\n\r\n");
    if (bodyPos != std::string::npos) {
        req.body = raw.substr(bodyPos + 4);
    }

    return req;
}

std::string HttpServer::buildResponse(const HttpResponse& resp) const {
    std::ostringstream oss;
    oss << "HTTP/1.1 " << resp.statusCode << " " << resp.statusText << "\r\n"
        << "Content-Type: " << resp.contentType << "\r\n"
        << "Content-Length: " << resp.body.size() << "\r\n"
        << "Connection: close\r\n"
        << "Access-Control-Allow-Origin: *\r\n"
        << "Access-Control-Allow-Methods: GET, POST\r\n"
        << "Access-Control-Allow-Headers: Content-Type\r\n"
        << "\r\n"
        << resp.body;
    return oss.str();
}
