#pragma once

#include "Game.hpp"
#include "Texture.hpp"

namespace game {
    class Sprite {
        int id; // Sprite ID in the sprite database

        int left;
        int top;
        int right;
        int bottom;

        const Texture* texture;
        D3DX10_SPRITE sprite;
        D3DXMATRIX matScaling;

      public:
        Sprite(int id, int left, int top, int right, int bottom, const Texture* tex);

        void Draw(float x, float y);

        void setTexture();
        void setTextureRect();
    };

    typedef Sprite *LPSPRITE;
}
