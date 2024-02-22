#pragma once

#include "Animation.hpp"
#include "Animations.hpp"
#include "GameObject.hpp"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
public:
    CBrick(float x, float y) : CGameObject(x, y) {}
    void Render();
    void Update(DWORD dt) {}
    void GetBoundingBox(float &l, float &t, float &r, float &b);
};
