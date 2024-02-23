#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <windows.h>

#include "AnimationFrame.hpp"
#include "Sprites.hpp"

namespace game {
    class Animation {
        uint_fast64_t lastFrameTime;
        int defaultTime;
        int currentFrame;
        std::vector<LPANIMATION_FRAME> frames;

    public:
        Animation(int defaultTime = 100) {
            this->defaultTime = defaultTime;
            lastFrameTime = -1;
            currentFrame = -1;
        }
        void Add(int spriteId, DWORD time = 0);
        void Render(float x, float y);
    };

    typedef Animation *LPANIMATION;
}
