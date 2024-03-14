////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2024 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// *. This inline file has been altered after copying from origin!
//
////////////////////////////////////////////////////////////

#include "Vector2.hpp"
#include <type_traits>

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T>::Vector2(const T x, const T y) noexcept(
        noexcept(T(x)) && noexcept(T(y))) : x(x), y(y) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    template <typename U>
        requires std::is_arithmetic_v<U>
    constexpr Vector2<T>::Vector2(const Vector2<U> &vector2) noexcept(
        noexcept(T(static_cast<T>(vector2.x))) && noexcept(T(static_cast<T>(vector2.y))))
        : x(static_cast<T>(vector2.x)), y(static_cast<T>(vector2.y)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    consteval Vector2<T> Vector2<T>::zero() noexcept(
        noexcept(Vector2<T>(static_cast<T>(0), static_cast<T>(0)))) {
        return Vector2<T>(static_cast<T>(0), static_cast<T>(0));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    consteval Vector2<T> Vector2<T>::one() noexcept(
        noexcept(Vector2<T>(static_cast<T>(1), static_cast<T>(1)))) {
        return Vector2<T>(static_cast<T>(1), static_cast<T>(1));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    consteval Vector2<T> Vector2<T>::unitX() noexcept(
        noexcept(Vector2<T>(static_cast<T>(1), static_cast<T>(0)))) {
        return Vector2<T>(static_cast<T>(1), static_cast<T>(0));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    consteval Vector2<T> Vector2<T>::unitY() noexcept(
        noexcept(Vector2<T>(static_cast<T>(0), static_cast<T>(1)))) {
        return Vector2<T>(static_cast<T>(0), static_cast<T>(1));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> operator+(const Vector2<T> &left, const Vector2<T> &right) noexcept(
        noexcept(Vector2<T>(left.x + right.x, left.y + right.y))) {
        return Vector2<T>(left.x + right.x, left.y + right.y);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr const Vector2<T> &operator+=(Vector2<T> &left, const Vector2<T> &right) noexcept(
        noexcept(left.x += right.x) && noexcept(left.y += right.y)) {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> operator-(const Vector2<T> &right) noexcept(noexcept(Vector2<T>(-right.x, -right.y))) {
        return Vector2<T>(-right.x, -right.y);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> operator-(const Vector2<T> &left, const Vector2<T> &right) noexcept(
        noexcept(Vector2<T>(left.x - right.x, left.y - right.y))) {
        return Vector2<T>(left.x - right.x, left.y - right.y);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr const Vector2<T> &operator-=(Vector2<T> &left, const Vector2<T> &right) noexcept(
        noexcept(left.x -= right.x) && noexcept(left.y -= right.y)) {
        left.x -= right.x;
        left.y -= right.y;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> operator*(const Vector2<T> &left, const T right) noexcept(
        noexcept(Vector2<T>(left.x * right, left.y *right))) {
        return Vector2<T>(left.x * right, left.y * right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> operator*(const T left, const Vector2<T> &right) noexcept(
        noexcept(Vector2<T>(left * right.x, left *right.y))) {
        return Vector2<T>(left * right.x, left * right.y);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr const Vector2<T> &operator*=(Vector2<T> &left, const T right) noexcept(
        noexcept(left.x *= right) && noexcept(left.y *= right)) {
        left.x *= right;
        left.y *= right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> operator/(const Vector2<T> &left, const T right) noexcept(
        noexcept(Vector2<T>(left.x / right, left.y / right))) {
        return Vector2<T>(left.x / right, left.y / right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr const Vector2<T> &operator/=(Vector2<T> &left, const T right) noexcept(
        noexcept(left.x /= right) && noexcept(left.y /= right)) {
        left.x /= right;
        left.y /= right;
        return left;
    }
}
