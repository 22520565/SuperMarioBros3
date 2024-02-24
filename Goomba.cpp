#include "Goomba.hpp"

namespace game {
    Goomba::Goomba(float x, float y) : GameObject(x, y) {
        this->ax = 0;
        this->ay = GOOMBA_GRAVITY;
        die_start = -1;
        SetState(GOOMBA_STATE_WALKING);
    }

    void Goomba::getBoundingBox(float &left, float &top, float &right, float &bottom) {
        if (state == GOOMBA_STATE_DIE) {
            left = x - GOOMBA_BBOX_WIDTH / 2;
            top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
            right = left + GOOMBA_BBOX_WIDTH;
            bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
        } else {
            left = x - GOOMBA_BBOX_WIDTH / 2;
            top = y - GOOMBA_BBOX_HEIGHT / 2;
            right = left + GOOMBA_BBOX_WIDTH;
            bottom = top + GOOMBA_BBOX_HEIGHT;
        }
    }

    void Goomba::OnNoCollision(DWORD dt) {
        x += vx * dt;
        y += vy * dt;
    };

    void Goomba::OnCollisionWith(LPCOLLISIONEVENT e) {
        if (!e->obj->IsBlocking())
            return;
        if (dynamic_cast<Goomba *>(e->obj))
            return;

        if (e->ny != 0) {
            vy = 0;
        } else if (e->nx != 0) {
            vx = -vx;
        }
    }

    void Goomba::update(DWORD dt, std::vector<LPGAMEOBJECT> *coObjects) {
        vy += ay * dt;
        vx += ax * dt;

        if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT)) {
            isDeleted = true;
            return;
        }

        GameObject::update(dt, coObjects);
        CCollision::GetInstance()->Process(this, dt, coObjects);
    }

    void Goomba::render() {
        int aniId = ID_ANI_GOOMBA_WALKING;
        if (state == GOOMBA_STATE_DIE) {
            aniId = ID_ANI_GOOMBA_DIE;
        }

        Animations::GetInstance()->getAnimation(aniId)->render(x, y);
        RenderBoundingBox();
    }

    void Goomba::SetState(int state) {
        GameObject::SetState(state);
        switch (state) {
        case GOOMBA_STATE_DIE:
            die_start = GetTickCount64();
            y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
            vx = 0;
            vy = 0;
            ay = 0;
            break;
        case GOOMBA_STATE_WALKING:
            vx = -GOOMBA_WALKING_SPEED;
            break;
        }
    }
}
