#pragma once
#include "Vector3.hpp"

namespace game {
    template <typename T>
        requires std::is_arithmetic_v<T>
    class Movable {
      public:
        Vector3<T> speed = Vector3<T>::zero();

        constexpr Movable() = default;

        constexpr explicit Movable(const Vector3<T> &speed) noexcept;

        constexpr virtual ~Movable() = default;

        constexpr virtual void move(const Vector3<T> &offset) noexcept = 0;

        [[nodiscard]]
        constexpr bool isMoving() const noexcept;

        constexpr virtual void update(const T deltaTime);
    };
}

#include "Movable.inl"
