#pragma once
#include "Angle3.hpp"
#include "Rotation2.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Utility class for rotation in 3-dimension.
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    class Rotation3 : public Rotation2<T> {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        Angle<T> angleZ = Angle<T>::zero(); // Angle to the Z axis.
        T centerZ = T();                    // Z coordinate of the center point.

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Rotation3() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Create a rotation with a specified angle3.
        /// The center point of rotation has a coordinate of (0, 0, 0).
        ///
        /// \param angle3: Angle3 of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rotation3(const Angle3<T> &angle3) noexcept(
            noexcept(Rotation2<T>(angle3)) && noexcept(Angle<T>(angle3.z)) && noexcept(T(T())));

        ////////////////////////////////////////////////////////////
        /// \brief Create a rotation with a specified coordinate of
        /// a center point.
        /// The angle of rotation is (0, 0, 0).
        ///
        /// \param center: Coordinate of the center point of the rotation.
        ////////////////////////////////////////////////////////////
        constexpr explicit Rotation3(const Vector3<T> &center) noexcept(
            noexcept(Rotation2<T>(center)) && noexcept(T(center.z)) && noexcept(Angle<T>(Angle<T>::zero())));

        ////////////////////////////////////////////////////////////
        /// \brief Create a rotation with a specified angle3 and
        /// a specified coordinate of a center point.
        ///
        /// \param angle3: Angle3 of the rotation.
        /// \param center: Coordinate of the center point of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit(false) Rotation3(const Angle3<T> &angle3, const Vector3<T> &center) noexcept(
            noexcept(Rotation2<T>(angle3, center)) && noexcept(Angle<T>(angle3.z)) && noexcept(T(center.z)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct a rotation3 from a rotation2.
        ///
        /// \param vector2: Rotation2 to construct.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rotation3(const Rotation2<T> &rotation2) noexcept(
            noexcept(Rotation2<T>(rotation2)) && noexcept(Angle<T>(Angle<T>::zero())) && noexcept(T(T())));

        ////////////////////////////////////////////////////////////
        /// \brief Construct a rotation3 from a rotation2 with
        /// an angle to the Z axis.
        ///
        /// \param vector2: Rotation2 to construct.
        /// \param angleZ: Angle to the Z axis.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rotation3(const Rotation2<T> &rotation2, const Angle<T> angleZ) noexcept(
            noexcept(Rotation2<T>(rotation2)) && noexcept(Angle<T>(angleZ)) && noexcept(T(T())));

        ////////////////////////////////////////////////////////////
        /// \brief Construct a rotation3 from a rotation2 with
        /// Z coordinate of the center point.
        ///
        /// \param vector2: Rotation2 to construct.
        /// \param centerZ: Z coordinate of the center point.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rotation3(const Rotation2<T> &rotation2, const T centerZ) noexcept(
            noexcept(Rotation2<T>(rotation2)) && noexcept(Angle<T>(Angle<T>::zero())) && noexcept(T(centerZ)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct a rotation3 from a rotation2 with
        /// an angle to the Z axis and Z coordinate of the center point.
        ///
        /// \param vector2: Rotation2 to construct.
        /// \param angleZ: Angle to the Z axis.
        /// \param centerZ: Z coordinate of the center point.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rotation3(const Rotation2<T> &rotation2, const Angle<T> angleZ, const T centerZ) noexcept(
            noexcept(Rotation2<T>(rotation2)) && noexcept(Angle<T>(angleZ)) && noexcept(T(centerZ)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the rotation3 from another type of rotation3.
        ///
        /// This constructor doesn't replace the move constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param rotation3: Rotation3 to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <std::floating_point U>
        constexpr explicit Rotation3(const Rotation3<U> &rotation3) noexcept(
            noexcept(Rotation2<T>(rotation3)) && noexcept(Angle<T>(rotation3.angleZ))
                && noexcept(T(rotation3.centerZ)));

        ////////////////////////////////////////////////////////////
        /// \brief Default overload of binary operator ==
        ///
        /// \note Since C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (a rotation3).
        /// \param right: Right operand (a rotation3).
        ///
        /// \return True if \a left is equal to \a right.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr bool
        operator==(const Rotation3<T> &left, const Rotation3<T> &right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get an angle3 of the rotation.
        ///
        /// \return Angle3 of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Angle3<T> getAngle() const noexcept(
            noexcept(Angle3<T>(Rotation2<T>().getAngle(), Angle<T>())));

        ////////////////////////////////////////////////////////////
        /// \brief Get an vector3 of the center point's coordinate
        /// of the rotation.
        ///
        /// \return Vector3 of the center point of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Vector3<T> getCenter() const noexcept(
            noexcept(Vector3<T>(Rotation2<T>().getCenter(), T())));
    };
}

#include "Rotation3.inl"
