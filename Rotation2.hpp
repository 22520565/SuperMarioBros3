#pragma once
#include "Angle.hpp"
#include "Angle2.hpp"
#include "Vector2.hpp"
#include <concepts>

namespace game {
    template <std::floating_point T>
    struct Rotation2 {
      public:
        const Angle2<T &> angle = Angle2<T &>(angleX, angleY);
        const Vector2<T &> center = Vector2<T &>(centerX, centerY);

        constexpr Rotation2() = default;

        constexpr explicit Rotation2(const Angle2<T> &angle) noexcept(
            noexcept(Angle<T>(angle.x)) && noexcept(Angle<T>(angle.y)) && noexcept(T(T())));

        constexpr explicit Rotation2(const Vector2<T> &center) noexcept(
            noexcept(T(center.x)) && noexcept(T(center.y)) && noexcept(Angle<T>(Angle<T>::zero())));

        constexpr explicit Rotation2(const Angle2<T> &angle, const Vector2<T> &center) noexcept(
            noexcept(Angle<T>(angle.x)) && noexcept(Angle<T>(angleY(angle.y)))
                && noexcept(T(center.x)) && noexcept(T(center.y)));

        template <std::floating_point U>
        constexpr explicit Rotation2(const Rotation2<U> &rotation2) noexcept(
            noexcept(Angle<T>(rotation2.angle.x)) && noexcept(Angle<T>(rotation2.angle.y))
                && noexcept(T(rotation2.center.x)) && noexcept(T(rotation2.center.y)));

        [[nodiscard]]
        friend constexpr bool
        operator==(const Rotation2<T> &left, const Rotation2<T> &right) = default;

      private:
        Angle<T> angleX = Angle<T>::zero();
        Angle<T> angleY = Angle<T>::zero();
        T centerX = T();
        T centerY = T();
    };
}
