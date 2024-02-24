#pragma once

#include "Sprite.hpp"

namespace game {
    /*
        Sprite animation
    */
    class AnimationFrame {
      public:
        explicit constexpr AnimationFrame(const LPSPRITE sprite, const DWORD time) noexcept
            : sprite(sprite), time(time) {}

        [[nodiscard("Use the value of this method or remove the redundant statement!")]]
        constexpr const DWORD &getTime() const noexcept { return this->time; }

        [[nodiscard("Use the value of this method or remove the redundant statement!")]]
        constexpr const LPSPRITE &getSprite() const noexcept { return this->sprite; }

      private:
        LPSPRITE sprite = nullptr;
        DWORD time = DWORD();
    };

    typedef AnimationFrame *LPANIMATION_FRAME;
}
