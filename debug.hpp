#pragma once
// TODO: "cstdio" and "ctime" shall not be included!
#include <csignal>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>

namespace game {
#define _W(x) __W(x)
#define __W(x) L##x

#define VA_PRINTS(s)               \
    {                              \
        va_list argp;              \
        va_start(argp, fmt);       \
        vswprintf_s(s, fmt, argp); \
        va_end(argp);              \
    }

    void DebugOut(const wchar_t* fmt, ...);
    void DebugOutTitle(const wchar_t* fmt, ...);
    void SetDebugWindow(HWND hwnd);
}
