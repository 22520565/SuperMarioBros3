#include "Movable.hpp"
#include "Vector3.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Movable<T>::Movable(const Vector3<T> &speed) noexcept
        : speed(speed) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr bool Movable<T>::isMoving() const noexcept { return this->speed == Vector3<T>::zero(); }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr void Movable<T>::update(const T deltaTime) {
        this->move(this->speed * deltaTime);
    }
}
