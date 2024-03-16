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
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    template <std::floating_point U>
    constexpr Angle<T>::Angle(const Angle<U> &angle) noexcept(
        noexcept(T(static_cast<T>(angle.asDegrees()))))
        : amountDegrees(static_cast<T>(angle.asDegrees())) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    template <std::floating_point U>
    constexpr Angle<T>::Angle(Angle<U> &&angle) noexcept(
        noexcept(T(static_cast<T>(angle.asDegrees()))))
        : amountDegrees(static_cast<T>(angle.asDegrees())) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> Angle<T>::degrees(const T angle) noexcept(
        noexcept(Angle<T>(angle))) { return Angle<T>(angle); }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    template <std::integral U>
    constexpr Angle<T> Angle<T>::degrees(const U angle) noexcept(
        noexcept(Angle<T>(static_cast<T>(angle)))) {
        return Angle<T>(static_cast<T>(angle));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> Angle<T>::radians(const T angle) noexcept(
        noexcept(Angle<T>(angle * (static_cast<T>(180.0) / std::numbers::pi_v<T>)))) {
        return Angle<T>(angle * (static_cast<T>(180.0) / std::numbers::pi_v<T>));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    template <std::integral U>
    constexpr Angle<T> Angle<T>::radians(const U angle) noexcept(
        noexcept(Angle<T>(static_cast<T>(angle) * (static_cast<T>(180.0) / std::numbers::pi_v<T>)))) {
        return Angle<T>(static_cast<T>(angle) * (static_cast<T>(180.0) / std::numbers::pi_v<T>));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const T &Angle<T>::asDegrees() const noexcept { return this->amountDegrees; }

    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr T Angle<T>::asRadians() const noexcept(
        noexcept(amountDegrees * (std::numbers::pi_v<T> / static_cast<T>(180.0)))) {
        return this->amountDegrees * (std::numbers::pi_v<T> / static_cast<T>(180.0));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> Angle<T>::wrapSigned() const noexcept(
        noexcept(Angle<T>(std::fmod(amountDegrees + static_cast<T>(180.0F), static_cast<T>(360.0F)) -
                          static_cast<T>(180.0F)))) {
        return Angle<T>(std::fmod(this->amountDegrees + static_cast<T>(180.0F), static_cast<T>(360.0F)) -
                        static_cast<T>(180.0F));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> Angle<T>::wrapUnsigned() const noexcept(
        noexcept(Angle<T>(std::fmod(amountDegrees, static_cast<T>(360.0))))) {
        return Angle(std::fmod(this->amountDegrees, static_cast<T>(360.0)));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle<T> Angle<T>::zero() noexcept(noexcept(Angle<T>())) {
        return Angle<T>();
    };

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle<T> Angle<T>::one_deg() noexcept(noexcept(Angle<T>::degrees(1.0))) {
        return Angle<T>::degrees(1.0);
    };

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle<T> Angle<T>::one_rad() noexcept(noexcept(Angle<T>::radians(1.0))) {
        return Angle<T>::radians(1.0);
    };

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> operator+(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(Angle<T>::degrees(left.asDegrees() + right.asDegrees()))) {
        return Angle<T>::degrees(left.asDegrees() + right.asDegrees());
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator+=(Angle<T> &left, const Angle<T> right) noexcept(
        noexcept(left = (left + right))) {
        left = left + right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> operator-(const Angle<T> right) noexcept(
        noexcept(Angle<T>::degrees(-right.asDegrees()))) { return Angle<T>::degrees(-right.asDegrees()); }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> operator-(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(Angle<T>::degrees(left.asDegrees() - right.asDegrees()))) {
        return Angle<T>::degrees(left.asDegrees() - right.asDegrees());
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator-=(Angle<T> &left, const Angle<T> right) noexcept(
        noexcept(left = (left - right))) {
        left = left - right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> operator*(const Angle<T> left, const T right) noexcept(
        noexcept(Angle<T>::degrees(left.asDegrees() * right))) {
        return Angle<T>::degrees(left.asDegrees() * right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> operator*(const T left, const Angle<T> right) noexcept(
        noexcept(right * left)) { return right * left; }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator*=(Angle<T> &left, const T right) noexcept(
        noexcept(left = (left * right))) {
        left = left * right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> operator/(const Angle<T> left, const T right) noexcept(
        noexcept(Angle<T>::degrees(left.asDegrees() / right))) {
        return Angle<T>::degrees(left.asDegrees() / right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator/=(Angle<T> &left, const T right) noexcept(
        noexcept(left = (left / right))) {
        left = left / right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr T operator/(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(left.asDegrees() / right.asDegrees())) {
        return left.asDegrees() / right.asDegrees();
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> operator%(const Angle<T> left, const Angle<T> right) noexcept(
        noexcept(Angle<T>::degrees(std::fmod(left.asDegrees(), right.asDegrees())))) {
        return Angle<T>::degrees(std::fmod(left.asDegrees(), right.asDegrees()));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle<T> &operator%=(Angle<T> &left, const Angle<T> right) noexcept(
        noexcept(left = (left % right))) {
        left = left % right;
        return left;
    }

    inline namespace literals {
        ////////////////////////////////////////////////////////////
        consteval Angle<long double>
        operator""_deg(const long double angle) noexcept(
            noexcept(Angle<long double>::degrees(angle))) {
            return Angle<long double>::degrees(angle);
        }

        consteval Angle<long double>
        operator""_deg(const unsigned long long int angle) noexcept(
            noexcept(Angle<long double>::degrees(angle))) {
            return Angle<long double>::degrees(angle);
        }

        ////////////////////////////////////////////////////////////
        consteval Angle<long double>
        operator""_rad(const long double angle) noexcept(
            noexcept(Angle<long double>::radians(angle))) {
            return Angle<long double>::radians(angle);
        }

        ////////////////////////////////////////////////////////////
        consteval Angle<long double>
        operator""_rad(const unsigned long long int angle) noexcept(
            noexcept(Angle<long double>::radians(angle))) {
            return Angle<long double>::radians(angle);
        }
    }
}
