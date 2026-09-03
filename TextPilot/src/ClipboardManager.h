#pragma once
#include <string>

/// 将 UTF-8 文本写入 Windows 剪贴板
bool setClipboardText(const std::string& text);

/// 从 Windows 剪贴板读取 UTF-8 文本
bool getClipboardText(std::string& text);