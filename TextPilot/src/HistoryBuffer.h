#pragma once
#include <string>
#include <mutex>
#include <vector>
#include <cstdint>

struct HistoryEntry {
    int32_t id;
    std::string timestamp;
    std::string text;
    bool autoEnter;
};

/// 线程安全的环形缓冲区
class HistoryBuffer {
public:
    explicit HistoryBuffer(size_t capacity = 500)
        : m_capacity(capacity), m_entries(capacity) {}

    void push(const std::string& text, bool autoEnter);
    std::vector<HistoryEntry> getRecent(size_t count) const;
    size_t size() const { return m_size; }

private:
    size_t m_capacity;
    size_t m_size = 0;
    size_t m_head = 0;
    int32_t m_nextId = 1;
    std::vector<HistoryEntry> m_entries;
    mutable std::mutex m_mutex;

    static std::string nowStr();
};
