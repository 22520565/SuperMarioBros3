#include "WindowBase.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    inline WindowBase::WindowBase(const Vector2<int> &size, const TCHAR *const title, const TCHAR *const iconPath,
                                  const TCHAR *const className, const HINSTANCE hInstance, const int nCmdShow) noexcept {
        std::ignore = this->create(size, title, iconPath, className, hInstance, nCmdShow);
    }

    ////////////////////////////////////////////////////////////
    inline WindowBase::~WindowBase() noexcept {
        if ((!this->isOpen()) || this->close()) [[likely]] {
            std::ignore = UnregisterClass(this->className, this->hInstance);
        }
    }

    ////////////////////////////////////////////////////////////
    inline LRESULT CALLBACK WindowBase::winProc(const HWND hWnd, const UINT message,
                                                const WPARAM wParam, const LPARAM lParam) noexcept {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    ////////////////////////////////////////////////////////////
    inline bool WindowBase::close() const noexcept { return ::DestroyWindow(hWnd); }

    ////////////////////////////////////////////////////////////
    inline bool WindowBase::isOpen() const noexcept { return ::IsWindow(this->hWnd); }

    ////////////////////////////////////////////////////////////
    inline const MSG *WindowBase::pollMsg() noexcept {
        const MSG *result = nullptr;
        if (PeekMessage(&(this->msg), hWnd, 0U, 0U, PM_REMOVE) != 0) [[likely]] {
            std::ignore = ::TranslateMessage(&(this->msg));
            std::ignore = ::DispatchMessage(&(this->msg));
            result = &(this->msg);
        }
        return result;
    }

    ////////////////////////////////////////////////////////////
    inline Vector2<int> WindowBase::getSize() const noexcept {
        RECT rect = RECT();
        std::ignore = ::GetClientRect(hWnd, &rect);
        return Vector2<int>(rect.right, rect.bottom);
    }
}
