#include "Animation.hpp"
#include "AnimationFrame.hpp"
#include "Rect2.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Time.hpp"
#include <vector>

namespace game {
    ////////////////////////////////////////////////////////////
    inline Animation::Animation(const Texture &texture) noexcept(
        noexcept(Animation(texture, std::vector<AnimationFrame>())))
        : Animation(texture, std::vector<AnimationFrame>()) {}

    inline Animation::Animation(const Texture &texture, const std::vector<AnimationFrame> &animationFrames) noexcept(
        noexcept(Sprite(texture))) : Sprite(texture), animationFrames(animationFrames) {}

    ////////////////////////////////////////////////////////////
    inline void Animation::update(const Time deltaTime) noexcept {
        if (this->animationFrames.empty() ||
            (this->currentFrame > (this->animationFrames.size() - 1UL))) [[unlikely]] {
            this->restart();
        } else if (this->timeElaspedFrame += deltaTime;
                   this->timeElaspedFrame >= this->animationFrames[this->currentFrame].frameTime) [[unlikely]] {
            if (++(this->currentFrame);
                this->currentFrame >= this->animationFrames.size()) [[unlikely]] {
                this->currentFrame = 0UL;
            }
            this->timeElaspedFrame = Time::zero;
            this->setTextureRect(this->animationFrames[this->currentFrame].textureRect);
        } else [[likely]] {
            // Frame stays remain!
        }
    }

    ////////////////////////////////////////////////////////////
    constexpr void Animation::restart() noexcept {
        this->currentFrame = 0UL;
        this->timeElaspedFrame = Time::zero;
        if (!this->animationFrames.empty()) [[likely]] {
            this->setTextureRect((*this->animationFrames.cbegin()).textureRect);
        } else [[unlikely]] {
            this->setTextureRect(Rect2uf32());
        }
    }
}
