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

#pragma once
#include "Angle.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    template <std::floating_point U>
    constexpr Angle<T>::Angle(const Angle<U> &angle) noexcept(
        noexcept(T(static_cast<T>(angle.amountDegrees))))
        : amountDegrees(static_cast<T>(angle.amountDegrees)) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    template <std::floating_point U>
    constexpr Angle<T>::Angle(Angle<U> &&angle) noexcept(
        noexcept(T(static_cast<T>(angle.amountDegrees))))
        : amountDegrees(static_cast<T>(angle.amountDegrees)) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    [[nodiscard]]
    constexpr Angle<T> degrees(const T angle) noexcept(
        noexcept(Angle<T>(angle))) { return Angle<T>(angle); }

    ////////////////////////////////////////////////////////////
    template <std::integral T>
    constexpr Angle<long double> degrees(const T angle) noexcept(
        noexcept(Angle<long double>(angle))) { return Angle<long double>(angle); }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    [[nodiscard]]
    constexpr Angle<T> radians(const T angle) noexcept(
        noexcept(Angle<T>(angle * (static_cast<T>(180.0) / std::numbers::pi_v<T>)))) {
        return Angle<T>(angle * (static_cast<T>(180.0) / std::numbers::pi_v<T>));
    }

    ////////////////////////////////////////////////////////////
    template <std::integral T>
    [[nodiscard]]
    constexpr Angle<long double> radians(const T angle) noexcept(
        noexcept(Angle<long double>(angle * (static_cast<long double>(180.0) / std::numbers::pi_v<long double>)))) {
        return Angle<long double>(angle * (static_cast<long double>(180.0) / std::numbers::pi_v<long double>));
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const T &Angle<T>::asDegrees() const noexcept { return this->amountDegrees; }

    template <std::floating_point T>
    constexpr T Angle<T>::asRadians() const noexcept(
        noexcept(this->amountDegrees * (std::numbers::pi_v<T> / static_cast<T>(180.0)))) {
        return this->amountDegrees * (std::numbers::pi_v<T> / static_cast<T>(180.0));
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> Angle<T>::wrapSigned() const noexcept(
        noexcept(Angle<T>(std::fmod(this->amountDegrees + static_cast<T>(180.0F), static_cast<T>(360.0F)) -
                          static_cast<T>(180.0F)))) {
        return Angle<T>(std::fmod(this->amountDegrees + static_cast<T>(180.0F), static_cast<T>(360.0F)) -
                        static_cast<T>(180.0F));
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> Angle<T>::wrapUnsigned() const noexcept(
        noexcept(Angle(std::fmod(this->amountDegrees, static_cast<T>(360.0))))) {
        return Angle(std::fmod(this->amountDegrees, static_cast<T>(360.0)));
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> operator+(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(degrees(left.asDegrees() + right.asDegrees()))) {
        return degrees(left.asDegrees() + right.asDegrees());
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> &operator+=(Angle<T> &left, const Angle<T> right) noexcept(
        noexcept(left = (left + right))) {
        left = left + right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> operator-(const Angle<T> right) noexcept(
        noexcept(degrees(-right.asDegrees()))) { return degrees(-right.asDegrees()); }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> operator-(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(degrees(left.asDegrees() - right.asDegrees()))) {
        return degrees(left.asDegrees() - right.asDegrees());
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> &operator-=(Angle<T> &left, const Angle<T> right) noexcept(
        noexcept(left = (left - right))) {
        left = left - right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> operator*(const Angle<T> left, const T right) noexcept(
        noexcept(degrees(left.asDegrees() * right))) {
        return degrees(left.asDegrees() * right);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> operator*(const T left, const Angle<T> right) noexcept(
        noexcept(right * left)) { return right * left; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> &operator*=(Angle<T> &left, const T right) noexcept(
        noexcept(left = (left * right))) {
        left = left * right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> operator/(const Angle<T> left, const T right) noexcept(
        noexcept(degrees(left.asDegrees() / right))) {
        return degrees(left.asDegrees() / right);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> &operator/=(Angle<T> &left, const T right) noexcept(
        noexcept(left = (left / right))) {
        left = left / right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr T operator/(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(left.asDegrees() / right.asDegrees())) {
        return left.asDegrees() / right.asDegrees();
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> operator%(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(degrees(std::fmod(left.asDegrees(), right.asDegrees())))) {
        return degrees(std::fmod(left.asDegrees(), right.asDegrees()));
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle<T> &operator%=(Angle<T> &left, const Angle<T> right) noexcept(
        noexcept(left = (left % right))) {
        left = left % right;
        return left;
    }

    inline namespace literals {
        ////////////////////////////////////////////////////////////
        consteval Angle<long double>
        operator""_deg(const long double angle) noexcept(
            noexcept(degrees<long double>(angle))) {
            return degrees<long double>(angle);
        }

        consteval Angle<long double>
        operator""_deg(unsigned long long int angle) noexcept(
            noexcept(degrees<long double>(angle))) { return degrees<long double>(angle); }

        ////////////////////////////////////////////////////////////
        consteval Angle<long double>
        operator""_rad(const long double angle) noexcept(
            noexcept(radians<long double>(angle))) { return radians<long double>(angle); }

        consteval Angle<long double>
        operator""_rad(unsigned long long int angle) noexcept(
            noexcept(radians<long double>(angle))) { return radians<long double>(angle); }
    }
}
