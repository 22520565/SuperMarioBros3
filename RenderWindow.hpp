#pragma once
#include "RenderTarget.hpp"
#include "Window.hpp"

namespace game {
    class RenderWindow final : public Window, public RenderTarget {
      private:
      public:
         explicit RenderWindow(const Vector2<int>& size, const tchar* const title, const tchar* const className,
              const tchar* const iconPath, const HINSTANCE hInstance, const int nCmdShow) noexcept;

        Vector2<int> getSize() const noexcept override;
    };
}

#include "RenderWindow.inl"
