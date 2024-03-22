#include "Window.hpp"
#include "debug.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
   inline Window::Window(const Vector2<int> &size, const TCHAR *const title, const TCHAR *const className,
                   const TCHAR *const iconPath, const HINSTANCE hInstance, const int nCmdShow) noexcept
        : WindowBase(size, title, className, iconPath, hInstance, nCmdShow) {
        const auto windowSize = this->getSize();
        DebugOut(L"[INFO] Window's client area: width= %d, height= %d\n", windowSize.x, windowSize.y);
    }
}
