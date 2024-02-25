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
        float ax = 0;
        float ay = GOOMBA_GRAVITY;

        ULONGLONG die_start = -1;

        virtual void getBoundingBox(float &left, float &top, float &right, float &bottom);
        virtual void update(DWORD dt, std::vector< GameObject *> *coObjects);
        virtual void render();

        virtual int IsCollidable() { return 1; };
        virtual int IsBlocking() { return 0; }
        virtual void OnNoCollision(DWORD dt);

        virtual void OnCollisionWith(LPCOLLISIONEVENT e);

      public:
        using GameObject::GameObject;
        explicit Goomba(const Vector2<std::float32_t> &position) : GameObject(position) {
            SetState(GOOMBA_STATE_WALKING);
        }
        virtual void SetState(int state);
    };
}
