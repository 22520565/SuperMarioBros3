#pragma once
#include "Clock.hpp"
#include "Sprite.hpp"
#include "Time.hpp"
#include <vector>

namespace game {
    class AnimatedSprite : public Sprite {
      public:
        std::vector<Rect2uf32> textureRects = std::vector<Rect2uf32>();
        Time textureRectTime = Time::zero;

        explicit AnimatedSprite(const Texture &texture) noexcept(
            noexcept(AnimatedSprite(texture, Time::zero)));

        explicit AnimatedSprite(const Texture &texture, const Time textureRectTime) noexcept(
            noexcept(AnimatedSprite(texture, textureRectTime, std::vector<Rect2uf32>())));

        explicit AnimatedSprite(const Texture &texture, const Time textureRectTime, const std::vector<Rect2uf32> &textureRects) noexcept(
            noexcept(Sprite(texture)));

        void update(const Time deltaTime) noexcept;

        constexpr void restart() noexcept;

      private:
        std::vector<Rect2uf32>::const_iterator itCurrentTextureRect = textureRects.cbegin();
        Time timeElaspedCurrentTextureRect = Time::zero;
        // size_t currentFrame = 0UL;
        // game::Time timeElaspedFrame = Time::zero;
    };
}

#include "AnimatedSprite.inl"
