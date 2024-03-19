#pragma once
#include "Sprite.hpp"
#include "Time.hpp"

namespace game {
    /*
        Sprite animation
    */
    struct AnimationFrame {
      public:
        Rect2f textureRect = Rect2f();
        Time frameTime = Time::zero;

        constexpr explicit AnimationFrame(const Rect2f &textureRect, const Time frameTime);
    };

    typedef AnimationFrame *LPANIMATION_FRAME;
}

#include "AnimationFrame.inl"
