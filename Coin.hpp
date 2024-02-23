#pragma once

#include "Animation.hpp"
#include "Animations.hpp"
#include "GameObject.hpp"

#define ID_ANI_COIN 11000

#define COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

namespace game {
    class Coin : public GameObject {
    public:
        Coin(float x, float y) : GameObject(x, y) {}
        void Render();
        void Update(DWORD dt) {}
        void GetBoundingBox(float &l, float &t, float &r, float &b);
        int IsBlocking() { return 0; }
    };
}
