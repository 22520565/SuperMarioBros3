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
// * This header file has been altered after copying from origin!
//
////////////////////////////////////////////////////////////
#pragma once
#include "Vector2.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Utility class for manipulating 2D axis aligned rectangles.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    class Rect2 {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        T left = T();   // Left coordinate of the rect.
        T top = T();    // Top coordinate of the rect.
        T width = T();  // Width of the rect.
        T height = T(); // Height of the rect.

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        /// Creates an empty rectangle (it is equivalent to calling
        /// Rect2({0, 0}, {0, 0})).
        ///
        ////////////////////////////////////////////////////////////
        constexpr Rect2() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the rectangle from position and size.
        /// Be careful, the last parameter is the size,
        /// not the bottom-right corner!
        ///
        /// \param position: Position of the top-left corner of the rectangle.
        /// \param size: Size of the rectangle.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit(false) Rect2(const Vector2<T> &position, const Vector2<T> &size) noexcept(
            noexcept(T(position.x)) && noexcept(T(position.y))
                && noexcept(T(size.x)) && noexcept(T(size.y)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the rectangle from another type of rectangle
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param rec: Rectangle to convert
        ///
        ////////////////////////////////////////////////////////////
        template <typename U>
            requires std::is_arithmetic_v<std::remove_reference_t<U>>
        constexpr explicit Rect2(const Rect2<U> &rect2) noexcept(
            noexcept(T(static_cast<T>(rect2.left))) && noexcept(T(static_cast<T>(rect2.top)))
                && noexcept(T(static_cast<T>(rect2.width))) && noexcept(T(static_cast<T>(rect2.height))));

        ////////////////////////////////////////////////////////////
        /// \brief Default overload of binary operator ==
        ///
        /// \note Since C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (a rect2).
        /// \param right: Right operand (a rec2).
        ///
        /// \return True if \a left is equal to \a right.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr bool
        operator==(const Rect2<T> &left, const Rect2<T> &right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get the position of the rectangle's top-left corner
        ///
        /// \return Position of rectangle
        ///
        /// \see getSize, getCenter
        ///
        ////////////////////////////////////////////////////////////
        constexpr Vector2<T> getPosition() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the size of the rectangle
        ///
        /// \return Size of rectangle
        ///
        /// \see getPosition, getCenter
        ///
        ////////////////////////////////////////////////////////////
        constexpr Vector2<T> getSize() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the position of the center of the rectangle.
        ///
        /// \return Center of rectangle.
        ///
        /// \see getPosition, getSize
        ///
        ////////////////////////////////////////////////////////////
        constexpr Vector2<T> getCenter() const noexcept(
            noexcept(Vector2<T>(left + (width / T(2)), top - (height / T(2)))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a copy of the rectangle that its size
        /// is wrapped to unsigned.
        ///
        /// \return An unsigned-wrapped-size rectangle.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Rect2<T> wrapSizeUnsigned() const noexcept(
            noexcept(Rect2<T>(Rect2<T>())));

        ////////////////////////////////////////////////////////////
        /// \brief Check if a point is inside the rectangle's area
        ///
        /// This check is non-inclusive. If the point lies on the
        /// edge of the rectangle, this function will return false.
        ///
        /// \param point: Point to test
        ///
        /// \return True if the point is inside, false otherwise.
        ///
        ////////////////////////////////////////////////////////////
        constexpr bool contains(const Vector2<T> &point) const noexcept(
            noexcept(wrapSizeUnsigned()));
    };
}

#include "Rect2.inl"
