#pragma once

#include "stdfloat"
#include <cstdint>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <windows.h>
#include "Sprites.hpp"

namespace game {
    class Animation final {
      public:
        constexpr explicit Animation() noexcept = default;

        [[deprecated("'defaultTime' is redundant")]] constexpr explicit Animation(const int defaultTime) noexcept
            : defaultTime(defaultTime) {}

        void add(int_fast32_t spriteId, DWORD time);

        void render(const std::float32_t x, const std::float32_t y);

      private:
        uint_fast64_t lastFrameTime = 100U;
        int_fast32_t defaultTime = -1;
        int_fast32_t currentFrame = -1;
        std::vector<LPANIMATION_FRAME> frames;
    };

    typedef Animation *LPANIMATION;
}
