#pragma once

#include "Animation.hpp"
#include "Sprite.hpp"

namespace game {
    class CAnimations {
        static CAnimations *__instance;

        std::unordered_map<int, LPANIMATION> animations;

    public:
        void Add(int id, LPANIMATION ani);
        LPANIMATION Get(int id);
        void Clear();

        static CAnimations *GetInstance();
    };
}
