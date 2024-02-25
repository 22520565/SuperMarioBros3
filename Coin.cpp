#include "Coin.hpp"

namespace game {
    void Coin::render() {
        Animations *animations = Animations::GetInstance();
        animations->getAnimation(ID_ANI_COIN)->render(this->position.x,this->position.y);

        // RenderBoundingBox();
    }

    void Coin::getBoundingBox(float &l, float &t, float &r, float &b) {
        l = this->position.x - COIN_BBOX_WIDTH / 2;
        t = this->position.y - COIN_BBOX_HEIGHT / 2;
        r = l + COIN_BBOX_WIDTH;
        b = t + COIN_BBOX_HEIGHT;
    }
}
