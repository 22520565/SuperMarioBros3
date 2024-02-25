#pragma once

#include "Animation.hpp"
#include "Animations.hpp"
#include "Collision.hpp"
#include "Sprites.hpp"
#include "Vector3.hpp"
#include "stdfloat"
#include <d3dx10.h>
#include <vector>
#include <windows.h>

#define ID_TEX_BBOX -100 // special texture to draw object bounding box
#define BBOX_ALPHA 0.25f // Bounding box transparency

namespace game {
    class GameObject {
      public:
        constexpr GameObject() = default;
        constexpr GameObject(std::float32_t x, std::float32_t y) noexcept : x(x), y(y) {}

        constexpr void setPosition(const std::float32_t x, const std::float32_t y) noexcept(
            noexcept(this->position = Vector2(x, y))) {
            this->position = Vector2(x, y);
        }

        void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
        void GetPosition(float &x, float &y) {
            x = this->x;
            y = this->y;
        }
        void GetSpeed(float &vx, float &vy) {
            vx = this->vx;
            vy = this->vy;
        }

        constexpr const int_fast32_t &getState() const noexcept { return this->state; }
        virtual void Delete() { isDeleted = true; }
        bool IsDeleted() { return isDeleted; }

        void RenderBoundingBox();

        virtual void getBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
        virtual void update(DWORD dt, std::vector<LPGAMEOBJECT> *coObjects = NULL){};
        virtual void render() = 0;
        virtual void SetState(int state) { this->state = state; }

        //
        // Collision ON or OFF ? This can change depending on object's state. For example: die
        //
        virtual int IsCollidable() { return 0; };

        // When no collision has been detected (triggered by CCollision::Process)
        virtual void OnNoCollision(DWORD dt){};

        // When collision with an object has been detected (triggered by CCollision::Process)
        virtual void OnCollisionWith(LPCOLLISIONEVENT e){};

        // Is this object blocking other object? If YES, collision framework will automatically push the other object
        virtual int IsBlocking() { return 1; }

        static bool IsDeleted(const LPGAMEOBJECT &o) { return o->isDeleted; }

      protected:
        Vector2<std::float32_t> position = Vector2<std::float32_t>();
        Vector2<std::float32_t> speed = Vector2<std::float32_t>();

        // position
        std::float32_t x = 0.0F;
        std::float32_t y = 0.0F;

        // speed, about to replace
        std::float32_t vx = 0.0F;
        std::float32_t vy = 0.0F;

        int_fast32_t nx = 1;

        int_fast32_t state = -1;

        bool isDeleted = false;
    };
}
