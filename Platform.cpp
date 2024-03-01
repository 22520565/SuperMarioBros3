#include "Platform.hpp"

#include "Sprite.hpp"
#include "Sprites.hpp"

#include "Textures.hpp"

namespace game {
    void Platform::RenderBoundingBox() {
        D3DXVECTOR3 p(position.x, position.y, 0);
        RECT rect;

        const Texture* bbox = Textures::getTexture(L"textures/bbox.png");

        float l, t, r, b;

        getBoundingBox(l, t, r, b);
        rect.left = 0;
        rect.top = 0;
        rect.right = (int)r - (int)l;
        rect.bottom = (int)b - (int)t;

        float cx, cy;
        Game::GetInstance()->GetCamPos(cx, cy);

        float xx = position.x - this->cellWidth / 2 + rect.right / 2;

        Game::GetInstance()->Draw(xx - cx, position.y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
    }

    void Platform::render() {
        if (this->length <= 0)
            return;
        float xx = position.x;
        Sprites *s = Sprites::GetInstance();

        s->Get(this->spriteIdBegin)->Draw(xx, position.y);
        xx += this->cellWidth;
        for (int i = 1; i < this->length - 1; i++) {
            s->Get(this->spriteIdMiddle)->Draw(xx, position.y);
            xx += this->cellWidth;
        }
        if (length > 1)
            s->Get(this->spriteIdEnd)->Draw(xx, position.y);

        RenderBoundingBox();
    }

    void Platform::getBoundingBox(float &l, float &t, float &r, float &b) {
        float cellWidth_div_2 = this->cellWidth / 2;
        l = position.x - cellWidth_div_2;
        t = position.y - this->cellHeight / 2;
        r = l + this->cellWidth * this->length;
        b = t + this->cellHeight;
    }
}
