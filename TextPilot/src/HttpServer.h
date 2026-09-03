#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <thread>
#include <atomic>
#include <winsock2.h>
#include <ws2tcpip.h>

struct HttpRequest {
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

struct HttpResponse {
    int statusCode{200};
    std::string statusText{"OK"};
    std::string contentType{"application/json"};
    std::string body;
};

class HttpServer {
public:
    using RequestHandler = std::function<HttpResponse(const HttpRequest&)>;

    explicit HttpServer(int port);
    ~HttpServer();

    HttpServer(const HttpServer&) = delete;
    HttpServer& operator=(const HttpServer&) = delete;

    bool start();
    void stop();
    bool isRunning() const { return m_running.load(); }
    int port() const { return m_port; }

    void setHandler(const std::string& method, const std::string& path, RequestHandler handler);

private:
    SOCKET m_listenSocket{INVALID_SOCKET};
    int m_port;
    std::unordered_map<std::string, RequestHandler> m_getHandlers;
    std::unordered_map<std::string, RequestHandler> m_postHandlers;
    std::atomic<bool> m_running{false};
    std::thread m_acceptThread;

    void acceptLoop();
    void handleClient(SOCKET clientSocket);
    HttpRequest parseRequest(const std::string& raw) const;
    std::string buildResponse(const HttpResponse& resp) const;
};
