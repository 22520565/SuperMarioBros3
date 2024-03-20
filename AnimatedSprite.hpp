#pragma once
#include "AnimationFrame.hpp"
#include "Clock.hpp"
#include "Sprite.hpp"
#include <vector>

namespace game {
    class AnimatedSprite : public Sprite {
      public:
        std::vector<AnimationFrame> animationFrames = std::vector<AnimationFrame>();

        explicit AnimatedSprite(const Texture& texture) noexcept(
            noexcept(AnimatedSprite(texture, std::vector<AnimationFrame>())));

        AnimatedSprite(const Texture& texture, const std::vector<AnimationFrame>& animationFrames) noexcept(
            noexcept(Sprite(texture)));

        void update(const Time deltaTime) noexcept;

       constexpr void restart() noexcept;

      private:
        size_t currentFrame = 0UL;
        game::Time timeElaspedFrame = Time::zero;
    };
}

#include "AnimatedSprite.inl"
