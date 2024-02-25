#include "Brick.hpp"

namespace game {
    void Brick::render() {
        Animations *animations = Animations::GetInstance();
        animations->getAnimation(ID_ANI_BRICK)->render(this->position.x, this->position.y);
        // RenderBoundingBox();
    }

    void Brick::getBoundingBox(float &l, float &t, float &r, float &b) {
        l = this->position.x - BRICK_BBOX_WIDTH / 2;
        t = this->position.y - BRICK_BBOX_HEIGHT / 2;
        r = l + BRICK_BBOX_WIDTH;
        b = t + BRICK_BBOX_HEIGHT;
    }
}
