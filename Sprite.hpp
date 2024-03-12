#pragma once

#include "Texture.hpp"
#include "Drawable.hpp"
#include "Transformable.hpp"
#include "Rect.hpp"
#include "RenderTarget.hpp"

namespace game {
    class Sprite : public Drawable, public Transformable<float>
    {
     //   int id; // Sprite ID in the sprite database
        const Texture* texture;
        Rect<uint_fast32_t> textureRect = Rect<uint_fast32_t>(Vector2<uint_fast32_t>(), texture->getSize());
        void draw(RenderTarget& target) const override;
        

        D3DXMATRIX matScaling;
        

      public:
          Sprite(const Texture& texture);

       Sprite(int id, int left, int top, int right, int bottom, const Texture* tex);

        void Draw(float x, float y);

        void setTexture();
        void setTextureRect();
    };

    typedef Sprite *LPSPRITE;
}
