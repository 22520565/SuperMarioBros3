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
// *. This header file has been altered after copying from origin!
//
////////////////////////////////////////////////////////////

#pragma once

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Class template for manipulating 2-dimensional vectors.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    class Vector2 {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        T x = T(); // X coordinate of the vector.
        T y = T(); // Y coordinate of the vector.

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a Vector2(0, 0).
        ///
        ////////////////////////////////////////////////////////////
        constexpr Vector2() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the vector2 from cartesian coordinates
        ///
        /// \param x: X coordinate.
        /// \param y: Y coordinate.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit(false) Vector2(const T x, const T y) noexcept(
            noexcept(T(x)) && noexcept(T(y)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the vector from another type of vector.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param vector2: Vector2 to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <typename U>
        constexpr explicit Vector2(const Vector2<U> &vector2) noexcept(
            noexcept(T(static_cast<T>(vector2.x))) && noexcept(T(static_cast<T>(vector2.y))));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the vector from another type of vector.
        ///
        /// This constructor doesn't replace the move constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param vector2: Vector2 to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <typename U>
        constexpr explicit Vector2(Vector2<U> &&vector2) noexcept(
            noexcept(T(static_cast<T>(vector2.x))) && noexcept(T(static_cast<T>(vector2.y))));

        ////////////////////////////////////////////////////////////
        /// \brief Overload of binary operator ==
        ///
        /// This operator compares strict equality between two vectors.
        ///
        /// \note Since C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (a vector).
        /// \param right: Right operand (a vector).
        ///
        /// \return True if \a left is equal to \a right.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr bool
        operator==(const Vector2<T> &left, const Vector2<T> &right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get a Vector2 of (0, 0).
        ///
        /// \return A Vector2 of (0, 0).
        ///
        ////////////////////////////////////////////////////////////
        static constexpr Vector2<T> zero() noexcept(
            noexcept(Vector2<T>(static_cast<T>(0), static_cast<T>(0))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Vector2 of (1, 1).
        ///
        /// \return A Vector2 of (1, 1).
        ///
        ////////////////////////////////////////////////////////////
        static constexpr Vector2<T> one() noexcept(
            noexcept(Vector2<T>(static_cast<T>(1), static_cast<T>(1))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Vector2 of (1, 0).
        ///
        /// \return A Vector2 of (1, 0).
        ///
        ////////////////////////////////////////////////////////////
        static constexpr Vector2<T> unitX() noexcept(
            noexcept(Vector2<T>(static_cast<T>(1), static_cast<T>(0))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Vector2 of (0, 1).
        ///
        /// \return A Vector2 of (0, 1).
        ///
        ////////////////////////////////////////////////////////////
        static constexpr Vector2<T> unitY() noexcept(
            noexcept(Vector2<T>(static_cast<T>(0), static_cast<T>(1))));
    };

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator +
    ///
    /// \param left:  Left operand (a vector).
    /// \param right: Right operand (a vector).
    ///
    /// \return Memberwise addition of both vectors.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    [[nodiscard]]
    constexpr Vector2<T>
    operator+(const Vector2<T> &left, const Vector2<T> &right) noexcept(
        noexcept(Vector2<T>(left.x + right.x, left.y + right.y)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator +=
    ///
    /// This operator performs a memberwise addition of both vectors,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (a vector).
    /// \param right: Right operand (a vector).
    ///
    /// \return Const-reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    constexpr const Vector2<T> &
    operator+=(Vector2<T> &left, const Vector2<T> &right) noexcept(
        noexcept(left.x += right.x) && noexcept(left.y += right.y));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of unary operator -
    ///
    /// \param right: Vector to negate.
    ///
    /// \return Memberwise opposite of the vector.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    [[nodiscard]]
    constexpr Vector2<T>
    operator-(const Vector2<T> &right) noexcept(noexcept(Vector2<T>(-right.x, -right.y)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator -
    ///
    /// \param left: Left operand (a vector).
    /// \param right: Right operand (a vector).
    ///
    /// \return Memberwise subtraction of both vectors.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    [[nodiscard]]
    constexpr Vector2<T>
    operator-(const Vector2<T> &left, const Vector2<T> &right) noexcept(
        noexcept(Vector2<T>(left.x - right.x, left.y - right.y)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator -=
    ///
    /// This operator performs a memberwise subtraction of both vectors,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (a vector).
    /// \param right: Right operand (a vector).
    ///
    /// \return Reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    constexpr const Vector2<T> &
    operator-=(Vector2<T> &left, const Vector2<T> &right) noexcept(
        noexcept(left.x -= right.x) && noexcept(left.y -= right.y));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *
    ///
    /// \param left: Left operand (a vector).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Memberwise multiplication by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    [[nodiscard]]
    constexpr Vector2<T>
    operator*(const Vector2<T> &left, const T right) noexcept(
        noexcept(Vector2<T>(left.x * right, left.y *right)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *
    ///
    /// \param left: Left operand (a scalar value).
    /// \param right: Right operand (a vector).
    ///
    /// \return Memberwise multiplication by \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    [[nodiscard]]
    constexpr Vector2<T>
    operator*(const T left, const Vector2<T> &right) noexcept(
        noexcept(Vector2<T>(left * right.x, left *right.y)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *=
    ///
    /// This operator performs a memberwise multiplication by \a right,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (a vector).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    constexpr const Vector2<T> &
    operator*=(Vector2<T> &left, const T right) noexcept(
        noexcept(left.x *= right) && noexcept(left.y *= right));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator /
    ///
    /// \note Avoid 0 in the right operand.
    ///
    /// \param left: Left operand (a vector).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Memberwise division by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    [[nodiscard]]
    constexpr Vector2<T>
    operator/(const Vector2<T> &left, const T right) noexcept(
        noexcept(Vector2<T>(left.x / right, left.y / right)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator /=
    ///
    /// \note Avoid 0 in the right operand.
    ///
    /// This operator performs a memberwise division by \a right,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (a vector).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    constexpr const Vector2<T> &
    operator/=(Vector2<T> &left, const T right) noexcept(
        noexcept(left.x /= right) && noexcept(left.y /= right));
}

#include "Vector2.inl"
