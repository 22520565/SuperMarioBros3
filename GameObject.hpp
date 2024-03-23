#pragma once
#include "Sprite.hpp"
#include "Time.hpp"

namespace game {
    class GameObject {
      public:
        bool enabled = true;

        Sprite sprite = Sprite();

        constexpr virtual ~GameObject() = default;

        virtual void loadFromFile(const TCHAR *const fileName);

        virtual void update(const Time deltaTime);
    };
}

#include "GameObject.inl"
