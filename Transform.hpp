#pragma once
#include "Angle.hpp"
#include "Angle3.hpp"
#include "D3DX10math.h"
#include <cmath>
#include <minwindef.h>

namespace game {
    template <typename T>
        requires std::is_floating_point_v<std::remove_reference_t<T>>
    class Transform final {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        T f00 = static_cast<T>(1.0); // Element (0, 0) of the matrix.
        T f01 = static_cast<T>(0.0); // Element (0, 1) of the matrix.
        T f02 = static_cast<T>(0.0); // Element (0, 2) of the matrix.
        T f03 = static_cast<T>(0.0); // Element (0, 3) of the matrix.
        T f10 = static_cast<T>(0.0); // Element (1, 0) of the matrix.
        T f11 = static_cast<T>(1.0); // Element (1, 1) of the matrix.
        T f12 = static_cast<T>(0.0); // Element (1, 2) of the matrix.
        T f13 = static_cast<T>(0.0); // Element (1, 3) of the matrix.
        T f20 = static_cast<T>(0.0); // Element (2, 0) of the matrix.
        T f21 = static_cast<T>(0.0); // Element (2, 1) of the matrix.
        T f22 = static_cast<T>(1.0); // Element (2, 2) of the matrix.
        T f23 = static_cast<T>(0.0); // Element (2, 3) of the matrix.
        T f30 = static_cast<T>(0.0); // Element (3, 0) of the matrix.
        T f31 = static_cast<T>(0.0); // Element (3, 1) of the matrix.
        T f32 = static_cast<T>(0.0); // Element (3, 2) of the matrix.
        T f33 = static_cast<T>(1.0); // Element (3, 3) of the matrix.

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates an identity transform (a transform that does nothing).
        ///
        ////////////////////////////////////////////////////////////
        constexpr Transform() noexcept = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct a transform from a 4x4 matrix.
        ///
        /// \param f00: Element (0, 0) of the matrix.
        /// \param f01: Element (0, 1) of the matrix.
        /// \param f02: Element (0, 2) of the matrix.
        /// \param f03: Element (0, 3) of the matrix.
        /// \param f10: Element (1, 0) of the matrix.
        /// \param f11: Element (1, 1) of the matrix.
        /// \param f12: Element (1, 2) of the matrix.
        /// \param f13: Element (1, 3) of the matrix.
        /// \param f20: Element (2, 0) of the matrix.
        /// \param f21: Element (2, 1) of the matrix.
        /// \param f22: Element (2, 2) of the matrix.
        /// \param f23: Element (2, 3) of the matrix.
        /// \param f30: Element (3, 0) of the matrix.
        /// \param f31: Element (3, 1) of the matrix.
        /// \param f32: Element (3, 2) of the matrix.
        /// \param f33: Element (3, 3) of the matrix.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Transform(const T f00, const T f01, const T f02, const T f03,
                            const T f10, const T f11, const T f12, const T f13,
                            const T f20, const T f21, const T f22, const T f23,
                            const T f30, const T f31, const T f32, const T f33) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Convert to D3DXMATRIX.
        ///
        /// \return D3DXMATRIX.
        ///
        ////////////////////////////////////////////////////////////
        explicit(false) operator D3DXMATRIX() const;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with another one.
        ///
        /// \param transform: Transform to combine with this transform.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform<T> combine(const Transform<T> &transform) const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with a translation.
        ///
        /// \param offset: Translation offset to apply.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform<T> translate(const Vector3<T> &offset) const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with a rotation with
        /// a center point of (0, 0, 0).
        ///
        /// \param angle3: Rotation angle in three dimensions.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform<T> rotate(const Angle3<T> &angle3) const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with a rotation with
        /// a specified center point.
        ///
        /// \param angle3: Rotation angle in three dimensions.
        /// \param center: Coordinate of center point to rotate.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform rotate(const Angle3<T> &angle3, const Vector3<T> &center) const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with a rotation with
        /// a center point of (0, 0, 0).
        ///
        /// \param angle: Rotation angle, in degrees.
        /// \param axis: Unit vector of the rotation axis.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform rotate(const Angle<T> angle, const Vector3<T> &axis) const noexcept;

        [[nodiscard]]
        constexpr Transform rotate(const Angle<T> angle, const Vector3<T> &axis,
                                   const Vector3<T> &center) const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with a scalation with
        /// a center point of (0, 0, 0)
        ///
        /// \param factor: Scaling factor in three dimensions.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform scale(const Vector3f &factor) const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with a scalation with
        /// a specified center point.
        ///
        /// \param factor: Scaling factor in three dimensions.
        /// \param center: Coordinate of center point of scaling.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform scale(const Vector3<T> &factor, const Vector3<T> &center) const noexcept;
    };
}

#include "Transform.inl"
