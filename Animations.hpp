#pragma once

#include "Animation.hpp"
#include "Sprite.hpp"

namespace game {
    class Animations {
        static Animations *__instance;

        std::unordered_map<int, LPANIMATION> animations;

    public:
        void add(int id, LPANIMATION ani);
        LPANIMATION Get(int id);
        void Clear();

        static Animations *GetInstance();
    };
}
