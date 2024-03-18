#pragma once

#include "Drawable.hpp"
#include "Rect2.hpp"
#include "RenderTarget.hpp"
#include "Texture.hpp"
#include "Transformable.hpp"


//TODO: Maybe we should create a StaticSprite?
namespace game {
    class Sprite : public Drawable, public Transformable<float> {
        //   int id; // Sprite ID in the sprite database
        const Texture *texture=nullptr;
        Rect2uf32 textureRect = Rect2uf32();
        void draw(RenderTarget &target) const override;

      public:
        inline Sprite() = default;

        Sprite(const Texture &texture)noexcept(
            noexcept(Rect2uf32(Vector2uf32::zero(), texture.getSize())));

        Sprite(const Texture& texture,const Rect2uf32& textureRect) noexcept;

        Sprite(int id, int left, int top, int right, int bottom, const Texture *tex);

        void Draw(float x, float y);

        void setTexture(const Texture& texture) noexcept(
            noexcept(Rect2uf32(Vector2uf32::zero(), texture.getSize())));

        void setTexture(const Texture& texture, const Rect2uf32& textureRect) noexcept;

       constexpr void setTextureRect(const Rect2uf32& textureRect) noexcept;
    };

    typedef Sprite *LPSPRITE;
}

#include "Sprite.inl"
