#include "HistoryBuffer.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

std::string HistoryBuffer::nowStr() {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S");
    return oss.str();
}

void HistoryBuffer::push(const std::string& text, bool autoEnter) {
    std::lock_guard<std::mutex> lock(m_mutex);

    HistoryEntry entry;
    entry.id = m_nextId++;
    entry.timestamp = nowStr();
    entry.text = text;
    entry.autoEnter = autoEnter;

    m_entries[m_head] = entry;
    m_head = (m_head + 1) % m_capacity;
    if (m_size < m_capacity) m_size++;

    // 完整终端打印（不截断）
    std::cout << "[" << entry.timestamp << "] #" << entry.id
              << " | " << text << std::endl;
}

std::vector<HistoryEntry> HistoryBuffer::getRecent(size_t count) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (count > m_size) count = m_size;

    std::vector<HistoryEntry> result;
    result.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        size_t idx = (m_head + m_capacity - i - 1) % m_capacity;
        result.push_back(m_entries[idx]);
    }

    return result;
}
