#include "Vector2.hpp"
#include "Window.hpp"
#include "WindowSettings.hpp"
#include <minwindef.h>
#include <tuple>
#include <windef.h>
#include <WinUser.h>

namespace game {
    ////////////////////////////////////////////////////////////
    inline Window::Window(const WindowSettings& newSettings) noexcept {
        std::ignore = this->create(newSettings);
    }

    ////////////////////////////////////////////////////////////
    inline Window::~Window() noexcept {
        if ((!this->isOpen()) || this->close()) [[likely]] {
            std::ignore = UnregisterClass(this->settings.className.data(), this->settings.hInstance);
        }
    }

    ////////////////////////////////////////////////////////////
    inline LRESULT CALLBACK Window::winProc(const HWND hWnd, const UINT message,
                                                const WPARAM wParam, const LPARAM lParam) noexcept {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    ////////////////////////////////////////////////////////////
    inline bool Window::close() const noexcept { return ::DestroyWindow(hWnd); }

    ////////////////////////////////////////////////////////////
    inline bool Window::isOpen() const noexcept { return ::IsWindow(this->hWnd); }

    ////////////////////////////////////////////////////////////
    inline const MSG *Window::pollMsg() noexcept {
        const MSG *result = nullptr;
        if (PeekMessage(&(this->msg), hWnd, 0U, 0U, PM_REMOVE) != 0) [[likely]] {
            std::ignore = ::TranslateMessage(&(this->msg));
            std::ignore = ::DispatchMessage(&(this->msg));
            result = &(this->msg);
        }
        return result;
    }

    ////////////////////////////////////////////////////////////
    constexpr const Vector2<int>& Window::getSize() const noexcept {
        return this->settings.size;
    }
}
