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
#include "Vector3.hpp"
#include <cmath>
#include <compare>
#include <concepts>
#include <numbers>
#include <type_traits>
#include <windows.h>

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Represents an angle value.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    class Angle final {
      public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Sets the angle value to zero.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Angle() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the angle from another type of angle.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param angle: Angle to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <std::floating_point U>
        constexpr explicit(false) Angle(const Angle<U> &angle) noexcept(
            noexcept(T(static_cast<T>(angle.asDegrees()))));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the angle from another type of angle.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param angle: Angle to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <std::floating_point U>
        constexpr explicit(false) Angle(Angle<U> &&angle) noexcept(
            noexcept(T(static_cast<T>(angle.asDegrees()))));

        ////////////////////////////////////////////////////////////
        /// \brief Construct an angle value from a number of degrees
        ///
        /// \param angle Number of degrees
        ///
        /// \return Angle value constructed from the number of degrees
        ///
        /// \see radians
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        static constexpr Angle<T> degrees(const T angle) noexcept(
            noexcept(Angle<T>(angle)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct an angle value from a number of degrees
        ///
        /// \param angle Number of degrees
        ///
        /// \return Angle value constructed from the number of degrees
        ///
        /// \see radians
        ///
        ////////////////////////////////////////////////////////////
        template <std::integral U>
        [[nodiscard]]
        static constexpr Angle<T> degrees(const U angle) noexcept(
            noexcept(Angle<T>(static_cast<T>(angle))));

        ////////////////////////////////////////////////////////////
        /// \brief Construct an angle value from a number of radians
        ///
        /// \param angle Number of radians
        ///
        /// \return Angle value constructed from the number of radians
        ///
        /// \see degrees
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        static constexpr Angle<T> radians(const T angle) noexcept(
            noexcept(Angle<T>(angle * (static_cast<T>(180.0) / std::numbers::pi_v<T>))));

        ////////////////////////////////////////////////////////////
        /// \brief Construct an angle value from a number of radians
        ///
        /// \param angle Number of radians
        ///
        /// \return Angle value constructed from the number of radians
        ///
        /// \see degrees
        ///
        ////////////////////////////////////////////////////////////
        template <std::integral U>
        [[nodiscard]]
        static constexpr Angle<T> radians(const U angle) noexcept(
            noexcept(Angle<T>(static_cast<T>(angle) * (static_cast<T>(180.0) / std::numbers::pi_v<T>))));

        ////////////////////////////////////////////////////////////
        /// \brief Return the angle's value in degrees.
        ///
        /// \return Angle in degrees.
        ///
        /// \see asRadians.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const T &asDegrees() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Return the angle's value in radians
        ///
        /// \return Angle in radians
        ///
        /// \see asDegrees
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr T asRadians() const noexcept(
            noexcept(amountDegrees * (std::numbers::pi_v<T> / static_cast<T>(180.0))));

        ////////////////////////////////////////////////////////////
        /// \brief Wrap to a range such that -180° <= angle < 180°
        ///
        /// Similar to a modulo operation, this returns a copy of the angle
        /// constrained to the range [-180°, 180°) == [-Pi, Pi).
        /// The resulting angle represents a rotation which is equivalent to *this.
        ///
        /// \return Signed angle, wrapped to [-180°, 180°)
        ///
        /// \see wrapUnsigned
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Angle<T> wrapSigned() const noexcept(
            noexcept(Angle<T>(std::fmod(amountDegrees + static_cast<T>(180.0F), static_cast<T>(360.0F)) -
                              static_cast<T>(180.0F))));

        ////////////////////////////////////////////////////////////
        /// \brief Wrap to a range such that 0° <= angle < 360°
        ///
        /// Similar to a modulo operation, this returns a copy of the angle
        /// constrained to the range [0°, 360°) == [0, Tau) == [0, 2*Pi).
        /// The resulting angle represents a rotation which is equivalent to *this.
        ///
        /// \return Unsigned angle, wrapped to [0°, 360°)
        ///
        /// \see wrapSigned
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Angle<T> wrapUnsigned() const noexcept(
            noexcept(Angle<T>(std::fmod(amountDegrees, static_cast<T>(360.0)))));

        ////////////////////////////////////////////////////////////
        /// \relates Angle
        /// \brief Overload of <=> operator to compare two angle values.
        ///
        /// \param left: Left operand (an angle).
        /// \param right: Right operand (an angle).
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr std::partial_ordering
        operator<=>(Angle<T> left, Angle<T> right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get an Angle of 0.
        ///
        /// \return An angle of 0.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        static consteval Angle<T> zero() noexcept(noexcept(Angle<T>()));

        ////////////////////////////////////////////////////////////
        /// \brief Get an Angle of 1.0_deg.
        ///
        /// \return An angle of 1.0_deg.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        static consteval Angle<T> one_deg() noexcept(noexcept(Angle<T>::degrees(1.0)));

        ////////////////////////////////////////////////////////////
        /// \brief Get an Angle of 1.0_rad.
        ///
        /// \return An angle of 1.0_rad.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        static consteval Angle<T> one_rad() noexcept(noexcept(Angle<T>::radians(1.0)));

      private:
        ////////////////////////////////////////////////////////////
        /// \brief Construct from a number of degrees.
        ///
        /// This function is internal. To construct angle values,
        /// use game::radians or game::degrees instead.
        ///
        /// \param degrees: Angle in degrees.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Angle(const T degrees) noexcept : amountDegrees(degrees) {}

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        T amountDegrees = T(); // Angle value stored as degrees
    };

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary + operator to add two angle values.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Sum of the two angle values.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle<T>
    operator+(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(Angle<T>::degrees(left.asDegrees() + right.asDegrees())));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary += operator to add/assign two angle values.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Sum of the two angle values.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator+=(Angle<T> &left, const Angle<T> right) noexcept(
        noexcept(left = (left + right)));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of unary - operator to negate an angle value.
    ///
    /// Represents a rotation in the opposite direction.
    ///
    /// \param right: Right operand (an angle).
    ///
    /// \return Negative of the angle value.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle<T>
    operator-(const Angle<T> right) noexcept(noexcept(Angle<T>::degrees(-right.asDegrees())));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary - operator to subtract two angle values.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Difference of the two angle values.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle<T>
    operator-(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(Angle<T>::degrees(left.asDegrees() - right.asDegrees())));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary -= operator to subtract/assign two angle values.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Difference of the two angle values.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator-=(Angle<T> &left, const Angle<T> right) noexcept(
        noexcept(left = (left - right)));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary * operator to scale an angle value.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left multiplied by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle<T>
    operator*(const Angle<T> left, const T right) noexcept(
        noexcept(Angle<T>::degrees(left.asDegrees() * right)));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary * operator to scale an angle value.
    ///
    /// \param left: Left operand (a number).
    /// \param right: Right operand (an angle).
    ///
    /// \return \a left multiplied by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle<T>
    operator*(const T left, const Angle<T> right) noexcept(noexcept(right * left));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary *= operator to scale/assign an angle value.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left multiplied by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator*=(Angle<T> &left, const T right) noexcept(
        noexcept(left = (left * right)));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary / operator to scale an angle value.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left divided by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle<T>
    operator/(const Angle<T> left, const T right) noexcept(
        noexcept(Angle<T>::degrees(left.asDegrees() / right)));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary /= operator to scale/assign an angle value.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left divided by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator/=(Angle<T> &left, const T right) noexcept(
        noexcept(left = (left / right)));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary / operator to compute the ratio of two angle values.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return \a left divided by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr T
    operator/(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(left.asDegrees() / right.asDegrees()));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary % operator to compute modulo of an angle value.
    ///
    /// Right hand angle must be greater than zero.
    ///
    /// Examples:
    /// \code
    /// degrees(90) % degrees(40)  // 10 degrees
    /// degrees(-90) % degrees(40) // 30 degrees (not -10)
    /// \endcode
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return \a left modulo \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle<T>
    operator%(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(Angle<T>::degrees(std::fmod(left.asDegrees(), right.asDegrees()))));

    ////////////////////////////////////////////////////////////
    /// \relates Angle
    /// \brief Overload of binary %= operator to compute/assign remainder of an angle value
    ///
    /// \param left: Left operand (an angle)
    /// \param right: Right operand (an angle)
    ///
    /// \return \a left modulo \a right
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator%=(Angle<T> &left, const Angle<T> right) noexcept(
        noexcept(left = (left % right)));

    inline namespace literals {
        ////////////////////////////////////////////////////////////
        /// \brief User defined literal for angles in degrees, e.g. 10.5_deg.
        ///
        /// \param angle Angle in degrees.
        ///
        /// \return \a Angle.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        consteval Angle<long double>
        operator""_deg(const long double angle) noexcept(
            noexcept(Angle<long double>::degrees(angle)));

        ////////////////////////////////////////////////////////////
        /// \relates sf::Angle
        /// \brief User defined literal for angles in degrees, e.g. 90_deg
        ///
        /// \param angle Angle in degrees
        ///
        /// \return \a Angle
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        consteval Angle<long double>
        operator""_deg(const unsigned long long int angle) noexcept(
            noexcept(Angle<long double>::degrees(angle)));

        ////////////////////////////////////////////////////////////
        /// \brief User defined literal for angles in radians, e.g. 0.1_rad.
        ///
        /// \param angle Angle in radians.
        ///
        /// \return \a Angle.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        consteval Angle<long double>
        operator""_rad(const long double angle) noexcept(
            noexcept(Angle<long double>::radians(angle)));

        ////////////////////////////////////////////////////////////
        /// \relates sf::Angle
        /// \brief User defined literal for angles in radians, e.g. 2_rad
        ///
        /// \param angle Angle in radians
        ///
        /// \return \a Angle
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        consteval Angle<long double>
        operator""_rad(const unsigned long long int angle) noexcept(
            noexcept(Angle<long double>::radians(angle)));
    }
}

#include "Angle.inl"
