#include "debug.hpp"
#include "Vector2.hpp"
#include "Window.hpp"
#include "WindowSettings.hpp"
#include <tuple>
#include <windef.h>
#include <WinUser.h>

namespace game {
    ////////////////////////////////////////////////////////////
    bool Window::create(const WindowSettings& newSettings) noexcept {
        bool windowCreated = false;

        if ((!this->isOpen()) || this->close()) [[likely]] {
            std::ignore = UnregisterClass(this->settings.className.data(), this->settings.hInstance);
            if (const WNDCLASSEX wc = WNDCLASSEX{
                    .cbSize = sizeof(WNDCLASSEX),
                    .style = CS_HREDRAW | CS_VREDRAW,
                    .lpfnWndProc = winProc,
                    .cbClsExtra = 0,
                    .cbWndExtra = 0,
                    .hInstance = newSettings.hInstance,
                    .hIcon = static_cast<HICON>(
                        LoadImage(newSettings.hInstance, newSettings.iconPath.data(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE)),
                    .hCursor = LoadCursor(nullptr, IDC_ARROW),
                    .hbrBackground = nullptr,
                    .lpszMenuName = nullptr,
                    .lpszClassName = newSettings.className.data(),
                    .hIconSm = nullptr,
                };
                RegisterClassEx(&wc) != 0) [[likely]] {
                if (RECT windowRect = RECT{
                        .left = 0,
                        .top = 0,
                        .right = newSettings.size.x,
                        .bottom = newSettings.size.y,
                    };
                    ::AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, false, 0) != 0) [[likely]] {
                    this->hWnd = CreateWindow(
                        newSettings.className.data(), newSettings.title.data(), WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
                        nullptr, nullptr, wc.hInstance, nullptr);
                    if (this->hWnd != nullptr) [[likely]] {
                        std::ignore = ::ShowWindow(this->hWnd, newSettings.nCmdShow);
                        if (::UpdateWindow(hWnd) != 0) [[likely]] {
                            this->settings = newSettings;
                            DebugOut(L"[INFO] Window's client area: width= %d, height= %d\n", newSettings.size.x, newSettings.size.y);
                            windowCreated = true;
                        } else [[unlikely]] {
                            std::ignore = this->close();
                        }
                    }
                }
            }
        }

        return windowCreated;
    }
}
