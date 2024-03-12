#include "Angle2.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T>::Angle2(const Angle<T> x, const Angle<T> y) noexcept(
        noexcept(Angle<T>(x)) && noexcept(Angle<T>(y))) : x(x), y(y) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    template <std::floating_point U>
    constexpr Angle2<T>::Angle2(const Angle2<U> &angle2) noexcept(
        noexcept(Angle<T>(static_cast<Angle<T>>(angle2.x)))
            && noexcept(Angle<T>(static_cast<Angle<T>>(angle2.y))))
        : x(static_cast<Angle<T>>(angle2.x)), y(static_cast<T>(angle2.y)) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    template <std::floating_point U>
    constexpr Angle2<T>::Angle2(Angle2<U> &&angle2) noexcept(
        noexcept(Angle<T>(static_cast<Angle<T>>(angle2.x)))
            && noexcept(Angle<T>(static_cast<Angle<T>>(angle2.y))))
        : x(static_cast<Angle<T>>(angle2.x)), y(static_cast<T>(angle2.y)) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T> Angle2<T>::wrapSigned() const noexcept(
        noexcept(Angle2<T>(this->x.wrapSigned(), this->y.wrapSigned()))) {
        return Angle2<T>(this->x.wrapSigned(), this->y.wrapSigned());
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T> Angle2<T>::wrapUnsigned() const noexcept(
        noexcept(Angle2<T>(this->x.wrapUnsigned(), this->y.wrapUnsigned()))) {
        return Angle2<T>(this->x.wrapUnsigned(), this->y.wrapUnsigned());
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    consteval Angle2<T> Angle2<T>::zero() noexcept(noexcept(Angle2<T>(0.0_deg, 0.0_deg))) {
        return Angle2<T>(0.0_deg, 0.0_deg);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    consteval Angle2<T> Angle2<T>::one_deg() noexcept(noexcept(Angle2<T>(1.0_deg, 1.0_deg))) {
        return Angle2<T>(1.0_deg, 1.0_deg);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    consteval Angle2<T> Angle2<T>::unitX_deg() noexcept(noexcept(Angle2<T>(1.0_deg, 0.0_deg))) {
        return Angle2<T>(1.0_deg, 0.0_deg);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    consteval Angle2<T> Angle2<T>::unitY_deg() noexcept(noexcept(Angle2<T>(0.0_deg, 1.0_deg))) {
        return Angle2<T>(0.0_deg, 1.0_deg);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    consteval Angle2<T> Angle2<T>::one_rad() noexcept(noexcept(Angle2<T>(1.0_rad, 1.0_rad))) {
        return Angle2<T>(1.0_rad, 1.0_rad);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    consteval Angle2<T> Angle2<T>::unitX_rad() noexcept(noexcept(Angle2<T>(1.0_rad, 0.0_rad))) {
        return Angle2<T>(1.0_rad, 0.0_rad);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    consteval Angle2<T> Angle2<T>::unitY_rad() noexcept(noexcept(Angle2<T>(0.0_rad, 1.0_rad))) {
        return Angle2<T>(0.0_rad, 1.0_rad);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T> operator+(const Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(left.x + right.x, left.y + right.y))) {
        return Angle2<T>(left.x + right.x, left.y + right.y);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle2<T> &operator+=(Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(left.x += right.x) && noexcept(left.y += right.y)) {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T> operator-(const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(-right.x, -right.y))) {
        return Angle2<T>(-right.x, -right.y);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T> operator-(const Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(left.x - right.x, left.y - right.y))) {
        return Angle2<T>(left.x - right.x, left.y - right.y);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle2<T> &operator-=(Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(left.x -= right.x) && noexcept(left.y -= right.y)) {
        left.x -= right.x;
        left.y -= right.y;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T>
    operator*(const Angle2<T> &left, const T right) noexcept(
        noexcept(Angle2<T>(left.x * right, left.y *right))) {
        return Angle2<T>(left.x * right, left.y * right);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T>
    operator*(const T left, const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(left * right.x, left *right.y))) {
        return Angle2<T>(left * right.x, left * right.y);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle2<T> &
    operator*=(Angle2<T> &left, const T right) noexcept(
        noexcept(left.x *= right) && noexcept(left.y *= right)) {
        left.x *= right;
        left.y *= right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle2<T>
    operator/(const Angle2<T> &left, const T right) noexcept(
        noexcept(Angle2<T>(left.x / right, left.y / right))) {
        return Angle2<T>(left.x / right, left.y / right);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle2<T> &operator/=(Angle2<T> &left, const T right) noexcept(
        noexcept(left.x /= right) && noexcept(left.y /= right)) {
        left.x /= right;
        left.y / right;
        return left;
    }
}
