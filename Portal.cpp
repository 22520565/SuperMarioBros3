#include "Portal.hpp"
#include "Game.hpp"
#include "TextureHolder.hpp"

namespace game {
    Portal::Portal(const Vector2<std::float32_t>& position, float r, float b, int scene_id) {
        this->scene_id = scene_id;
        this->position=position;
        width = r - position.x;
        height = b - position.y;
    }

    void Portal::RenderBoundingBox() {
        D3DXVECTOR3 p(position.x, position.y, 0);
        RECT rect;

      const Texture*  bbox = TextureHolder::getTexture(L"textures/bbox.png");

        float l, t, r, b;

        getBoundingBox(l, t, r, b);
        rect.left = 0;
        rect.top = 0;
        rect.right = (int)r - (int)l;
        rect.bottom = (int)b - (int)t;

        float cx, cy;
        Game::GetInstance()->GetCamPos(cx, cy);

        Game::GetInstance()->Draw(position.x - cx, position.y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
    }

    void Portal::render() {
        RenderBoundingBox();
    }

    void Portal::getBoundingBox(float &l, float &t, float &r, float &b) {
        l = position.x - width / 2;
        t = position.y - height / 2;
        r = position.x + width / 2;
        b = position.y + height / 2;
    }
}
