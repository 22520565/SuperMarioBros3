#include "WindowBase.hpp"
#include "Vector2.hpp"
#include <tuple>

namespace game {
    ////////////////////////////////////////////////////////////
    bool WindowBase::create(const Vector2<int> &size, const tchar *const title, const tchar *const iconPath,
                            const tchar *const className, const HINSTANCE hInstance, const int nCmdShow) noexcept {
        bool windowCreated = false;

        if ((!this->isOpen()) || this->close()) [[likely]] {
            std::ignore = UnregisterClass(this->className, this->hInstance);
            if (const WNDCLASSEX wc = WNDCLASSEX{
                    .cbSize = sizeof(WNDCLASSEX),
                    .style = CS_HREDRAW | CS_VREDRAW,
                    .lpfnWndProc = winProc,
                    .cbClsExtra = 0,
                    .cbWndExtra = 0,
                    .hInstance = hInstance,
                    .hIcon = static_cast<HICON>(
                        LoadImage(hInstance, iconPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE)),
                    .hCursor = LoadCursor(nullptr, IDC_ARROW),
                    .hbrBackground = nullptr,
                    .lpszMenuName = nullptr,
                    .lpszClassName = className,
                    .hIconSm = nullptr,
                };
                RegisterClassEx(&wc) != 0) [[likely]] {
                if (RECT windowRect = RECT{
                        .left = 0,
                        .top = 0,
                        .right = size.x,
                        .bottom = size.y,
                    };
                    ::AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, false, 0) != 0) [[likely]] {
                    this->hWnd = CreateWindow(
                        className, title, WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
                        nullptr, nullptr, wc.hInstance, nullptr);
                    if (this->hWnd != nullptr) [[likely]] {
                        std::ignore = ::ShowWindow(hWnd, nCmdShow);
                        if (::UpdateWindow(hWnd) != 0) [[likely]] {
                            this->className = className;
                            this->hInstance = hInstance;
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
