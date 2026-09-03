#pragma once
#include <string>
#include <windows.h>

class KeyboardSimulator {
public:
    KeyboardSimulator() = default;

    /// 将文本逐字输入到当前焦点窗口
    bool typeText(const std::wstring& text);

    /// Ctrl+V 粘贴剪贴板内容
    void pasteFromClipboard();

    /// 单独按一次回车键
    void pressEnter();

    /// 设置字符间延迟（毫秒）
    void setCharDelay(DWORD ms) { m_charDelay = ms; }

private:
    DWORD m_charDelay{5};

    bool sendUnicodeChar(wchar_t ch);
};
