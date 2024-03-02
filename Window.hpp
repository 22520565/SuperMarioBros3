#pragma once
#include "DxResource.hpp"
#include "Vector2.hpp"
#include "WindowBase.hpp"

namespace game {
    class Window : public WindowBase, public DxResource {
    public:
        Window(const Vector2<int>& size, const TCHAR *const title, int nCmdShow) 
            : WindowBase(size, title, nCmdShow), DxResource() {
            RECT rect = RECT();
            GetClientRect(hWnd, &rect);

            backBufferSize = Vector2<uint_fast32_t>(rect.right + 1, rect.bottom + 1);

            DebugOut(L"[INFO] Window's client area: width= %d, height= %d\n", rect.right - 1, rect.bottom - 1);

             }
    };
}
