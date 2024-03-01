#pragma once
#include "DxResource.hpp"
#include "Vector2.hpp"
#include "WindowBase.hpp"

namespace game {
    class Window : public WindowBase, public DxResource {
    public:
        Window(const Vector2<int>& size, int nCmdShow) 
            : WindowBase(size, nCmdShow), DxResource(this->hWnd) {}

    };
}
