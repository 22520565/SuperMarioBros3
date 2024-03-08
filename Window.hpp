#pragma once
#include "DxResource.hpp"
#include "Vector2.hpp"
#include "WindowBase.hpp"

namespace game {
    class Window : public WindowBase, public DxResource {
    public:
        constexpr Window() = default;

        Window(const Vector2<int>& size, const TCHAR *const title, int nCmdShow,
            HINSTANCE hInstance, const TCHAR* const className)
            : WindowBase(size, title, nCmdShow,hInstance, className), DxResource() {
            auto windowSize = this->getSize();

            backBufferSize = Vector2<uint_fast32_t>(windowSize.x, windowSize.y);

            DebugOut(L"[INFO] Window's client area: width= %d, height= %d\n", windowSize.x, windowSize.y);

             }
    };
}
