#pragma once
#include "tchar.hpp"
#include "Vector2.hpp"
#include "WindowBase.hpp"
#include <minwindef.h>
#include <winnt.h>

namespace game {
    class Window : public WindowBase {
      public:
       explicit Window(const Vector2<int> &size, const tchar *const title, const tchar *const className,
               const tchar *const iconPath, const HINSTANCE hInstance, const int nCmdShow) noexcept;
    };
}

#include "Window.inl"
