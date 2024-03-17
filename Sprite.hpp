#pragma once

#include "Drawable.hpp"
#include "Rect2.hpp"
#include "RenderTarget.hpp"
#include "Texture.hpp"
#include "Transformable.hpp"

namespace game {
    class Sprite : public Drawable, public Transformable<float> {
        //   int id; // Sprite ID in the sprite database
        const Texture *texture=nullptr;
        Rect2<uint_fast32_t> textureRect = Rect2 <uint_fast32_t> ();// Rect2<uint_fast32_t>(Vector2<uint_fast32_t>(), texture->getSize());
        void draw(RenderTarget &target) const override;

        D3DXMATRIX matScaling;

      public:
        inline Sprite() = default;
        Sprite(const Texture &texture);

        Sprite(int id, int left, int top, int right, int bottom, const Texture *tex);

        void Draw(float x, float y);

        void setTexture(const Texture& texture) { 
            this->texture = &texture; 
            this->textureRect = Rect2<uint_fast32_t>(Vector2<uint_fast32_t>(), texture.getSize()); }
        void setTextureRect();
    };

    typedef Sprite *LPSPRITE;
}
