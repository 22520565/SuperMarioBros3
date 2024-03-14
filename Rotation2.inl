#include "Rotation2.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation2<T>::Rotation2(const Angle2<T> &angle2) noexcept(
        noexcept(Angle<T>(angle2.x)) && noexcept(Angle<T>(angle2.y)) && noexcept(T(T())))
        : angleX(angle2.x), angleY(angle2.y), centerX(T()), centerY(T()) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation2<T>::Rotation2(const Vector2<T> &center) noexcept(
        noexcept(T(center.x)) && noexcept(T(center.y)) && noexcept(Angle<T>(Angle<T>::zero())))
        : centerX(center.x), centerY(center.y), angleX(Angle<T>::zero()), angleY(Angle<T>::zero()) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation2<T>::Rotation2(const Angle2<T> &angle2, const Vector2<T> &center) noexcept(
        noexcept(Angle<T>(angle2.x)) && noexcept(Angle<T>(angle2.y))
            && noexcept(T(center.x)) && noexcept(T(center.y)))
        : angleX(angle2.x), angleY(angle2.y), centerX(center.x), centerY(center.y) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    template <std::floating_point U>
    constexpr Rotation2<T>::Rotation2(const Rotation2<U> &rotation2) noexcept(
        noexcept(Angle<T>(rotation2.angleX)) && noexcept(Angle<T>(rotation2.angleY))
            && noexcept(T(rotation2.centerX)) && noexcept(T(rotation2.centerY)))
        : angleX(rotation2.angleX), angleY(rotation2.angleY),
          centerX(rotation2.centerX), centerY(rotation2.centerY) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T> Rotation2<T>::getAngle() const noexcept(
        noexcept(Angle2<T>(Angle<T>(), Angle<T>()))) {
        return Angle2<T>(this->angleX, this->angleY);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Vector2<T> Rotation2<T>::getCenter() const noexcept(
        noexcept(Vector2<T>(T(), T()))) { return Vector2<T>(this->centerX, this->centerY); }
}
