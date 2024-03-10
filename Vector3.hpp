////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
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
//
// *. This header file has been altered after copying from origin!
//
////////////////////////////////////////////////////////////

#pragma once
#include "Vector2.hpp"
#include "stdfloat"
#include <cstdint>
#include <type_traits>

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Class template for manipulating 3-dimensional vectors.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    class Vector3 : public Vector2<T> {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        T z = T(); // Z coordinate of the vector.

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a Vector3(0, 0, 0).
        ///
        ////////////////////////////////////////////////////////////
        constexpr Vector3() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the vector3 from cartesian coordinates.
        ///
        /// \param x: X coordinate.
        /// \param y: Y coordinate.
        /// \param z: Z coordinate.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit(false) Vector3(const T x, const T y, const T z) noexcept(
            noexcept(Vector2<T>(x, y)) && noexcept(T(z)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct a vector3 from a vector2.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Vector3(const Vector2<T> &vector2) noexcept(
            noexcept(Vector2<T>(vector2)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct a vector3 from a vector2 with Z coordinate.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Vector3<T>(const Vector2<T> &vector2, const T z) noexcept(
            noexcept(Vector2<T>(vector2)) && noexcept(T(z)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the vector from another type of vector.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param vector3: Vector3 to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <typename U>  requires std::is_arithmetic_v<U>
        constexpr explicit Vector3<T>(const Vector3<U> &vector3) noexcept(
            noexcept(Vector2<T>(vector3)) && noexcept(T(static_cast<T>(vector3.z))));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the vector from another type of vector.
        ///
        /// This constructor doesn't replace the move constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param vector3: Vector3 to convert.
        ////////////////////////////////////////////////////////////
        template <typename U>  requires std::is_arithmetic_v<U>
        constexpr explicit Vector3<T>(Vector3<U> &&vector3) noexcept(
            noexcept(Vector2<T>(vector3)) && noexcept(T(static_cast<T>(vector3.z))));

        ////////////////////////////////////////////////////////////
        /// \brief Overload of binary operator ==
        ///
        /// This operator compares strict equality between two vectors.
        ///
        /// \note In C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
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
        operator==(const Vector3<T> &left, const Vector3<T> &right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get a Vector3 of (0, 0, 0).
        ///
        /// \return A Vector3 of (0, 0, 0).
        ///
        ////////////////////////////////////////////////////////////
        static constexpr Vector3<T> zero() noexcept(
            noexcept(Vector3<T>(Vector2<T>::zero(), static_cast<T>(0))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Vector3 of (1, 1, 1).
        ///
        /// \return A Vector3 of (1, 1, 1).
        ///
        ////////////////////////////////////////////////////////////
        static constexpr Vector3<T> one() noexcept(
            noexcept(Vector3<T>(Vector2<T>::one(), static_cast<T>(1))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Vector3 of (1, 0, 0).
        ///
        /// \return A Vector3 of (1, 0, 0).
        ///
        ////////////////////////////////////////////////////////////
        static constexpr Vector3<T> unitX() noexcept(
            noexcept(Vector3<T>(Vector2<T>::unitX(), static_cast<T>(0))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Vector3 of (0, 1, 0).
        ///
        /// \return A Vector3 of (0, 1, 0).
        ///
        ////////////////////////////////////////////////////////////
        static constexpr Vector3<T> unitY() noexcept(
            noexcept(Vector3<T>(Vector2<T>::unitY(), static_cast<T>(0))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Vector3 of (0, 0, 1).
        ///
        /// \return A Vector3 of (0, 0, 1).
        ///
        ////////////////////////////////////////////////////////////
        static constexpr Vector3<T> unitZ() noexcept(
            noexcept(Vector3<T>(Vector2<T>::zero(), static_cast<T>(1))));
    };

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator +
    ///
    /// \param left: Left operand (a vector).
    /// \param right: Right operand (a vector).
    ///
    /// \return Memberwise addition of both vectors.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]]
    constexpr Vector3<T>
    operator+(const Vector3<T> &left, const Vector3<T> &right) noexcept(
        noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) + static_cast<const Vector2<T> &>(right),
                            left.z + right.z)));

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
        requires std::is_arithmetic_v<T>
    constexpr const Vector3<T> &operator+=(Vector3<T> &left, const Vector3<T> &right) noexcept(
        noexcept(static_cast<Vector2<T> &>(left) += static_cast<const Vector2<T> &>(right))
            && noexcept(left.z += right.z));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of unary operator -
    ///
    /// \param right: Vector to negate.
    ///
    /// \return Memberwise opposite of the vector.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]]
    constexpr Vector3<T>
    operator-(const Vector3<T> &right) noexcept(
        noexcept(Vector3<T>(-static_cast<const Vector2<T> &>(right), -right.z)));

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
        requires std::is_arithmetic_v<T>
    [[nodiscard]]
    constexpr Vector3<T>
    operator-(const Vector3<T> &left, const Vector3<T> &right) noexcept(
        noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) - static_cast<const Vector2<T> &>(right),
                            left.z - right.z)));

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
        requires std::is_arithmetic_v<T>
    constexpr const Vector3<T> &operator-=(Vector3<T> &left, const Vector3<T> &right) noexcept(
        noexcept(static_cast<Vector2<T> &>(left) -= static_cast<const Vector2<T> &>(right))
            && noexcept(left.z -= right.z));

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
        requires std::is_arithmetic_v<T>
    [[nodiscard]]
    constexpr Vector3<T>
    operator*(const Vector3<T> &left, const T right) noexcept(
        noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) * right, left.z *right)));

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
        requires std::is_arithmetic_v<T>
    [[nodiscard]]
    constexpr Vector3<T>
    operator*(const T left, const Vector3<T> &right) noexcept(
        noexcept(Vector3<T>(left * static_cast<const Vector2<T> &>(right), left *right.z)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *=
    ///
    /// This operator performs a memberwise multiplication by \a right,
    /// and assigns the result to \a left.
    ///
    /// \param left:  Left operand (a vector).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Reference to \a left.
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr const Vector3<T> &operator*=(Vector3<T> &left, const T right) noexcept(
        noexcept(static_cast<Vector2<T> &>(left) *= right) && noexcept(left.z *= right));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator /
    ///
    /// \param left:  Left operand (a vector).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Memberwise division by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]]
    constexpr Vector3<T>
    operator/(const Vector3<T> &left, const T right) noexcept(
        noexcept(Vector3<T>(static_cast<const Vector2<T> &>(left) / right, left.z / right)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator /=
    ///
    /// This operator performs a memberwise division by \a right,
    /// and assigns the result to \a left.
    ///
    /// \param left:  Left operand (a vector).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr const Vector3<T> &operator/=(Vector3<T> &left, const T right) noexcept(
        noexcept(static_cast<Vector2<T> &>(left) /= right) && noexcept(left.z /= right));

    // Define common types

    using Vector3c = Vector3<char>;
    using Vector3uc = Vector3<unsigned char>;
    using Vector3s = Vector3<short>;
    using Vector3us = Vector3<unsigned short>;
    using Vector3i = Vector3<int>;
    using Vector3u = Vector3<unsigned>;
    using Vector3l = Vector3<long>;
    using Vector3ul = Vector3<unsigned long>;
    using Vector3ll = Vector3<long long>;
    using Vector3ull = Vector3<unsigned long long>;

    using Vector3i8 = Vector3<int8_t>;
    using Vector3il8 = Vector3<int_least8_t>;
    using Vector3if8 = Vector3<int_fast8_t>;
    using Vector3u8 = Vector3<uint8_t>;
    using Vector3ul8 = Vector3<uint_least8_t>;
    using Vector3uf8 = Vector3<uint_fast8_t>;
    using Vector3i16 = Vector3<int16_t>;
    using Vector3il16 = Vector3<int_least16_t>;
    using Vector3if16 = Vector3<int_fast16_t>;
    using Vector3u16 = Vector3<uint16_t>;
    using Vector3ul16 = Vector3<uint_least16_t>;
    using Vector3uf16 = Vector3<uint_fast16_t>;
    using Vector3i32 = Vector3<int32_t>;
    using Vector3il32 = Vector3<int_least32_t>;
    using Vector3if32 = Vector3<int_fast32_t>;
    using Vector3u32 = Vector3<uint32_t>;
    using Vector3ul32 = Vector3<uint_least32_t>;
    using Vector3uf32 = Vector3<uint_fast32_t>;
    using Vector3i64 = Vector3<int64_t>;
    using Vector3il64 = Vector3<int_least64_t>;
    using Vector3if64 = Vector3<int_fast64_t>;
    using Vector3u64 = Vector3<uint64_t>;
    using Vector3ul64 = Vector3<uint_least64_t>;
    using Vector3uf64 = Vector3<uint_fast64_t>;

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
    using Vector3ld = Vector3<long double>;
    using Vector3f16 = Vector3<std::float16_t>;
    using Vector3bf16 = Vector3<std::bfloat16_t>;
    using Vector3f32 = Vector3<std::float32_t>;
    using Vector3f64 = Vector3<std::float64_t>;
    using Vector3f128 = Vector3<std::float128_t>;
}

#include "Vector3.inl"
