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
    template <typename T>
    class Rect {
      public:
        Vector2<T> position = Vector2<T>();
        Vector2<T> size = Vector2<T>();
        T &left = position.x;
        T &top = position.y;
        T &width = size.x;
        T &height = size.y;

        /// \brief Default constructor.
        /// Creates an empty rectangle (it is equivalent to calling
        /// Rect(0, 0, 0, 0)).
        constexpr Rect<T>() = default;

        /// \brief Construct the rectangle from position and size.
        /// Be careful, the last parameter is the size,
        /// not the bottom-right corner!
        ///
        /// \param position: Position of the top-left corner of the rectangle
        /// \param size: Size of the rectangle
        constexpr explicit Rect(const Vector2<T> &position, const Vector2<T> &size) noexcept(
            noexcept(Vector2<T>(position)) && noexcept(Vector2<T>(size)))
            : position(position), size(size) {}

        /// \brief Construct the rectangle from its coordinates.
        /// Be careful, the last two parameters are the width
        /// and height, not the right and bottom coordinates!
        ///
        /// \param left: Left coordinate of the rectangle
        /// \param top: Top coordinate of the rectangle
        /// \param width: Width of the rectangle
        /// \param height: Height of the rectangle
        constexpr explicit Rect(const T left, const T top, const T width, const T height) noexcept(
            noexcept(T(left)) && noexcept(T(top)) && noexcept(T(width)) && noexcept(T(height)))
            : left(left), top(top), width(width), height(height) {}

        /// \brief Construct the rectangle from another type of rectangle
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param rec: Rectangle to convert
        template <typename U>
        constexpr explicit Rect(const Rect<U> &rect) noexcept(
            noexcept(Vector2<T>(static_cast<Vector2<T>>(rect.position)))
                && noexcept(Vector2<T>(static_cast<Vector2<T>>(rect.size))))
            : position(static_cast<Vector2<T>>(rect.position)), size(static_cast<Vector2<T>>(rect.size)) {}

        /// \brief Check if a point is inside the rectangle's area
        ///
        /// This check is non-inclusive. If the point lies on the
        /// edge of the rectangle, this function will return false.
        ///
        /// \param point: Point to test
        ///
        /// \return True if the point is inside, false otherwise.
        constexpr bool contains(const Vector2<T> &point) const noexcept(
            noexcept(this->contains(point.x, point.y))) {
            return this->contains(point.x, point.y);
        }

        /// \brief Check if a point is inside the rectangle's area
        ///
        /// This check is non-inclusive. If the point lies on the
        /// edge of the rectangle, this function will return false.
        ///
        /// \param x: X coordinate of the point to test
        /// \param y: Y coordinate of the point to test
        ///
        /// \return True if the point is inside, false otherwise.
        constexpr bool contains(T x, T y) const noexcept(
            noexcept((this->left < x) && (x < (this->left + this->width)) &&
                     (this->top < y) && (y < (this->top + this->height)))) {
            return (this->left < x) && (x < (this->left + this->width)) &&
                   (this->top < y) && (y < (this->top + this->height));
        }
    };
}
