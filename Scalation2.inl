#include "Scalation2.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Scalation2<T>::Scalation2(const Vector2<T> &factor, const Vector2<T> &center) noexcept(
        noexcept(T(factor.x)) && noexcept(T(factor.y)) && noexcept(T(center.x)) && noexcept(T(center.y)))
        : factorX(factor.x), factorY(factor.y), centerX(center.x), centerY(center.y) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    template <typename U>
        requires std::is_arithmetic_v<U>
    constexpr Scalation2<T>::Scalation2(const Scalation2<U> &scalation2) noexcept(
        noexcept(T(static_cast<T>(scalation2.factorX))) && noexcept(T(static_cast<T>(scalation2.factorY)))
            && noexcept(T(static_cast<T>(scalation2.centerX))) && noexcept(T(static_cast<T>(scalation2.centerY))))
        : factorX(static_cast<T>(scalation2.factorX)), factorY(static_cast<T>(scalation2.factorY)),
          centerX(static_cast<T>(scalation2.centerX)), centerY(static_cast<T>(scalation2.centerY)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector2<T> Scalation2<T>::getFactor() const noexcept(
        noexcept(Vector2<T>(T(), T()))) {
        return Vector2<T>(this->factorX, this->factorY);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector2<T> Scalation2<T>::getCenter() const noexcept(
        noexcept(Vector2<T>(T(), T()))) {
        return Vector2<T>(this->centerX, this->centerY);
    }
}
