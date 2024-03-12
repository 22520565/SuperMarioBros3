#include "Angle2.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle2<T>::Angle2(const Angle<T> x, const Angle<T> y) noexcept(
        noexcept(Angle<T>(x)) && noexcept(Angle<T>(y))) : x(x), y(y) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    template <std::floating_point U>
    constexpr Angle2<T>::Angle2(const Angle2<U> &angle2) noexcept(
        noexcept(x(static_cast<Angle<T>>(angle2.x)))
            && noexcept(y(static_cast<Angle<T>>(angle2.y))))
        : x(static_cast<Angle<T>>(angle2.x)), y(static_cast<T>(angle2.y)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    template <std::floating_point U>
    constexpr Angle2<T>::Angle2(Angle2<U> &&angle2) noexcept(
        noexcept(x(static_cast<Angle<T>>(angle2.x)))
            && noexcept(y(static_cast<Angle<T>>(angle2.y))))
        : x(static_cast<Angle<T>>(angle2.x)), y(static_cast<T>(angle2.y)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Vector2<const T &> Angle2<T>::asDegrees() const noexcept(
        noexcept(Vector2<const T &>(x.asDegrees(), y.asDegrees()))) {
        return Vector2<const T &>(this->x.asDegrees(), this->y.asDegrees());
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Vector2<T> Angle2<T>::asRadians() const noexcept(
        noexcept(Vector2<T>(x.asRadians(), y.asRadians()))) {
        return Vector2<T>(this->x.asRadians(), this->y.asRadians());
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle2<T> Angle2<T>::wrapSigned() const noexcept(
        noexcept(Angle2<T>(x.wrapSigned(), y.wrapSigned()))) {
        return Angle2<T>(this->x.wrapSigned(), this->y.wrapSigned());
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle2<T> Angle2<T>::wrapUnsigned() const noexcept(
        noexcept(Angle2<T>(x.wrapUnsigned(), y.wrapUnsigned()))) {
        return Angle2<T>(this->x.wrapUnsigned(), this->y.wrapUnsigned());
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle2<T> Angle2<T>::zero() noexcept(noexcept(Angle2<T>(0.0_deg, 0.0_deg))) {
        return Angle2<T>(0.0_deg, 0.0_deg);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle2<T> Angle2<T>::one_deg() noexcept(noexcept(Angle2<T>(1.0_deg, 1.0_deg))) {
        return Angle2<T>(1.0_deg, 1.0_deg);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle2<T> Angle2<T>::unitX_deg() noexcept(noexcept(Angle2<T>(1.0_deg, 0.0_deg))) {
        return Angle2<T>(1.0_deg, 0.0_deg);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle2<T> Angle2<T>::unitY_deg() noexcept(noexcept(Angle2<T>(0.0_deg, 1.0_deg))) {
        return Angle2<T>(0.0_deg, 1.0_deg);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle2<T> Angle2<T>::one_rad() noexcept(noexcept(Angle2<T>(1.0_rad, 1.0_rad))) {
        return Angle2<T>(1.0_rad, 1.0_rad);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle2<T> Angle2<T>::unitX_rad() noexcept(noexcept(Angle2<T>(1.0_rad, 0.0_rad))) {
        return Angle2<T>(1.0_rad, 0.0_rad);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle2<T> Angle2<T>::unitY_rad() noexcept(noexcept(Angle2<T>(0.0_rad, 1.0_rad))) {
        return Angle2<T>(0.0_rad, 1.0_rad);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle2<T> operator+(const Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(left.x + right.x, left.y + right.y))) {
        return Angle2<T>(left.x + right.x, left.y + right.y);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle2<T> &operator+=(Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(left.x += right.x) && noexcept(left.y += right.y)) {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle2<T> operator-(const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(-right.x, -right.y))) {
        return Angle2<T>(-right.x, -right.y);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle2<T> operator-(const Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(left.x - right.x, left.y - right.y))) {
        return Angle2<T>(left.x - right.x, left.y - right.y);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle2<T> &operator-=(Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(left.x -= right.x) && noexcept(left.y -= right.y)) {
        left.x -= right.x;
        left.y -= right.y;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle2<T>
    operator*(const Angle2<T> &left, const T right) noexcept(
        noexcept(Angle2<T>(left.x * right, left.y *right))) {
        return Angle2<T>(left.x * right, left.y * right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle2<T>
    operator*(const T left, const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(left * right.x, left *right.y))) {
        return Angle2<T>(left * right.x, left * right.y);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle2<T> &
    operator*=(Angle2<T> &left, const T right) noexcept(
        noexcept(left.x *= right) && noexcept(left.y *= right)) {
        left.x *= right;
        left.y *= right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle2<T>
    operator/(const Angle2<T> &left, const T right) noexcept(
        noexcept(Angle2<T>(left.x / right, left.y / right))) {
        return Angle2<T>(left.x / right, left.y / right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle2<T> &operator/=(Angle2<T> &left, const T right) noexcept(
        noexcept(left.x /= right) && noexcept(left.y /= right)) {
        left.x /= right;
        left.y / right;
        return left;
    }
}
