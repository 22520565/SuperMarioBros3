#pragma once

#include "Collision.hpp"
#include "Vector2.hpp"
#include "stdfloat"
#include <vector>
#include <windows.h>

#define ID_TEX_BBOX -100 // special texture to draw object bounding box
#define BBOX_ALPHA 0.25f // Bounding box transparency

namespace game {
    class GameObject {
      public:
        constexpr GameObject() = default;

        constexpr explicit GameObject(const Vector2<std::float32_t> &position) noexcept(
            noexcept(Vector2(position))) : position(position) {}

        constexpr const Vector2<std::float32_t> &getPosition() const noexcept { return this->position; }

        constexpr void setPosition(const std::float32_t x, const std::float32_t y) noexcept(
            noexcept(this->position = Vector2(position.x, position.y))) { this->position = Vector2(x, y); }

        constexpr void setPosition(const Vector2<std::float32_t> &position) noexcept(
            noexcept(this->position = position)) { this->position = position; }

        constexpr const Vector2<std::float32_t> &getSpeed() const noexcept { return this->speed; }

        constexpr void setSpeed(const std::float32_t x, const std::float32_t y) noexcept(
            noexcept(this->speed = Vector2(position.x, position.y))) { this->speed = Vector2(x, y); }

        constexpr void setSpeed(const Vector2<std::float32_t> &speed) noexcept(
            noexcept(this->speed = speed)) { this->speed = speed; }

        constexpr const int_fast32_t &getState() const noexcept { return this->state; }

        virtual void Delete() { isDeleted = true; }
        bool IsDeleted() { return isDeleted; }

        void RenderBoundingBox();

        virtual void getBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
        virtual void update(DWORD dt, std::vector<GameObject *> *coObjects = NULL){};
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

        static bool IsDeleted(const GameObject *&o) { return o->isDeleted; }

      protected:
        Vector2<std::float32_t> position = Vector2<std::float32_t>();

        Vector2<std::float32_t> speed = Vector2<std::float32_t>();

        int_fast32_t nx = 1;

        int_fast32_t state = -1;

        bool isDeleted = false;
    };
}