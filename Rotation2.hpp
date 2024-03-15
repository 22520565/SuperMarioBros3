#pragma once
#include "Angle.hpp"
#include "Angle2.hpp"
#include "Vector2.hpp"
#include <concepts>

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Utility class for rotation in 2-dimension.
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    class Rotation2 {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        Angle<T> angleX = Angle<T>::zero(); // Angle to the X axis.
        Angle<T> angleY = Angle<T>::zero(); // Angle to the Y axis.
        T centerX = T();                    // X coordinate of the center point.
        T centerY = T();                    // Y coordinate of the center point.

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Rotation2() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Create a rotation with a specified angle2.
        /// The center point of rotation has a coordinate of (0, 0).
        ///
        /// \param angle2: Angle2 of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rotation2(const Angle2<T> &angle2) noexcept(
            noexcept(Angle<T>(angle2.x)) && noexcept(Angle<T>(angle2.y)) && noexcept(T(T())));

        ////////////////////////////////////////////////////////////
        /// \brief Create a rotation with a specified coordinate of
        /// a center point.
        /// The angle of rotation is (0, 0).
        ///
        /// \param center: Coordinate of the center point of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rotation2(const Vector2<T> &center) noexcept(
            noexcept(T(center.x)) && noexcept(T(center.y)) && noexcept(Angle<T>(Angle<T>::zero())));

        ////////////////////////////////////////////////////////////
        /// \brief Create a rotation with a specified angle2 and
        /// a specified coordinate of a center point.
        ///
        /// \param angle2: Angle2 of the rotation.
        /// \param center: Coordinate of the center point of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit(false) Rotation2(const Angle2<T> &angle2, const Vector2<T> &center) noexcept(
            noexcept(Angle<T>(angle2.x)) && noexcept(Angle<T>(angle2.y))
                && noexcept(T(center.x)) && noexcept(T(center.y)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the rotation2 from another type of rotation2.
        ///
        /// This constructor doesn't replace the move constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param rotation2: Rotation2 to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <std::floating_point U>
        constexpr explicit Rotation2(const Rotation2<U> &rotation2) noexcept(
            noexcept(Angle<T>(static_cast<Angle<T>>(rotation2.angleX)))
                && noexcept(Angle<T>(static_cast<Angle<T>>(rotation2.angleY)))
                    && noexcept(T(static_cast<T>(rotation2.centerX)))
                        && noexcept(T(static_cast<T>(rotation2.centerY))));

        ////////////////////////////////////////////////////////////
        /// \brief Default overload of binary operator ==
        ///
        /// \note Since C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (a rotation2).
        /// \param right: Right operand (a rotation2).
        ///
        /// \return True if \a left is equal to \a right.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr bool
        operator==(const Rotation2<T> &left, const Rotation2<T> &right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get an angle2 of the rotation.
        ///
        /// \return Angle2 of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Angle2<T> getAngle() const noexcept(
            noexcept(Angle2<T>(Angle<T>(), Angle<T>())));

        ////////////////////////////////////////////////////////////
        /// \brief Get an vector2 of the center point's coordinate
        /// of the rotation.
        ///
        /// \return Vector2 of the center point of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Vector2<T> getCenter() const noexcept(
            noexcept(Vector2<T>(T(), T())));
    };
}

#include "Rotation2.inl"
