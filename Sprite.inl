#include "Sprite.hpp"

namespace game {
    inline Sprite::Sprite(const Texture& texture) noexcept(
        noexcept(Rect2uf32(Vector2uf32::zero(), texture.getSize())))
        : Sprite(texture, Rect2uf32(Vector2uf32::zero(), texture.getSize())) {}

    inline Sprite::Sprite(const Texture& texture, const Rect2uf32& textureRect) noexcept
        : texture(&texture), textureRect(textureRect) {}


    inline void Sprite::setTexture(const Texture& texture) noexcept(
        noexcept(Rect2uf32(Vector2uf32::zero(), texture.getSize()))) {
        this->setTexture(texture, Rect2uf32(Vector2uf32::zero(), texture.getSize()));
    }

    inline void Sprite::setTexture(const Texture& texture, const Rect2uf32& textureRect) noexcept
    {
        this->texture = &texture;
        this->textureRect = textureRect;
    }

    constexpr void Sprite::setTextureRect(const Rect2uf32& textureRect) noexcept {
        this->textureRect = textureRect;
    }
}
