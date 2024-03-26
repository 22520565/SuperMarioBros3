#pragma once
#include "RenderTarget.hpp"
#include "Window.hpp"

namespace game {
    class RenderWindow final : public Window, public RenderTarget {
      private:
      public:
         explicit RenderWindow(const WindowSettings& windowSettings) noexcept;

        Vector2<int> getSize() const noexcept override;
    };
}

#include "RenderWindow.inl"
