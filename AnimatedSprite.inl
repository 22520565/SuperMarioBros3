#include "AnimatedSprite.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    inline AnimatedSprite::AnimatedSprite(const Texture &texture) noexcept(
        noexcept(AnimatedSprite(texture, std::vector<AnimationFrame>())))
        : AnimatedSprite(texture, std::vector<AnimationFrame>()) {}

    ////////////////////////////////////////////////////////////
    inline AnimatedSprite::AnimatedSprite(const Texture &texture, const std::vector<AnimationFrame> &animationFrames) noexcept(
        noexcept(Sprite(texture)))
        : Sprite(texture), animationFrames(animationFrames) {
        if (!animationFrames.empty()) [[likely]] {
            this->setTextureRect(animationFrames[0UL].textureRect);
        }
    }

    ////////////////////////////////////////////////////////////
    inline void AnimatedSprite::update(const Time deltaTime) noexcept {
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

    ////////////////////////////////////////////////////////////
    constexpr void AnimatedSprite::restart() noexcept {
        this->currentFrame = 0UL;
        this->timeElaspedFrame = Time::zero;
        if (!animationFrames.empty()) [[likely]] {
            this->setTextureRect(animationFrames[0UL].textureRect);
        }
    }
}
