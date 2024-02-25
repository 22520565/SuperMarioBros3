#pragma once

#include <algorithm>
#include <vector>
#include <windows.h>

namespace game {
    class GameObject;

    struct CCollisionEvent;
    typedef CCollisionEvent *LPCOLLISIONEVENT;

    struct CCollisionEvent {
         GameObject * src_obj; // source object : the object from which to calculate collision
         GameObject * obj;     // the target object

        float t, nx, ny;

        float dx, dy; // *RELATIVE* movement distance between this object and obj
        bool isDeleted;

        CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0,
                         GameObject * obj = NULL,  GameObject * src_obj = NULL) {
            this->t = t;
            this->nx = nx;
            this->ny = ny;
            this->dx = dx;
            this->dy = dy;
            this->obj = obj;
            this->src_obj = src_obj;
            this->isDeleted = false;
        }

        int WasCollided() { return t >= 0.0f && t <= 1.0f; }

        static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b) {
            return a->t < b->t;
        }
    };

    class CCollision {
        static CCollision *__instance;

      public:
        static void SweptAABB(
            float ml, // move left
            float mt, // move top
            float mr, // move right
            float mb, // move bottom
            float dx, //
            float dy, //
            float sl, // static left
            float st,
            float sr,
            float sb,
            float &t,
            float &nx,
            float &ny);

        LPCOLLISIONEVENT SweptAABB(
             GameObject * objSrc,
            DWORD dt,
             GameObject * objDest);
        void Scan(
             GameObject * objSrc,
            DWORD dt,
            std::vector< GameObject *> *objDests,
            std::vector<LPCOLLISIONEVENT> &coEvents);

        void Filter(
             GameObject * objSrc,
            std::vector<LPCOLLISIONEVENT> &coEvents,
            LPCOLLISIONEVENT &colX,
            LPCOLLISIONEVENT &colY,
            int filterBlock,
            int filterX,
            int filterY);

        void Process( GameObject * objSrc, DWORD dt, std::vector< GameObject *> *coObjects);

        static CCollision *GetInstance();
    };
}
