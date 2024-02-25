// Copyright (C) 2007-2023 Laurent Gomila (laurent@sfml-dev.org)
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
// * This header file has been altered after copying from origin!

#pragma once
#include "Vector2.hpp"
namespace game {
    template <class T>
    struct Vector3 : Vector2<T> {
      public:
        // Z coordinate of the vector
        T z = T();

        /// \brief Default constructor.
        constexpr Vector3<T>() = default;

        /// \brief Construct a vector3 from its coordinates.
        constexpr explicit Vector3<T>(const T x, const T y, const T z) noexcept(
            noexcept(Vector2<T>(x, y)) && noexcept(T(z))) : Vector2<T>(x, y), z(z) {}

        /// \brief Construct a vector3 from a vector2.
        constexpr explicit Vector3<T>(const Vector2<T> &vector2) noexcept(
            noexcept(Vector2<T>(vector2))) : Vector2<T>(vector2) {}

        /// \brief Construct a vector3 from a vector2 with Z coordinate.
        constexpr explicit Vector3<T>(const Vector2<T> &vector2, const T z) noexcept(
            noexcept(Vector2<T>(vector2)) && noexcept(T(z))) : Vector2<T>(vector2), z(z) {}

        ///\brief Construct the vector from another type of vector.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param vector3: Vector3 to convert
        template <typename U>
        constexpr explicit Vector3<T>(const Vector3<U> &vector3) noexcept(
            noexcept(Vector2<T>(vector3)) && noexcept(T(static_cast<T>(vector3.z))))
            : Vector2<T>(vector3), z(static_cast<T>(vector3.z)) {}

        ///\brief Construct the vector from another type of vector.
        ///
        /// This constructor doesn't replace the move constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param vector3: Vector3 to convert
        template <typename U>
        constexpr explicit Vector3<T>(Vector3<U> &&vector3) noexcept(
            noexcept(Vector2<T>(vector3)) && noexcept(T(static_cast<T>(vector3.z))))
            : Vector2<T>(vector3), z(static_cast<T>(vector3.z)) {}

        /// \brief Overload of binary operator ==
        ///
        /// This operator compares strict equality between two vectors.
        ///
        /// \note In C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Hence, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left:  Left operand (a vector)
        /// \param right: Right operand (a vector)
        ///
        /// \return True if \a left is equal to \a right
        [[nodiscard("Use the result of this comparison or remove this redundant comparison!")]]
        friend constexpr bool
        operator==(const Vector3<T> &left, const Vector3<T> &right) = default;

