#pragma once

#include "Animation.hpp"
#include "Animations.hpp"
#include "GameObject.hpp"

namespace game {

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

    class Brick : public GameObject {
    public:
        Brick(float x, float y) : GameObject(x, y) {}
        void render();
        void Update(DWORD dt) {}
        void GetBoundingBox(float& l, float& t, float& r, float& b);
    };
}
