#include "config.h"
#include "../include/json.hpp"
#include <fstream>
#include <iostream>
#include <windows.h>

static std::string getExeDir() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string path(buffer);
    size_t pos = path.find_last_of("\\/");
    return (pos != std::string::npos) ? path.substr(0, pos) : ".";
}

Config loadConfig(const std::string& path) {
    Config cfg;
    std::string fullPath = path;
    if (fullPath.find(":\\") == std::string::npos && fullPath.front() != '/') {
        fullPath = getExeDir() + "\\" + path;
    }

    std::ifstream file(fullPath);
    if (!file.is_open()) {
        nlohmann::json defaults;
        defaults["port"] = cfg.port;
        defaults["charDelayMs"] = cfg.charDelayMs;
        defaults["historySize"] = cfg.historySize;
        std::ofstream out(fullPath);
        out << defaults.dump(4) << std::endl;
        std::cout << "[Config] Created default at " << fullPath << std::endl;
        return cfg;
    }

    try {
        auto j = nlohmann::json::parse(file);
        cfg.port = j.value("port", cfg.port);
        cfg.charDelayMs = j.value("charDelayMs", cfg.charDelayMs);
        cfg.historySize = j.value("historySize", cfg.historySize);
        std::cout << "[Config] Loaded " << fullPath
                  << " (port=" << cfg.port
                  << ", delay=" << cfg.charDelayMs << "ms"
                  << ", history=" << cfg.historySize << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Config] Parse error: " << e.what() << ", using defaults" << std::endl;
    }

    return cfg;
}