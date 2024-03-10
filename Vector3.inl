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
#include "Vector3.hpp"
#include <type_traits>

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T>::Vector3(const T x, const T y, const T z) noexcept(
        noexcept(Vector2<T>(x, y)) && noexcept(T(z))) : Vector2<T>(x, y), z(z) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T>::Vector3(const Vector2<T> &vector2) noexcept(
        noexcept(Vector2<T>(vector2))) : Vector2<T>(vector2) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T>::Vector3(const Vector2<T> &vector2, const T z) noexcept(
        noexcept(Vector2<T>(vector2)) && noexcept(T(z))) : Vector2<T>(vector2), z(z) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    template <typename U> requires std::is_arithmetic_v<U>
    constexpr Vector3<T>::Vector3(const Vector3<U> &vector3) noexcept(
        noexcept(Vector2<T>(vector3)) && noexcept(T(static_cast<T>(vector3.z))))
        : Vector2<T>(vector3), z(static_cast<T>(vector3.z)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    template <typename U>  requires std::is_arithmetic_v<U>
    constexpr Vector3<T>::Vector3(Vector3<U> &&vector3) noexcept(
        noexcept(Vector2<T>(vector3)) && noexcept(T(static_cast<T>(vector3.z))))
        : Vector2<T>(vector3), z(static_cast<T>(vector3.z)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> Vector3<T>::zero() noexcept(noexcept(Vector3<T>(Vector2<T>::zero(), static_cast<T>(0)))) {
        return Vector3<T>(Vector2<T>::zero(), static_cast<T>(0));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> Vector3<T>::one() noexcept(noexcept(Vector3<T>(Vector2<T>::one(), static_cast<T>(1)))) {
        return Vector3<T>(Vector2<T>::one(), static_cast<T>(1));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> Vector3<T>::unitX() noexcept(noexcept(Vector3<T>(Vector2<T>::unitX(), static_cast<T>(0)))) {
        return Vector3<T>(Vector2<T>::unitX(), static_cast<T>(0));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> Vector3<T>::unitY() noexcept(noexcept(Vector3<T>(Vector2<T>::unitY(), static_cast<T>(0)))) {
        return Vector3<T>(Vector2<T>::unitY(), static_cast<T>(0));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> Vector3<T>::unitZ() noexcept(noexcept(Vector3<T>(Vector2<T>::zero(), static_cast<T>(1)))) {
        return Vector3<T>(Vector2<T>::zero(), static_cast<T>(1));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> operator+(const Vector3<T> &left, const Vector3<T> &right) noexcept(
        noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) + static_cast<const Vector2<T> &>(right),
                            left.z + right.z))) {
        return Vector3<T>(static_cast<const Vector2<T> &>(left) + static_cast<const Vector2<T> &>(right),
                          left.z + right.z);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr const Vector3<T> &operator+=(Vector3<T> &left, const Vector3<T> &right) noexcept(
        noexcept(static_cast<Vector2<T> &>(left) += static_cast<const Vector2<T> &>(right))
            && noexcept(left.z += right.z)) {
        static_cast<Vector2<T> &>(left) += static_cast<const Vector2<T> &>(right);
        left.z += right.z;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> operator-(const Vector3<T> &right) noexcept(
        noexcept(Vector3<T>(-static_cast<const Vector2<T> &>(right), -right.z))) {
        return Vector3<T>(-static_cast<const Vector2<T> &>(right), -right.z);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> operator-(const Vector3<T> &left, const Vector3<T> &right) noexcept(
        noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) - static_cast<const Vector2<T> &>(right),
                            left.z - right.z))) {
        return Vector3<T>(static_cast<const Vector2<T> &>(left) - static_cast<const Vector2<T> &>(right),
                          left.z - right.z);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr const Vector3<T> &operator-=(Vector3<T> &left, const Vector3<T> &right) noexcept(
        noexcept(static_cast<Vector2<T> &>(left) -= static_cast<const Vector2<T> &>(right))
            && noexcept(left.z -= right.z)) {
        static_cast<Vector2<T> &>(left) -= static_cast<const Vector2<T> &>(right);
        left.z -= right.z;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> operator*(const Vector3<T> &left, const T right) noexcept(
        noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) * right, left.z *right))) {
        return Vector3<T>(static_cast<const Vector2<T> &>(left) * right, left.z * right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> operator*(const T left, const Vector3<T> &right) noexcept(
        noexcept(Vector3<T>(left * static_cast<const Vector2<T> &>(right), left *right.z))) {
        return Vector3<T>(left * static_cast<const Vector2<T> &>(right), left * right.z);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr const Vector3<T> &operator*=(Vector3<T> &left, const T right) noexcept(
        noexcept(static_cast<Vector2<T> &>(left) *= right) && noexcept(left.z *= right)) {
        static_cast<Vector2<T> &>(left) *= right;
        left.z *= right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> operator/(const Vector3<T> &left, const T right) noexcept(
        noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) / right, left.z / right))) {
        return Vector3<T>(static_cast<const Vector2<T> &>(left) / right, left.z / right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr const Vector3<T> &operator/=(Vector3<T> &left, const T right) noexcept(
        noexcept(static_cast<Vector2<T> &>(left) /= right) && noexcept(left.z /= right)) {
        static_cast<Vector2<T> &>(left) /= right;
        left.z /= right;
        return left;
    }
}
