#include "Goomba.hpp"

namespace game {
    void Goomba::getBoundingBox(float &left, float &top, float &right, float &bottom) {
        if (state == GOOMBA_STATE_DIE) {
            left = this->position.x - GOOMBA_BBOX_WIDTH / 2;
            top = this->position.y - GOOMBA_BBOX_HEIGHT_DIE / 2;
            right = left + GOOMBA_BBOX_WIDTH;
            bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
        } else {
            left = this->position.x - GOOMBA_BBOX_WIDTH / 2;
            top = this->position.y - GOOMBA_BBOX_HEIGHT / 2;
            right = left + GOOMBA_BBOX_WIDTH;
            bottom = top + GOOMBA_BBOX_HEIGHT;
        }
    }

    void Goomba::OnNoCollision(DWORD dt) {
        this->position.x += this->speed.x * dt;
        this->position.y += this->speed.y * dt;
    };

    void Goomba::OnCollisionWith(LPCOLLISIONEVENT e) {
        if (!e->obj->IsBlocking())
            return;
        if (dynamic_cast<Goomba *>(e->obj))
            return;

        if (e->ny != 0) {
            this->speed.y = 0;
        } else if (e->nx != 0) {
            this->speed.x = -this->speed.x;
        }
    }

    void Goomba::update(DWORD dt, std::vector<LPGAMEOBJECT> *coObjects) {
        this->speed.y += ay * dt;
        this->speed.x += ax * dt;

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

        Animations::GetInstance()->getAnimation(aniId)->render(position.x, position.y);
        RenderBoundingBox();
    }

    void Goomba::SetState(int state) {
        GameObject::SetState(state);
        switch (state) {
        case GOOMBA_STATE_DIE:
            die_start = GetTickCount64();
           this->position. y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
            this->speed.x = 0;
            this->speed.y = 0;
            ay = 0;
            break;
        case GOOMBA_STATE_WALKING:
            this->speed.x = -GOOMBA_WALKING_SPEED;
            break;
        }
    }
}
