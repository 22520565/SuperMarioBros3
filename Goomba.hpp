#pragma once
#include "GameObject.hpp"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

namespace game {
    class Goomba : public GameObject {
    protected:
        float ax;
        float ay;

        ULONGLONG die_start;

        virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
        virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT> *coObjects);
        virtual void render();

        virtual int IsCollidable() { return 1; };
        virtual int IsBlocking() { return 0; }
        virtual void OnNoCollision(DWORD dt);

        virtual void OnCollisionWith(LPCOLLISIONEVENT e);

    public:
        Goomba(float x, float y);
        virtual void SetState(int state);
    };
}
