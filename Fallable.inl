#include "Fallable.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Fallable<T>::Fallable(const T gravity) noexcept
        : gravity(gravity) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr bool Fallable<T>::hasGravity() const noexcept { return this->gravity == static_cast<T>(0); }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr void Fallable<T>::update(const T deltaTime) noexcept {
        this->move(Vector3<T>::unitY() * this->gravity * deltaTime);
    }
}
