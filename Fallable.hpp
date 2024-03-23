#pragma once
#include "Vector3.hpp"

namespace game {
    template <typename T>
        requires std::is_arithmetic_v<T>
    class Fallable {
      public:
        T gravity = T();

        constexpr Fallable() = default;

        constexpr explicit Fallable(const T gravity) noexcept;

        constexpr virtual ~Fallable() = default;

        constexpr virtual void move(const Vector3<T> &offset) noexcept = 0;

        [[nodiscard]]
        constexpr bool hasGravity() const noexcept;

        constexpr virtual void update(const T deltaTime) noexcept;
    };
}
