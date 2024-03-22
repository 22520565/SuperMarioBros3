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
#include <chrono>
#include <cstdint>

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Represents a time value.
    ///
    ////////////////////////////////////////////////////////////
    class Time {
      public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Sets the time value to zero.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Time() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct from std::chrono::duration.
        ///
        ////////////////////////////////////////////////////////////
        template <typename Rep, typename Period>
        constexpr explicit(false) Time(const std::chrono::duration<Rep, Period> &duration) noexcept(
            noexcept(std::chrono::microseconds(std::chrono::duration<Rep, Period>())));

        ////////////////////////////////////////////////////////////
        /// \brief Return the time value as a number of seconds.
        ///
        /// \return Time in seconds.
        ///
        /// \see asMilliseconds, asMicroseconds.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr float asSeconds() const noexcept(
            noexcept(std::chrono::duration<float>().count()));

        ////////////////////////////////////////////////////////////
        /// \brief Return the time value as a number of milliseconds.
        ///
        /// \return Time in milliseconds.
        ///
        /// \see asSeconds, asMicroseconds.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr std::int32_t asMilliseconds() const noexcept(
            noexcept(std::chrono::duration_cast<std::chrono::duration<std::int32_t, std::milli>>(std::chrono::microseconds()).count()));

        ////////////////////////////////////////////////////////////
        /// \brief Return the time value as a number of microseconds.
        ///
        /// \return Time in microseconds.
        ///
        /// \see asSeconds, asMilliseconds.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr std::int64_t asMicroseconds() const noexcept(
            noexcept(std::chrono::microseconds().count()));

        ////////////////////////////////////////////////////////////
        /// \brief Return the time value as a std::chorono::duration.
        ///
        /// \return Time in microseconds.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const std::chrono::microseconds &toDuration() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Implicit conversion to std::chrono::duration.
        ///
        /// \return Duration in microseconds.
        ///
        ////////////////////////////////////////////////////////////
        template <typename Rep, typename Period>
        [[nodiscard]] constexpr explicit(false) operator std::chrono::duration<Rep, Period>() const noexcept;

        ////////////////////////////////////////////////////////////
        // Static member data
        ////////////////////////////////////////////////////////////
        // NOLINTNEXTLINE(readability-identifier-naming)
        static const Time zero; // Predefined "zero" time value.

      private:
        friend constexpr Time seconds(const float amount) noexcept(
            noexcept(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(amount))));
        friend constexpr Time milliseconds(const std::int32_t amount) noexcept(
            noexcept(std::chrono::milliseconds(amount)));
        friend constexpr Time microseconds(const std::int64_t amount) noexcept(
            noexcept(std::chrono::microseconds(amount)));

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        std::chrono::microseconds microsecondsAmount = std::chrono::microseconds(); // Time value stored as microseconds.
    };

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Construct a time value from a number of seconds.
    ///
    /// \param amount: Number of seconds.
    ///
    /// \return Time value constructed from the amount of seconds.
    ///
    /// \see milliseconds, microseconds.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time seconds(const float amount) noexcept(
        noexcept(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(amount))));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Construct a time value from a number of milliseconds.
    ///
    /// \param amount: Number of milliseconds.
    ///
    /// \return Time value constructed from the amount of milliseconds.
    ///
    /// \see seconds, microseconds.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time milliseconds(const std::int32_t amount) noexcept(
        noexcept(std::chrono::milliseconds(amount)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Construct a time value from a number of microseconds.
    ///
    /// \param amount: Number of microseconds.
    ///
    /// \return Time value constructed from the amount of microseconds.
    ///
    /// \see seconds, milliseconds.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time microseconds(const std::int64_t amount) noexcept(
        noexcept(std::chrono::microseconds(amount)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of <=> operator to compare two time values.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a time).
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr auto
    operator<=>(const Time left, const Time right) noexcept(
        noexcept(left.asMicroseconds() <=> right.asMicroseconds()));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of unary - operator to negate a time value.
    ///
    /// \param right: Right operand (a time).
    ///
    /// \return Opposite of the time value.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator-(const Time right) noexcept(
        noexcept(microseconds(-right.asMicroseconds())));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary + operator to add two time values.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a time).
    ///
    /// \return Sum of the two times values.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator+(const Time left, const Time right) noexcept(
        noexcept(microseconds(left.asMicroseconds() + right.asMicroseconds())));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary += operator to add/assign two time values.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a time).
    ///
    /// \return Sum of the two times values.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Time &operator+=(Time &left, const Time right) noexcept(
        noexcept(left = (left + right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary - operator to subtract two time values.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a time).
    ///
    /// \return Difference of the two times values.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator-(const Time left, const Time right) noexcept(
        noexcept(microseconds(left.asMicroseconds() - right.asMicroseconds())));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary -= operator to subtract/assign two time values.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a time).
    ///
    /// \return Difference of the two times values.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Time &operator-=(Time &left, const Time right) noexcept(
        noexcept(left = (left - right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary * operator to scale a time value.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left multiplied by \a right.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator*(const Time left, const float right) noexcept(
        noexcept(seconds(left.asSeconds() * right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary * operator to scale a time value.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left multiplied by \a right.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator*(Time left, std::int64_t right) noexcept(
        noexcept(microseconds(left.asMicroseconds() * right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary * operator to scale a time value.
    ///
    /// \param left: Left operand (a number).
    /// \param right: Right operand (a time).
    ///
    /// \return \a left multiplied by \a right.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator*(const float left, const Time right) noexcept(
        noexcept(seconds(left * right.asSeconds())));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary * operator to scale a time value.
    ///
    /// \param left: Left operand (a number).
    /// \param right: Right operand (a time).
    ///
    /// \return \a left multiplied by \a right.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator*(const std::int64_t left, const Time right) noexcept(
        noexcept(microseconds(left * right.asMicroseconds())));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary *= operator to scale/assign a time value.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left multiplied by \a right.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Time &
    operator*=(Time &left, const float right) noexcept(
        noexcept(left = (left * right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary *= operator to scale/assign a time value.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left multiplied by \a right.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Time &operator*=(Time &left, const std::int64_t right) noexcept(
        noexcept(left = (left * right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary / operator to scale a time value.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left divided by \a right.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator/(const Time left, const float right) noexcept(
        noexcept(seconds(left.asSeconds() / right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary / operator to scale a time value.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left divided by \a right.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator/(const Time left, const std::int64_t right) noexcept(
        noexcept(microseconds(left.asMicroseconds() / right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary /= operator to scale/assign a time value.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a number).
    ///
    /// \return \a left divided by \a right.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Time &operator/=(Time &left, const float right) noexcept(
        noexcept(left = (left / right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary /= operator to scale/assign a time value
    ///
    /// \param left: Left operand (a time)
    /// \param right: Right operand (a number)
    ///
    /// \return \a left divided by \a right
    ///
    ////////////////////////////////////////////////////////////
    constexpr Time &operator/=(Time &left, const std::int64_t right) noexcept(
        noexcept(left = (left / right)));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary / operator to compute the ratio of two time values.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a time).
    ///
    /// \return \a left divided by \a right.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr float
    operator/(const Time left, const Time right) noexcept(
        noexcept(left.asSeconds() / right.asSeconds()));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary % operator to compute remainder of a time value
    ///
    /// \param left: Left operand (a time)
    /// \param right: Right operand (a time)
    ///
    /// \return \a left modulo \a right
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]]
    constexpr Time
    operator%(const Time left, const Time right) noexcept(
        noexcept(microseconds(left.asMicroseconds() % right.asMicroseconds())));

    ////////////////////////////////////////////////////////////
    /// \relates Time
    /// \brief Overload of binary %= operator to compute/assign remainder of a time value.
    ///
    /// \param left: Left operand (a time).
    /// \param right: Right operand (a time).
    ///
    /// \return \a left modulo \a right.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Time &operator%=(Time &left, const Time right) noexcept(
        noexcept(left = (left % right)));
}

#include "Time.inl"
