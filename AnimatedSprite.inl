#include "AnimatedSprite.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    inline AnimatedSprite::AnimatedSprite(const Texture &texture) noexcept(
        noexcept(AnimatedSprite(texture, Time::zero)))
        : AnimatedSprite(texture, Time::zero) {}

    ////////////////////////////////////////////////////////////
    inline AnimatedSprite::AnimatedSprite(const Texture &texture, const Time textureRectTime) noexcept(
        noexcept(AnimatedSprite(texture, textureRectTime, std::vector<Rect2uf32>())))
        : AnimatedSprite(texture, textureRectTime, std::vector<Rect2uf32>()) {}

    ////////////////////////////////////////////////////////////
    inline AnimatedSprite::AnimatedSprite(const Texture &texture, const Time textureRectTime,
                                          const std::vector<Rect2uf32> &textureRects) noexcept(noexcept(Sprite(texture)))
        : Sprite(texture), textureRectTime(textureRectTime), textureRects(textureRects) {
        if (!textureRects.empty()) [[likely]] {
            this->setTextureRect(*textureRects.begin());
        }
    }

    ////////////////////////////////////////////////////////////
    inline void AnimatedSprite::update(const Time deltaTime) noexcept {
        // if (this->textureRects.empty()) [[unlikely]] {
        //     this->restart();
        // } else [[likely]] {
        //     if (this->currentFrame > (this->textureRects.size() - 1UL)) {
        //         this->restart();
        //     } else if (this->timeElaspedFrame += deltaTime;
        //                this->timeElaspedFrame >= this->textureRectTime) [[unlikely]] {
        //         ++(this->currentFrame);
        //         this->currentFrame %= this->textureRects.size();
        //         this->timeElaspedFrame = Time::zero;
        //         this->setTextureRect(this->textureRects[this->currentFrame]);
        //     } else [[likely]] {
        //         // Frame stays remain!
        //     }
        // }

        if (this->textureRects.empty() || (this->itCurrentTextureRect._Ptr == nullptr) ||
            (this->itCurrentTextureRect >= this->textureRects.cend()) ||
            (this->itCurrentTextureRect < this->textureRects.cbegin())) [[unlikely]] {
            this->restart();
        } else if (this->timeElaspedCurrentTextureRect += deltaTime;
                   this->timeElaspedCurrentTextureRect >= this->textureRectTime) [[unlikely]] {
            if (++(this->itCurrentTextureRect);
                this->itCurrentTextureRect >= this->textureRects.cend()) [[unlikely]] {
                this->itCurrentTextureRect = this->textureRects.cbegin();
            }
            this->timeElaspedCurrentTextureRect = Time::zero;
            this->setTextureRect(*this->itCurrentTextureRect);
        } else [[likely]] {
            // Frame stays remain!
        }
    }

    ////////////////////////////////////////////////////////////
    constexpr void AnimatedSprite::restart() noexcept {
        // this->currentFrame = 0UL;
        // this->timeElaspedFrame = Time::zero;
        // if (!textureRects.empty()) [[likely]] {
        //     this->setTextureRect(*textureRects.begin());
        // }

        this->itCurrentTextureRect = this->textureRects.cbegin();
        this->timeElaspedCurrentTextureRect = Time::zero;
        if (!textureRects.empty()) [[likely]] {
            this->setTextureRect(*this->itCurrentTextureRect);
        }
    }
}
