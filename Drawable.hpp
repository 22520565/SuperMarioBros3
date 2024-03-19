#pragma once

namespace game {
    class RenderTarget;

    class Drawable {
      public:
        virtual ~Drawable() noexcept = default;

      protected:
        constexpr Drawable() noexcept = default;
        friend class RenderTarget;
        virtual bool draw(const RenderTarget &target) const = 0;
    };
}