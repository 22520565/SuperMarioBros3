#include "debug.hpp"
#include <algorithm>

#include "Game.hpp"
#include "Mario.hpp"

#include "Coin.hpp"
#include "Goomba.hpp"
#include "Portal.hpp"

#include "Collision.hpp"

namespace game {
    void Mario::update(DWORD dt, std::vector<LPGAMEOBJECT> *coObjects) {
        speed.y += ay * dt;
        speed.x += ax * dt;

        if (abs(speed.x) > abs(maxVx))
            speed.x = maxVx;

        // reset untouchable timer if untouchable time has passed
        if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) {
            untouchable_start = 0;
            untouchable = 0;
        }

        isOnPlatform = false;

        CCollision::GetInstance()->Process(this, dt, coObjects);
    }

    void Mario::OnNoCollision(DWORD dt) {
        position.x += speed.x * dt;
        position.y += speed.y * dt;
    }

    void Mario::OnCollisionWith(LPCOLLISIONEVENT e) {
        if (e->ny != 0 && e->obj->IsBlocking()) {
            speed.y = 0;
            if (e->ny < 0)
                isOnPlatform = true;
        } else if (e->nx != 0 && e->obj->IsBlocking()) {
            speed.x = 0;
        }

        if (dynamic_cast<Goomba *>(e->obj))
            OnCollisionWithGoomba(e);
        else if (dynamic_cast<Coin *>(e->obj))
            OnCollisionWithCoin(e);
        else if (dynamic_cast<Portal *>(e->obj))
            OnCollisionWithPortal(e);
    }

    void Mario::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
        Goomba *goomba = dynamic_cast<Goomba *>(e->obj);

        // jump on top >> kill Goomba and deflect a bit
        if (e->ny < 0) {
            if (goomba->getState() != GOOMBA_STATE_DIE) {
                goomba->SetState(GOOMBA_STATE_DIE);
                speed.y = -MARIO_JUMP_DEFLECT_SPEED;
            }
        } else // hit by Goomba
        {
            if (untouchable == 0) {
                if (goomba->getState() != GOOMBA_STATE_DIE) {
                    if (level > MARIO_LEVEL_SMALL) {
                        level = MARIO_LEVEL_SMALL;
                        StartUntouchable();
                    } else {
                        DebugOut(L">>> Mario DIE >>> \n");
                        SetState(MARIO_STATE_DIE);
                    }
                }
            }
        }
    }

    void Mario::OnCollisionWithCoin(LPCOLLISIONEVENT e) {
        e->obj->Delete();
        coin++;
    }

    void Mario::OnCollisionWithPortal(LPCOLLISIONEVENT e) {
        Portal *p = (Portal *)e->obj;
        Game::GetInstance()->InitiateSwitchScene(p->GetSceneId());
    }

    //
    // Get animation ID for small Mario
    //
    int Mario::GetAniIdSmall() {
        int aniId = -1;
        if (!isOnPlatform) {
            if (abs(ax) == MARIO_ACCEL_RUN_X) {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
                else
                    aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
            } else {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
                else
                    aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
            }
        } else if (isSitting) {
            if (nx > 0)
                aniId = ID_ANI_MARIO_SIT_RIGHT;
            else
                aniId = ID_ANI_MARIO_SIT_LEFT;
        } else if (speed.x == 0) {
            if (nx > 0)
                aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
            else
                aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
        } else if (speed.x > 0) {
            if (ax < 0)
                aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
            else if (ax == MARIO_ACCEL_RUN_X)
                aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
            else if (ax == MARIO_ACCEL_WALK_X)
                aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
        } else // speed.x < 0
        {
            if (ax > 0)
                aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
            else if (ax == -MARIO_ACCEL_RUN_X)
                aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
            else if (ax == -MARIO_ACCEL_WALK_X)
                aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
        }

        if (aniId == -1)
            aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

        return aniId;
    }

    //
    // Get animdation ID for big Mario
    //
    int Mario::GetAniIdBig() {
        int aniId = -1;
        if (!isOnPlatform) {
            if (abs(ax) == MARIO_ACCEL_RUN_X) {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
                else
                    aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
            } else {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
                else
                    aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
            }
        } else if (isSitting) {
            if (nx > 0)
                aniId = ID_ANI_MARIO_SIT_RIGHT;
            else
                aniId = ID_ANI_MARIO_SIT_LEFT;
        } else if (speed.x == 0) {
            if (nx > 0)
                aniId = ID_ANI_MARIO_IDLE_RIGHT;
            else
                aniId = ID_ANI_MARIO_IDLE_LEFT;
        } else if (speed.x > 0) {
            if (ax < 0)
                aniId = ID_ANI_MARIO_BRACE_RIGHT;
            else if (ax == MARIO_ACCEL_RUN_X)
                aniId = ID_ANI_MARIO_RUNNING_RIGHT;
            else if (ax == MARIO_ACCEL_WALK_X)
                aniId = ID_ANI_MARIO_WALKING_RIGHT;
        } else // speed.x < 0
        {
            if (ax > 0)
                aniId = ID_ANI_MARIO_BRACE_LEFT;
            else if (ax == -MARIO_ACCEL_RUN_X)
                aniId = ID_ANI_MARIO_RUNNING_LEFT;
            else if (ax == -MARIO_ACCEL_WALK_X)
                aniId = ID_ANI_MARIO_WALKING_LEFT;
        }

        if (aniId == -1)
            aniId = ID_ANI_MARIO_IDLE_RIGHT;

        return aniId;
    }

    void Mario::render() {
        Animations *animations = Animations::GetInstance();
        int aniId = -1;

        if (state == MARIO_STATE_DIE)
            aniId = ID_ANI_MARIO_DIE;
        else if (level == MARIO_LEVEL_BIG)
            aniId = GetAniIdBig();
        else if (level == MARIO_LEVEL_SMALL)
            aniId = GetAniIdSmall();

        animations->getAnimation(aniId)->render(position.x, position.y);

        // RenderBoundingBox();

        DebugOutTitle(L"Coins: %d", coin);
    }

    void Mario::SetState(int state) {
        // DIE is the end state, cannot be changed!
        if (this->state == MARIO_STATE_DIE)
            return;

        switch (state) {
        case MARIO_STATE_RUNNING_RIGHT:
            if (isSitting)
                break;
            maxVx = MARIO_RUNNING_SPEED;
            ax = MARIO_ACCEL_RUN_X;
            nx = 1;
            break;
        case MARIO_STATE_RUNNING_LEFT:
            if (isSitting)
                break;
            maxVx = -MARIO_RUNNING_SPEED;
            ax = -MARIO_ACCEL_RUN_X;
            nx = -1;
            break;
        case MARIO_STATE_WALKING_RIGHT:
            if (isSitting)
                break;
            maxVx = MARIO_WALKING_SPEED;
            ax = MARIO_ACCEL_WALK_X;
            nx = 1;
            break;
        case MARIO_STATE_WALKING_LEFT:
            if (isSitting)
                break;
            maxVx = -MARIO_WALKING_SPEED;
            ax = -MARIO_ACCEL_WALK_X;
            nx = -1;
            break;
        case MARIO_STATE_JUMP:
            if (isSitting)
                break;
            if (isOnPlatform) {
                if (abs(this->speed.x) == MARIO_RUNNING_SPEED)
                    speed.y = -MARIO_JUMP_RUN_SPEED_Y;
                else
                    speed.y = -MARIO_JUMP_SPEED_Y;
            }
            break;

        case MARIO_STATE_RELEASE_JUMP:
            if (speed.y < 0)
                speed.y += MARIO_JUMP_SPEED_Y / 2;
            break;

        case MARIO_STATE_SIT:
            if (isOnPlatform && level != MARIO_LEVEL_SMALL) {
                state = MARIO_STATE_IDLE;
                isSitting = true;
                speed.x = 0;
                speed.y = 0.0f;
                position.y += MARIO_SIT_HEIGHT_ADJUST;
            }
            break;

        case MARIO_STATE_SIT_RELEASE:
            if (isSitting) {
                isSitting = false;
                state = MARIO_STATE_IDLE;
                position.y -= MARIO_SIT_HEIGHT_ADJUST;
            }
            break;

        case MARIO_STATE_IDLE:
            ax = 0.0f;
            speed.x = 0.0f;
            break;

        case MARIO_STATE_DIE:
            speed.y = -MARIO_JUMP_DEFLECT_SPEED;
            speed.x = 0;
            ax = 0;
            break;
        }

        GameObject::SetState(state);
    }

    void Mario::getBoundingBox(float &left, float &top, float &right, float &bottom) {
        if (level == MARIO_LEVEL_BIG) {
            if (isSitting) {
                left = position.x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
                top = position.y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
                right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
                bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
            } else {
                left = position.x - MARIO_BIG_BBOX_WIDTH / 2;
                top = position.y - MARIO_BIG_BBOX_HEIGHT / 2;
                right = left + MARIO_BIG_BBOX_WIDTH;
                bottom = top + MARIO_BIG_BBOX_HEIGHT;
            }
        } else {
            left = position.x - MARIO_SMALL_BBOX_WIDTH / 2;
            top = position.y - MARIO_SMALL_BBOX_HEIGHT / 2;
            right = left + MARIO_SMALL_BBOX_WIDTH;
            bottom = top + MARIO_SMALL_BBOX_HEIGHT;
        }
    }

    void Mario::SetLevel(int l) {
        // Adjust position to avoid falling off platform
        if (this->level == MARIO_LEVEL_SMALL) {
            position.y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
        }
        level = l;
    }
}
