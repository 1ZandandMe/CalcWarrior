#include <iostream>
#include <csignal>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "TextInputService.h"
#include "config.h"
#include "SimpleLogger.h"

static TextInputService* g_service = nullptr;

void signalHandler(int) {
    std::cout << "\n[TextPilot] Shutting down..." << std::endl;
    if (g_service) g_service->stop();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Config cfg = loadConfig("config.json");
    Logger::instance().setLevel(Logger::Level::Info);

    std::cout << "╔══════════════════════════════════════════╗" << std::endl;
    std::cout << "║     TextPilot v3.0 — 局域网文本投送       ║" << std::endl;
    std::cout << "║  手机打字 → PC 键盘输入 + 剪贴板互通     ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;

    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    std::cout << "  本机名称: " << hostname << std::endl;
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo* result = nullptr;
    if (getaddrinfo(hostname, nullptr, &hints, &result) == 0) {
        auto addrinfoPtr = std::unique_ptr<addrinfo, decltype(&freeaddrinfo)>(
            result, freeaddrinfo);
        for (auto* p = result; p; p = p->ai_next) {
            auto* sin = (sockaddr_in*)p->ai_addr;
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &sin->sin_addr, ip, sizeof(ip));
            if (strcmp(ip, "127.0.0.1") != 0) {
                std::cout << "  局域网 IP: " << ip << std::endl;
            }
        }
    }

    std::cout << "  监听端口: " << cfg.port << std::endl;
    std::cout << "  历史记录: " << cfg.historySize << " 条" << std::endl;
    std::cout << std::endl;
    std::cout << "  API:" << std::endl;
    std::cout << "    POST /api/input          发送文本" << std::endl;
    std::cout << "    GET  /api/ping            心跳检测" << std::endl;
    std::cout << "    GET  /api/history?count=N 历史记录" << std::endl;
    std::cout << "    GET  /api/clipboard       拉取PC剪贴板" << std::endl;
    std::cout << "    POST /api/clipboard       推送到PC剪贴板" << std::endl;
    std::cout << std::endl;
    std::cout << "  按 Ctrl+C 停止服务" << std::endl;
    std::cout << "────────────────────────────────────────────" << std::endl;

    TextInputService service(cfg);
    g_service = &service;

    signal(SIGINT, signalHandler);

    if (!service.start()) {
        Logger::instance().error("Failed to start server.");
        return 1;
    }

    while (service.isRunning()) {
        Sleep(100);
    }

    std::cout << "[TextPilot] Goodbye." << std::endl;
    return 0;
}
