#pragma once

#include "Texture.hpp"
#include "Drawable.hpp"
#include "Transformable.hpp"
#include "Rect.hpp"
#include "RenderTarget.hpp"

namespace game {
    class Sprite : public Drawable, public Transformable
    {
     //   int id; // Sprite ID in the sprite database
        const Texture* texture;
        Rect<uint_fast32_t> textureRect = Rect<uint_fast32_t>(Vector2<uint_fast32_t>(), texture->getSize());
       mutable D3DX10_SPRITE dxSprite;
        

        D3DXMATRIX matScaling;
        // Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????
        

      public:
          Sprite(const Texture& texture);

          void draw(RenderTarget& target) const override;
       Sprite(int id, int left, int top, int right, int bottom, const Texture* tex);

        void Draw(float x, float y);

        void setTexture();
        void setTextureRect();
    };

    typedef Sprite *LPSPRITE;
}
