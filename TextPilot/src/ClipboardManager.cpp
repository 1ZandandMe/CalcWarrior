#include "ClipboardManager.h"
#include <windows.h>

bool setClipboardText(const std::string& text) {
    if (!OpenClipboard(nullptr)) return false;
    if (!EmptyClipboard()) {
        CloseClipboard();
        return false;
    }

    int len = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, nullptr, 0);
    if (len == 0) {
        CloseClipboard();
        return false;
    }

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(wchar_t));
    if (!hMem) {
        CloseClipboard();
        return false;
    }

    wchar_t* pMem = (wchar_t*)GlobalLock(hMem);
    MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, pMem, len);
    GlobalUnlock(hMem);

    SetClipboardData(CF_UNICODETEXT, hMem);
    CloseClipboard();
    return true;
}

bool getClipboardText(std::string& text) {
    if (!OpenClipboard(nullptr)) return false;

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (!hData) {
        CloseClipboard();
        return false;
    }

    wchar_t* pData = (wchar_t*)GlobalLock(hData);
    if (!pData) {
        CloseClipboard();
        return false;
    }

    int len = WideCharToMultiByte(CP_UTF8, 0, pData, -1, nullptr, 0, nullptr, nullptr);
    bool success = false;
    if (len > 0) {
        text.resize(len - 1);
        WideCharToMultiByte(CP_UTF8, 0, pData, -1, &text[0], len, nullptr, nullptr);
        success = true;
    }

    GlobalUnlock(hData);
    CloseClipboard();
    return success;
}