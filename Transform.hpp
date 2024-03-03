#pragma once
#include "Vector3.hpp"
#include <cmath>

namespace game {
    class Transform final {
      public:
        FLOAT f00 = 1.0F;
        FLOAT f01 = 0.0F;
        FLOAT f02 = 0.0F;
        FLOAT f03 = 0.0F;
        FLOAT f10 = 0.0F;
        FLOAT f11 = 1.0F;
        FLOAT f12 = 0.0F;
        FLOAT f13 = 0.0F;
        FLOAT f20 = 0.0F;
        FLOAT f21 = 0.0F;
        FLOAT f22 = 1.0F;
        FLOAT f23 = 0.0F;
        FLOAT f30 = 0.0F;
        FLOAT f31 = 0.0F;
        FLOAT f32 = 0.0F;
        FLOAT f33 = 1.0F;

        /// \brief Default constructor.
        ///
        /// Creates an identity transform (a transform that does nothing).
        constexpr Transform() noexcept = default;

        /// \brief Construct a transform from a 4x4 matrix.
        ///
        /// \param f00: Element (0, 0) of the matrix
        /// \param f01: Element (0, 1) of the matrix
        /// \param f02: Element (0, 2) of the matrix
        /// \param f03: Element (0, 3) of the matrix
        /// \param f10: Element (1, 0) of the matrix
        /// \param f11: Element (1, 1) of the matrix
        /// \param f12: Element (1, 2) of the matrix
        /// \param f13: Element (1, 3) of the matrix
        /// \param f20: Element (2, 0) of the matrix
        /// \param f21: Element (2, 1) of the matrix
        /// \param f22: Element (2, 2) of the matrix
        /// \param f23: Element (2, 3) of the matrix
        /// \param f30: Element (3, 0) of the matrix
        /// \param f31: Element (3, 1) of the matrix
        /// \param f32: Element (3, 2) of the matrix
        /// \param f33: Element (3, 3) of the matrix
        constexpr Transform(const FLOAT f00, const FLOAT f01, const FLOAT f02, const FLOAT f03,
                            const FLOAT f10, const FLOAT f11, const FLOAT f12, const FLOAT f13,
                            const FLOAT f20, const FLOAT f21, const FLOAT f22, const FLOAT f23,
                            const FLOAT f30, const FLOAT f31, const FLOAT f32, const FLOAT f33) noexcept
            : f00(f00), f01(f01), f02(f02), f03(f03),
              f10(f10), f11(f11), f12(f12), f13(f13),
              f20(f20), f21(f21), f22(f22), f23(f23),
              f30(f30), f31(f31), f32(f32), f33(f33) {}

        /// \brief Convert to D3DXMATRIX
        explicit(false) operator D3DXMATRIX() const {
            /*return D3DXMATRIX(
                f00, f01, f02, f03,
                f10, f11, f12, f13,
                f20, f21, f22, f23,
                f30, f31, f32, f33);*/
            return D3DXMATRIX(
                f00, f10, f20, f30,
                f01, f11, f21, f31,
                f02, f12, f22, f32,
                f03, f13, f23, f33);
        }

