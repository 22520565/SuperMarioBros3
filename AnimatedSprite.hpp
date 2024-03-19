#pragma once
#include "AnimationFrame.hpp"
#include "Clock.hpp"
#include "Sprite.hpp"
#include <vector>

namespace game {
    class AnimatedSprite : public Sprite {
      public:
        std::vector<AnimationFrame> animationFrames = std::vector<AnimationFrame>();

        explicit AnimatedSprite(const Texture &texture) : Sprite(texture) {}

        AnimatedSprite(const Texture &texture, const std::vector<AnimationFrame> &animationFrames)
            : Sprite(texture), animationFrames(animationFrames) {
            if (!animationFrames.empty()) [[likely]] {
                this->setTextureRect(animationFrames[0].textureRect);
            }
        }

        void update(const Time deltaTime) {
            if (this->animationFrames.empty()) [[unlikely]] {
                this->restart();
            } else [[likely]] {
                if (this->currentFrame > (this->animationFrames.size() - 1UL)) {
                    this->restart();
                } else if (this->timeElaspedFrame += deltaTime;
                           this->timeElaspedFrame >= this->animationFrames[this->currentFrame].frameTime) [[unlikely]] {
                    ++(this->currentFrame);
                    this->currentFrame %= this->animationFrames.size();
                    this->timeElaspedFrame = Time::zero;
                    this->setTextureRect(this->animationFrames[this->currentFrame].textureRect);
                } else [[likely]] {
                    // Frame stays remain!
                }
            }
        }

        void restart() {
            this->currentFrame = 0UL;
            this->timeElaspedFrame = Time::zero;
            if (!animationFrames.empty()) [[likely]] {
                this->setTextureRect(animationFrames[0].textureRect);
            }
        }

      private:
        size_t currentFrame = 0UL;
        game::Time timeElaspedFrame = Time::zero;
    };
}
