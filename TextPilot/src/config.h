#pragma once
#include <string>

struct Config {
    int port = 9527;
    int charDelayMs = 5;
    int historySize = 500;
};

Config loadConfig(const std::string& path);
