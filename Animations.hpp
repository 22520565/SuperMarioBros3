#pragma once

#include "Animation.hpp"
#include "Sprite.hpp"

class CAnimations {
    static CAnimations *__instance;

    unordered_map<int, LPANIMATION> animations;

public:
    void Add(int id, LPANIMATION ani);
    LPANIMATION Get(int id);
    void Clear();

    static CAnimations *GetInstance();
};
