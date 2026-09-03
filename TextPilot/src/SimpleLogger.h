#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

/// 简易控制台日志（enum class 避免 Windows.h 宏冲突）
class Logger {
public:
    enum class Level { Debug, Info, Warn, Error };

    static Logger& instance() {
        static Logger logger;
        return logger;
    }

    void setLevel(Level level) { m_level = level; }

    template<typename... Args>
    void info(const char* fmt, Args&&... args)  { log(Level::Info,  fmt, std::forward<Args>(args)...); }
    template<typename... Args>
    void warn(const char* fmt, Args&&... args)  { log(Level::Warn,  fmt, std::forward<Args>(args)...); }
    template<typename... Args>
    void error(const char* fmt, Args&&... args) { log(Level::Error, fmt, std::forward<Args>(args)...); }
    template<typename... Args>
    void debug(const char* fmt, Args&&... args) { log(Level::Debug, fmt, std::forward<Args>(args)...); }

private:
    Level m_level = Level::Info;

    Logger() = default;

    static const char* levelStr(Level lv) {
        switch (lv) {
            case Level::Debug: return "DEBUG";
            case Level::Info:  return "INFO";
            case Level::Warn:  return "WARN";
            case Level::Error: return "ERROR";
        }
        return "???";
    }

    static std::string timestamp() {
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        std::tm tm;
        localtime_s(&tm, &t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S")
            << '.' << std::setw(3) << std::setfill('0') << ms.count();
        return oss.str();
    }

    template<typename... Args>
    void log(Level lv, const char* fmt, Args&&... args) {
        if (lv < m_level) return;
        std::cout << "[" << timestamp() << "] [" << levelStr(lv) << "] ";
        format(std::cout, fmt, std::forward<Args>(args)...);
        std::cout << std::endl;
    }

    static void format(std::ostream& os, const char* fmt) { os << fmt; }

    template<typename T, typename... Rest>
    static void format(std::ostream& os, const char* fmt, T&& val, Rest&&... rest) {
        while (*fmt) {
            if (*fmt == '{' && *(fmt + 1) == '}') {
                os << val;
                return format(os, fmt + 2, std::forward<Rest>(rest)...);
            }
            os << *fmt++;
        }
    }
};
