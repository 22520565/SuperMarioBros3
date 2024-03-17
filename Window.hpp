#pragma once
#include "DxResource.hpp"
#include "Vector2.hpp"
#include "WindowBase.hpp"

namespace game {
    class Window : public WindowBase{
    public:
        constexpr Window() = default;

        Window(const Vector2<int>& size, const TCHAR *const title, int nCmdShow,
            HINSTANCE hInstance, const TCHAR* const className)
            : WindowBase(size, title, nCmdShow,hInstance, className) {
            auto windowSize = this->getSize();
            DebugOut(L"[INFO] Window's client area: width= %d, height= %d\n", windowSize.x, windowSize.y);
             }
    };
}