        /// \brief Combine the current transform with another one.
        ///
        /// \param transform: Transform to combine with this transform.
        ///
        /// \return The result of combination.
        [[nodiscard]]
        constexpr Transform combine(const Transform &transform) const noexcept {
            return Transform(
                (this->f00 * transform.f00) + (this->f01 * transform.f10) + (this->f02 * transform.f20) + (this->f03 * transform.f30),
                (this->f00 * transform.f01) + (this->f01 * transform.f11) + (this->f02 * transform.f21) + (this->f03 * transform.f31),
                (this->f00 * transform.f02) + (this->f01 * transform.f12) + (this->f02 * transform.f22) + (this->f03 * transform.f32),
                (this->f00 * transform.f03) + (this->f01 * transform.f13) + (this->f02 * transform.f23) + (this->f03 * transform.f33),
                (this->f10 * transform.f00) + (this->f11 * transform.f10) + (this->f12 * transform.f20) + (this->f13 * transform.f30),
                (this->f10 * transform.f01) + (this->f11 * transform.f11) + (this->f12 * transform.f21) + (this->f13 * transform.f31),
                (this->f10 * transform.f02) + (this->f11 * transform.f12) + (this->f12 * transform.f22) + (this->f13 * transform.f32),
                (this->f10 * transform.f03) + (this->f11 * transform.f13) + (this->f12 * transform.f23) + (this->f13 * transform.f33),
                (this->f20 * transform.f00) + (this->f21 * transform.f10) + (this->f22 * transform.f20) + (this->f23 * transform.f30),
                (this->f20 * transform.f01) + (this->f21 * transform.f11) + (this->f22 * transform.f21) + (this->f23 * transform.f31),
                (this->f20 * transform.f02) + (this->f21 * transform.f12) + (this->f22 * transform.f22) + (this->f23 * transform.f32),
                (this->f20 * transform.f03) + (this->f21 * transform.f13) + (this->f22 * transform.f23) + (this->f23 * transform.f33),
                (this->f30 * transform.f00) + (this->f31 * transform.f10) + (this->f32 * transform.f20) + (this->f33 * transform.f30),
                (this->f30 * transform.f01) + (this->f31 * transform.f11) + (this->f32 * transform.f21) + (this->f33 * transform.f31),
                (this->f30 * transform.f02) + (this->f31 * transform.f12) + (this->f32 * transform.f22) + (this->f33 * transform.f32),
                (this->f30 * transform.f03) + (this->f31 * transform.f13) + (this->f32 * transform.f23) + (this->f33 * transform.f33));
        }

        /// \brief Combine the current transform with a translation.
        /// \param offset: Translation offset to apply.
        ///
        /// \return The result of combination.
        [[nodiscard]]
        constexpr Transform translate(const Vector3<FLOAT> &offset) const noexcept {
            const Transform translationTransform = Transform(
                1.0F, 0.0F, 0.0F, offset.x,
                0.0F, 1.0F, 0.0F, offset.y,
                0.0F, 0.0F, 1.0F, offset.z,
                0.0F, 0.0F, 0.0F, 1.0F);
            return this->combine(translationTransform);
        }

        /// \brief Combine the current transform with a rotation
        /// \param angle: Rotation angle, in degrees.
        ///
        /// \return The result of combination.
        [[nodiscard]]
        constexpr Transform rotate(const FLOAT angle, const Vector3<FLOAT> &center) const noexcept {
            const Transform rotationTransform = Transform(
                std::cos(angle) + ((1.0F - std::cos(angle)) * center.x * center.x),
                ((1.0F - std::cos(angle)) * center.x * center.y) - (std::sin(angle) * center.z),
                ((1.0F - std::cos(angle)) * center.x * center.z) + (sin(angle) * center.y),
                0.0F,
                ((1.0F - std::cos(angle)) * center.x * center.y) + (std::sin(angle) * center.z),
                std::cos(angle) + ((1.0F - std::cos(angle)) * center.y * center.y),
                ((1.0F - std::cos(angle)) * center.y * center.z) - (std::sin(angle) * center.x),
                0.0F,
                ((1.0F - std::cos(angle)) * center.x * center.z) - (std::sin(angle) * center.y),
                ((1.0F - std::cos(angle)) * center.y * center.z) + (std::sin(angle) * center.x),
                std::cos(angle) + ((1.0F - std::cos(angle)) * center.z * center.z),
                0.0F,
                0.0F, 0.0F, 0.0F, 1.0F);
            return this->combine(rotationTransform);
        }

        /// \brief Combine the current transform with a scaling.
        /// \param factors: Scaling factors
        /// \param center: Center of scaling
        ///
        /// \return The result of combination.
        [[nodiscard]]
        constexpr Transform scale(const Vector3<FLOAT> &factors, const Vector3<FLOAT> &center) const noexcept {
            const Transform scalingTransform = Transform(
                factors.x, 0.0F, 0.0F, (1.0F - factors.x) * center.x,
                0.0F, factors.y, 0.0F, (1.0F - factors.y) * center.y,
                0.0F, 0.0F, factors.z, (1.0F - factors.z) * center.z,
                0.0F, 0.0F, 0.0F, 1.0F);
            return this->combine(scalingTransform);
        }
    };
}
