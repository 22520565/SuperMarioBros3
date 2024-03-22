#pragma once
#include "Vector2.hpp"
#include "WindowBase.hpp"
#include <minwindef.h>
#include <winnt.h>

namespace game {
    class Window : public WindowBase {
      public:
       explicit Window(const Vector2<int> &size, const TCHAR *const title, const TCHAR *const className,
               const TCHAR *const iconPath, const HINSTANCE hInstance, const int nCmdShow) noexcept;
    };
}

#include "Window.inl"
