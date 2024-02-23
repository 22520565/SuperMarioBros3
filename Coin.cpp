#include "Coin.hpp"

namespace game {
    void Coin::render() {
        Animations *animations = Animations::GetInstance();
        animations->Get(ID_ANI_COIN)->render(x, y);

        // RenderBoundingBox();
    }

    void Coin::GetBoundingBox(float &l, float &t, float &r, float &b) {
        l = x - COIN_BBOX_WIDTH / 2;
        t = y - COIN_BBOX_HEIGHT / 2;
        r = l + COIN_BBOX_WIDTH;
        b = t + COIN_BBOX_HEIGHT;
    }
}
