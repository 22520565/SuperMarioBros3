#pragma once
#include "Rect3.hpp"

namespace game {
    class Collidable {
      public:
        constexpr virtual ~Collidable() = default;

        constexpr virtual Rect3f getGlobalBounds() const noexcept = 0;

        [[nodiscard]]
        constexpr bool isCollided(const Collidable &collidable) const noexcept;
    };
}

#include "Collidable.inl"
