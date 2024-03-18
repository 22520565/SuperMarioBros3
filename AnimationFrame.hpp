#pragma once
#include "Sprite.hpp"
#include "Time.hpp"

namespace game {
    /*
        Sprite animation
    */
    struct AnimationFrame {
      public:        
          const Texture* texture = nullptr;
          Rect2f textureRect = Rect2f();
          Time time = Time::Zero;
     //   explicit constexpr AnimationFrame(const LPSPRITE sprite, const DWORD time) noexcept
     //       : sprite(sprite), time(time) {}

        [[nodiscard]]
        constexpr const Time &getTime() const noexcept { return this->time; }

      //  [[nodiscard]]
      //  constexpr const LPSPRITE &getSprite() const noexcept { return this->sprite; }


        explicit AnimationFrame(const Texture& texture, const Rect2f& textureRect, const Time time);
      private:
      //  LPSPRITE sprite = nullptr;
     //   DWORD time = DWORD();


    };

    typedef AnimationFrame *LPANIMATION_FRAME;
}
