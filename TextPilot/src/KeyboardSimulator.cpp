#include "KeyboardSimulator.h"
#include <iostream>

bool KeyboardSimulator::sendUnicodeChar(wchar_t ch) {
    INPUT input[2] = {};

    // KEYDOWN
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wScan = ch;
    input[0].ki.dwFlags = KEYEVENTF_UNICODE;

    // KEYUP
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wScan = ch;
    input[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;

    if (SendInput(2, input, sizeof(INPUT)) != 2) {
        return false;
    }

    if (m_charDelay > 0) {
        Sleep(m_charDelay);
    }

    return true;
}

void KeyboardSimulator::pasteFromClipboard() {
    INPUT ip[4] = {};

    // Ctrl 按下
    ip[0].type = INPUT_KEYBOARD;
    ip[0].ki.wVk = VK_CONTROL;

    // V 按下
    ip[1].type = INPUT_KEYBOARD;
    ip[1].ki.wVk = 'V';

    // V 抬起
    ip[2].type = INPUT_KEYBOARD;
    ip[2].ki.wVk = 'V';
    ip[2].ki.dwFlags = KEYEVENTF_KEYUP;

    // Ctrl 抬起
    ip[3].type = INPUT_KEYBOARD;
    ip[3].ki.wVk = VK_CONTROL;
    ip[3].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(4, ip, sizeof(INPUT));
}

void KeyboardSimulator::pressEnter() {
    INPUT ip[2] = {};
    ip[0].type = INPUT_KEYBOARD;
    ip[0].ki.wVk = VK_RETURN;
    ip[1].type = INPUT_KEYBOARD;
    ip[1].ki.wVk = VK_RETURN;
    ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, ip, sizeof(INPUT));
}

bool KeyboardSimulator::typeText(const std::wstring& text) {
    if (text.empty()) return true;

    // 确保当前窗口有焦点
    // 我们不做 SetForegroundWindow，由用户自己点击目标窗口

    for (wchar_t ch : text) {
        // 处理特殊字符
        switch (ch) {
        case L'\n':
            // Enter 键
            {
                INPUT ip[2] = {};
                ip[0].type = INPUT_KEYBOARD;
                ip[0].ki.wVk = VK_RETURN;
                ip[1].type = INPUT_KEYBOARD;
                ip[1].ki.wVk = VK_RETURN;
                ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(2, ip, sizeof(INPUT));
            }
            break;
        case L'\r':
            // 忽略回车符（会被 \n 处理）
            break;
        default:
            if (!sendUnicodeChar(ch)) {
                std::cerr << "[TextPilot] SendInput failed for char: " << (int)ch << std::endl;
                return false;
            }
            break;
        }
    }

    return true;
}