        /// \brief Overload of binary operator +
        ///
        /// \param left:  Left operand (a vector)
        /// \param right: Right operand (a vector)
        ///
        /// \return Memberwise addition of both vectors
        [[nodiscard("Use the result of this calculation or remove this redundant calculation!")]]
        friend constexpr Vector3<T>
        operator+(const Vector3<T> &left, const Vector3<T> &right) noexcept(
            noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) + static_cast<const Vector2<T> &>(right),
                                left.z + right.z))) {
            return Vector3<T>(static_cast<const Vector2<T> &>(left) + static_cast<const Vector2<T> &>(right),
                              left.z + right.z);
        }

        /// \brief Overload of binary operator +=
        ///
        /// This operator performs a memberwise addition of both vectors,
        /// and assigns the result to \a left.
        ///
        /// \param left:  Left operand (a vector)
        /// \param right: Right operand (a vector)
        ///
        /// \return Const-reference to \a left
        friend constexpr const Vector3<T> &operator+=(Vector3<T> &left, const Vector3<T> &right) noexcept(
            noexcept(static_cast<Vector2<T> &>(left) += static_cast<const Vector2<T> &>(right))
                && noexcept(left.z += right.z)) {
            static_cast<Vector2<T> &>(left) += static_cast<const Vector2<T> &>(right);
            left.z += right.z;
            return left;
        }

        /// \brief Overload of unary operator -
        ///
        /// \param right: Vector to negate
        ///
        /// \return Memberwise opposite of the vector
        [[nodiscard("Use the result of this calculation or remove this redundant calculation!")]]
        friend constexpr Vector3<T>
        operator-(const Vector3<T> &right) noexcept(
            noexcept(Vector3<T>(-static_cast<const Vector2<T> &>(right), -right.z))) {
            return Vector3<T>(-static_cast<const Vector2<T> &>(right), -right.z);
        }

        /// \brief Overload of binary operator -
        ///
        /// \param left:  Left operand (a vector)
        /// \param right: Right operand (a vector)
        ///
        /// \return Memberwise subtraction of both vectors
        [[nodiscard("Use the result of this calculation or remove this redundant calculation!")]]
        friend constexpr Vector3<T>
        operator-(const Vector3<T> &left, const Vector3<T> &right) noexcept(
            noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) - static_cast<const Vector2<T> &>(right),
                                left.z - right.z))) {
            return Vector3<T>(static_cast<const Vector2<T> &>(left) - static_cast<const Vector2<T> &>(right),
                              left.z - right.z);
        }

        /// \brief Overload of binary operator -=
        ///
        /// This operator performs a memberwise subtraction of both vectors,
        /// and assigns the result to \a left.
        ///
        /// \param left:  Left operand (a vector)
        /// \param right: Right operand (a vector)
        ///
        /// \return Reference to \a left
        friend constexpr const Vector3<T> &operator-=(Vector3<T> &left, const Vector3<T> &right) noexcept(
            noexcept(static_cast<Vector2<T> &>(left) -= static_cast<const Vector2<T> &>(right))
                && noexcept(left.z -= right.z)) {
            static_cast<Vector2<T> &>(left) -= static_cast<const Vector2<T> &>(right);
            left.z -= right.z;
            return left;
        }

        /// \brief Overload of binary operator *
        ///
        /// \param left:  Left operand (a vector)
        /// \param right: Right operand (a scalar value)
        ///
        /// \return Memberwise multiplication by \a right
        [[nodiscard("Use the result of this calculation or remove this redundant calculation!")]]
        friend constexpr Vector3<T>
        operator*(const Vector3<T> &left, const T right) noexcept(
            noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) * right, left.z *right))) {
            return Vector3<T>(static_cast<const Vector2<T> &>(left) * right, left.z * right);
        }

        /// \brief Overload of binary operator *
        ///
        /// \param left:  Left operand (a scalar value)
        /// \param right: Right operand (a vector)
        ///
        /// \return Memberwise multiplication by \a left
        [[nodiscard("Use the result of this calculation or remove this redundant calculation!")]]
        friend constexpr Vector3<T>
        operator*(const T left, const Vector3<T> &right) noexcept(
            noexcept(Vector3<T>(left * static_cast<const Vector2<T> &>(right), left *right.z))) {
            return Vector3<T>(left * static_cast<const Vector2<T> &>(right), left * right.z);
        }

        /// \brief Overload of binary operator *=
        ///
        /// This operator performs a memberwise multiplication by \a right,
        /// and assigns the result to \a left.
        ///
        /// \param left:  Left operand (a vector)
        /// \param right: Right operand (a scalar value)
        ///
        /// \return Reference to \a left
        friend constexpr const Vector3<T> &operator*=(Vector3<T> &left, const T right) noexcept(
            noexcept(static_cast<Vector2<T> &>(left) *= right) && noexcept(left.z *= right)) {
            static_cast<Vector2<T> &>(left) *= right;
            left.z *= right;
            return left;
        }

        /// \brief Overload of binary operator /
        ///
        /// \param left:  Left operand (a vector)
        /// \param right: Right operand (a scalar value)
        ///
        /// \return Memberwise division by \a right
        [[nodiscard("Use the result of this calculation or remove this redundant calculation!")]]
        friend constexpr Vector3<T>
        operator/(const Vector3<T> &left, const T right) noexcept(
            noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) / right, left.z / right))) {
            return Vector3<T>(static_cast<const Vector2<T> &>(left) / right, left.z / right);
        }

        /// \brief Overload of binary operator /=
        ///
        /// This operator performs a memberwise division by \a right,
        /// and assigns the result to \a left.
        ///
        /// \param left:  Left operand (a vector)
        /// \param right: Right operand (a scalar value)
        ///
        /// \return Reference to \a left
        friend constexpr const Vector3<T> &operator/=(Vector3<T> &left, const T right) noexcept(
            noexcept(static_cast<Vector2<T> &>(left) /= right) && noexcept(left.z /= right)) {
            static_cast<Vector2<T> &>(left) /= right;
            left.z /= right;
            return left;
        }
    };
}
