#pragma once
#include "Sprite.hpp"
#include "Time.hpp"

namespace game {
    struct AnimationFrame {
      public:
        Rect2uf32 textureRect = Rect2uf32();
        Time frameTime = Time::zero;

        constexpr explicit AnimationFrame(const Rect2uf32 &textureRect, const Time frameTime) noexcept;
    };
}

#include "AnimationFrame.inl"
