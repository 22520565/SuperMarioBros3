#pragma once
#include <concepts>

namespace game {
    template <std::floating_point T>
    class Scalation2 {
      public:
        T centerX = T();
        T centerY = T();
        T factorX = T();
        T factorY = T();
    };
}
