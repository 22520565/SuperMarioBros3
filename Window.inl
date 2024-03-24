#include "Window.hpp"
#include "debug.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
   inline Window::Window(const Vector2<int> &size, const tchar *const title, const tchar *const className,
                   const tchar *const iconPath, const HINSTANCE hInstance, const int nCmdShow) noexcept
        : WindowBase(size, title, className, iconPath, hInstance, nCmdShow) {
        const auto windowSize = this->getSize();
        DebugOut(L"[INFO] Window's client area: width= %d, height= %d\n", windowSize.x, windowSize.y);
    }
}
