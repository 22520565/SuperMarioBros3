#pragma once
#include "Vector2.hpp"
#include <type_traits>

namespace game {
    template <typename T>
        requires std::is_arithmetic_v<T>
    class Scalation2 {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        T factorX = static_cast<T>(1); // Factor to the X axis.
        T factorY = static_cast<T>(1); // Factor to the Y axis.
        T centerX = static_cast<T>(0); // X coordinate of the center point.
        T centerY = static_cast<T>(0); // Y coordinate of the center point.

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Scalation2() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Create a rotation with a specified factor and
        /// a specified coordinate of a center point.
        ///
        /// \param factor: Factor of the rotation.
        /// \param center: Coordinate of the center point of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit(false) Scalation2(const Vector2<T> &factor, const Vector2<T> &center) noexcept(
            noexcept(T(factor.x)) && noexcept(T(factor.y)) && noexcept(T(center.x)) && noexcept(T(center.y)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the scalation2 from another type of scalation2.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param scalation2: Scalation2 to convert
        ///
        ////////////////////////////////////////////////////////////
        template <typename U>
            requires std::is_arithmetic_v<U>
        constexpr explicit Scalation2(const Scalation2<U> &scalation2) noexcept(
            noexcept(T(static_cast<T>(scalation2.factorX))) && noexcept(T(static_cast<T>(scalation2.factorY)))
                && noexcept(T(static_cast<T>(scalation2.centerX))) && noexcept(T(static_cast<T>(scalation2.centerY))));

        ////////////////////////////////////////////////////////////
        /// \brief Default overload of binary operator ==
        ///
        /// \note Since C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (a scalation2).
        /// \param right: Right operand (a scalation2).
        ///
        /// \return True if \a left is equal to \a right.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr bool
        operator==(const Scalation2<T> &left, const Scalation2<T> &right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get a vector2 of the rotation's factor.
        ///
        /// \return Vector2 of the rotation's factor.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Vector2<T> getFactor() const noexcept(
            noexcept(Vector2<T>(T(), T())));

        ////////////////////////////////////////////////////////////
        /// \brief Get an vector2 of the center point's coordinate
        /// of the scalation.
        ///
        /// \return Vector2 of the center point of the scalation.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Vector2<T> getCenter() const noexcept(
            noexcept(Vector2<T>(T(), T())));
    };
}

#include "Scalation2.inl"
