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
// *. This header file has been altered after copying from origin!
//
////////////////////////////////////////////////////////////

#pragma once
#include "Angle.hpp"
#include "Angle3.hpp"
#include "Rotation3.hpp"
#include "Scalation3.hpp"
#include <D3DX10math.h>
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
        /// \brief Default overload of binary operator == to compare two transforms.
        ///
        /// Performs an element-wise comparison of the elements of the
        /// left transform with the elements of the right transform.
        /// 
        /// \note Since C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (the first transform).
        /// \param right: Right operand (the second transform).
        ///
        /// \return true if the transforms are equal, false otherwise.
        /// 
        ////////////////////////////////////////////////////////////
        [[nodiscard]] 
        friend constexpr bool
        operator==(const Transform<T>& left, const Transform<T>& right) = default;

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
        /// \param angle3: Angle3 of the rotation.
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
        /// \param angle3: Angle3 of the rotation.
        /// \param center: Coordinate of the center point to rotate.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform<T> rotate(const Angle3<T> &angle3, const Vector3<T> &center) const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with a rotation.
        ///
        /// \param rotation3: Rotation to combine.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform<T> rotate(const Rotation3<T> &rotation3) const noexcept;

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
        constexpr Transform<T> rotate(const Angle<T> angle, const Vector3<T> &axis) const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with a rotation with
        /// a specified point.
        ///
        /// \param angle: Rotation angle, in degrees.
        /// \param axis: Unit vector of the rotation axis.
        /// \param center: Coordinate of the center point to rotate.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform<T> rotate(const Angle<T> angle, const Vector3<T> &axis,
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
        constexpr Transform<T> scale(const Vector3<T> &factor) const noexcept;

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
        constexpr Transform<T> scale(const Vector3<T> &factor, const Vector3<T> &center) const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Combine the current transform with a scalation.
        ///
        /// \param scalation3: Scalation to combine.
        ///
        /// \return The result of combination.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Transform<T> scale(const Scalation3<T> &scalation3) const noexcept;

        ////////////////////////////////////////////////////////////
   /// \brief Transform a point.
   /// 
   /// \param point: Point to transform.
   ///
   /// \return Transformed point.
   ///
   ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Vector3<T> transformPoint(const Vector3<T>& point) const noexcept;

        ////////////////////////////////////////////////////////////
    /// \brief Transform a rectangle.
    ///
    /// Since oriented rectangles isn't provided support for,
    /// the result of this function is always an axis-aligned
    /// rectangle. Which means that if the transform contains a
    /// rotation, the bounding rectangle of the transformed rectangle
    /// is returned.
    ///
    /// \param rect3: Rectangle to transform.
    ///
    /// \return Transformed rectangle.
    ///
    ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Rect3<T> transformRect(const Rect3<T>& rect3) const noexcept;
    };
}

#include "Transform.inl"
