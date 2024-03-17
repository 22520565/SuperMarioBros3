////////////////////////////////////////////////////////////
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
// *. This inline file has been altered after copying from origin!
//
////////////////////////////////////////////////////////////
#include "Rect2.hpp"
#include "Vector2.hpp"
#include <type_traits>

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect2<T>::Rect2(const Vector2<T> &position, const Vector2<T> &size) noexcept(
        noexcept(T(position.x)) && noexcept(T(position.y))
            && noexcept(T(size.x)) && noexcept(T(size.y)))
        : left(position.x), top(position.y), width(size.x), height(size.y) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    template <typename U>
        requires std::is_arithmetic_v<std::remove_reference_t<U>>
    constexpr Rect2<T>::Rect2(const Rect2<U> &rect2) noexcept(
        noexcept(T(static_cast<T>(rect2.left))) && noexcept(T(static_cast<T>(rect2.top)))
            && noexcept(T(static_cast<T>(rect2.width))) && noexcept(T(static_cast<T>(rect2.height))))
        : left(static_cast<T>(rect2.left)), top(static_cast<T>(rect2.top)),
          width(static_cast<T>(rect2.width)), height(static_cast<T>(rect2.height)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> Rect2<T>::getPosition() const noexcept {
        return Vector2<T>(this->left, this->top);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> Rect2<T>::getSize() const noexcept {
        return Vector2<T>(this->width, this->height);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> Rect2<T>::getCenter() const noexcept(
        noexcept(Vector2<T>(left + (width / T(2)), top - (height / T(2))))) {
        return Vector2<T>(this->left + (this->width / T(2)), this->top - (this->height / T(2)));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect2<T> Rect2<T>::wrapSizeUnsigned() const noexcept(
        noexcept(Rect2<T>(Rect2<T>()))) {
        Rect2<T> newRect2 = *this;

        if (newRect2.width < T()) [[unlikely]] {
            newRect2.left += newRect2.width;
            newRect2.width = -newRect2.width;
        }
        if (newRect2.height < T()) [[unlikely]] {
            newRect2.top -= newRect2.height;
            newRect2.height = -newRect2.height;
        }

        return newRect2;
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr bool Rect2<T>::contains(const Vector2<T> &point) const noexcept(
        noexcept(wrapSizeUnsigned())) {
        const Rect2<T> wrappedSizeRect2 = this->wrapSizeUnsigned();
        return (point.x >= wrappedSizeRect2.left) &&
               (point.x < (wrappedSizeRect2.left + wrappedSizeRect2.width)) &&
               (point.y <= wrappedSizeRect2.top) &&
               (point.y > (wrappedSizeRect2.top - wrappedSizeRect2.height));
    }
}
