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

#include "Time.hpp"
#include <cassert>
#include <ratio>

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename Rep, typename Period>
    constexpr Time::Time(const std::chrono::duration<Rep, Period> &duration) noexcept(
        noexcept(std::chrono::microseconds(std::chrono::duration<Rep, Period>())))
        : microsecondsAmount(duration) {}

    ////////////////////////////////////////////////////////////
    constexpr float Time::asSeconds() const noexcept(
        noexcept(std::chrono::duration<float>().count())) {
        return std::chrono::duration<float>(this->microsecondsAmount).count();
    }

    ////////////////////////////////////////////////////////////
    constexpr std::int32_t Time::asMilliseconds() const noexcept(
        noexcept(std::chrono::duration_cast<std::chrono::duration<std::int32_t, std::milli>>(std::chrono::microseconds()).count())) {
        return std::chrono::duration_cast<std::chrono::duration<std::int32_t, std::milli>>(this->microsecondsAmount).count();
    }

    ////////////////////////////////////////////////////////////
    constexpr std::int64_t Time::asMicroseconds() const noexcept(
        noexcept(std::chrono::microseconds().count())) {
        return this->microsecondsAmount.count();
    }

    ////////////////////////////////////////////////////////////
    constexpr const std::chrono::microseconds &Time::toDuration() const noexcept {
        return this->microsecondsAmount;
    }

    ////////////////////////////////////////////////////////////
    template <typename Rep, typename Period>
    constexpr Time::operator std::chrono::duration<Rep, Period>() const noexcept {
        return this->microsecondsAmount;
    }

    ////////////////////////////////////////////////////////////
    constexpr Time seconds(const float amount) noexcept(
        noexcept(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(amount)))) {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(amount));
    }

    ////////////////////////////////////////////////////////////
    constexpr Time milliseconds(const std::int32_t amount) noexcept(
        noexcept(std::chrono::milliseconds(amount))) {
        return std::chrono::milliseconds(amount);
    }

    ////////////////////////////////////////////////////////////
    constexpr Time microseconds(const std::int64_t amount) noexcept(
        noexcept(std::chrono::microseconds(amount))) {
        return std::chrono::microseconds(amount);
    }

    ////////////////////////////////////////////////////////////
    constexpr auto operator<=>(const Time left, const Time right) noexcept(
        noexcept(left.asMicroseconds() <=> right.asMicroseconds())) {
        return left.asMicroseconds() <=> right.asMicroseconds();
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator-(const Time right) noexcept(
        noexcept(microseconds(-right.asMicroseconds()))) {
        return microseconds(-right.asMicroseconds());
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator+(const Time left, const Time right) noexcept(
        noexcept(microseconds(left.asMicroseconds() + right.asMicroseconds()))) {
        return microseconds(left.asMicroseconds() + right.asMicroseconds());
    }

    ////////////////////////////////////////////////////////////
    constexpr Time &operator+=(Time &left, const Time right) noexcept(
        noexcept(left = (left + right))) {
        left = left + right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator-(const Time left, const Time right) noexcept(
        noexcept(microseconds(left.asMicroseconds() - right.asMicroseconds()))) {
        return microseconds(left.asMicroseconds() - right.asMicroseconds());
    }

    ////////////////////////////////////////////////////////////
    constexpr Time &operator-=(Time &left, const Time right) noexcept(
        noexcept(left = (left - right))) {
        left = left - right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator*(const Time left, const float right) noexcept(
        noexcept(seconds(left.asSeconds() * right))) {
        return seconds(left.asSeconds() * right);
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator*(const Time left, const std::int64_t right) noexcept(
        noexcept(microseconds(left.asMicroseconds() * right))) {
        return microseconds(left.asMicroseconds() * right);
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator*(const float left, const Time right) noexcept(
        noexcept(seconds(left * right.asSeconds()))) {
        return seconds(left * right.asSeconds());
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator*(const std::int64_t left, const Time right) noexcept(
        noexcept(microseconds(left * right.asMicroseconds()))) {
        return microseconds(left * right.asMicroseconds());
    }

    ////////////////////////////////////////////////////////////
    constexpr Time &operator*=(Time &left, const float right) noexcept(
        noexcept(left = (left * right))) {
        left = left * right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    constexpr Time &operator*=(Time &left, const std::int64_t right) noexcept(
        noexcept(left = (left * right))) {
        left = left * right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator/(const Time left, const float right) noexcept(
        noexcept(seconds(left.asSeconds() / right))) {
        assert(right != 0 && "Time::operator/ cannot divide by 0");
        return seconds(left.asSeconds() / right);
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator/(const Time left, const std::int64_t right) noexcept(
        noexcept(microseconds(left.asMicroseconds() / right))) {
        assert(right != 0 && "Time::operator/ cannot divide by 0");
        return microseconds(left.asMicroseconds() / right);
    }

    ////////////////////////////////////////////////////////////
    constexpr Time &operator/=(Time &left, const float right) noexcept(
        noexcept(left = (left / right))) {
        assert(right != 0 && "Time::operator/= cannot divide by 0");
        left = left / right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    constexpr Time &operator/=(Time &left, const std::int64_t right) noexcept(
        noexcept(left = (left / right))) {
        assert(right != 0 && "Time::operator/= cannot divide by 0");
        left = left / right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    constexpr float operator/(const Time left, const Time right) noexcept(
        noexcept(left.asSeconds() / right.asSeconds())) {
        assert(right.asMicroseconds() != 0 && "Time::operator/ cannot divide by 0");
        return left.asSeconds() / right.asSeconds();
    }

    ////////////////////////////////////////////////////////////
    constexpr Time operator%(const Time left, const Time right) noexcept(
        noexcept(microseconds(left.asMicroseconds() % right.asMicroseconds()))) {
        assert(right.asMicroseconds() != 0 && "Time::operator% cannot modulus by 0");
        return microseconds(left.asMicroseconds() % right.asMicroseconds());
    }

    ////////////////////////////////////////////////////////////
    constexpr Time &operator%=(Time &left, const Time right) noexcept(
        noexcept(left = (left % right))) {
        assert(right.asMicroseconds() != 0 && "Time::operator%= cannot modulus by 0");
        left = left % right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////

    // Note: the 'inline' keyword here is technically not required, but VS2019 fails
    // to compile with a bogus "multiple definition" error if not explicitly used.

    inline constexpr Time Time::zero = Time();
}
