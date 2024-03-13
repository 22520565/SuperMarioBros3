#include "Rotation2.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation2<T>::Rotation2(const Angle2<T> &angle) noexcept(
        noexcept(Angle<T>(angle.x)) && noexcept(Angle<T>(angleY(angle.y))) && noexcept(T(T())))
        : angleX(angle.x), angleY(angle.y), centerX(T()), centerY(T()) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation2<T>::Rotation2(const Vector2<T> &center) noexcept(
        noexcept(T(center.x)) && noexcept(T(center.y)) && noexcept(Angle<T>(Angle<T>::zero())))
        : centerX(center.x), centerY(center.y), angleX(Angle<T>::zero()), angleY(Angle<T>::zero()) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation2<T>::Rotation2(const Angle2<T> &angle, const Vector2<T> &center) noexcept(
        noexcept(Angle<T>(angle.x)) && noexcept(Angle<T>(angleY(angle.y)))
            && noexcept(T(center.x)) && noexcept(T(center.y)))
        : angleX(angle.x), angleY(angle.y), centerX(center.x), centerY(center.y) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    template <std::floating_point U>
    constexpr Rotation2<T>::Rotation2(const Rotation2<U> &rotation2) noexcept(
        noexcept(Angle<T>(rotation2.angle.x)) && noexcept(Angle<T>(rotation2.angle.y))
            && noexcept(T(rotation2.center.x)) && noexcept(T(rotation2.center.y)))
        : angleX(rotation2.angle.x), angleY(rotation2.angle.y),
          centerX(rotation2.center.x), centerY(rotation2.center.y) {}
}
