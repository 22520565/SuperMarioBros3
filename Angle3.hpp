#pragma once
#include "Angle.hpp"
#include "Angle2.hpp"
#include "stdfloat"
#include <concepts>

namespace game {
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    class Angle3 : public Angle2<T> {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        Angle<T> z = 0_deg;

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a Angle3 of (0, 0, 0).
        ///
        ////////////////////////////////////////////////////////////
        constexpr Angle3() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the angle3 from cartesian coordinates.
        ///
        /// \param x: X coordinate.
        /// \param y: Y coordinate.
        /// \param z: Z coordinate.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit(false) Angle3(const Angle<T> x, const Angle<T> y, const Angle<T> z) noexcept(
            noexcept(Angle2<T>(x, y)) && noexcept(Angle<T>(z)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct an angle3 from an angle2.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Angle3(const Angle2<T> &angle2) noexcept(
            noexcept(Angle2<T>(angle2)) && noexcept(Angle<T>(0.0_deg)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct an angle3 from an angle2 with Z coordinate.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Angle3(const Angle2<T> &angle2, const Angle<T> z) noexcept(
            noexcept(Angle2<T>(angle2)) && noexcept(Angle<T>(z)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the vector from another type of vector.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param angle3: Angle3 to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <std::floating_point U>
        constexpr explicit Angle3(const Angle3<U> &angle3) noexcept(
            noexcept(Angle2<T>(angle3)) && noexcept(Angle<T>(static_cast<Angle<T>>(angle3.z))));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the vector from another type of vector.
        ///
        /// This constructor doesn't replace the move constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param angle3: Angle3 to convert.
        ////////////////////////////////////////////////////////////
        template <std::floating_point U>
        constexpr explicit Angle3(Angle3<U> &&angle3) noexcept(
            noexcept(Angle2<T>(angle3)) && noexcept(Angle<T>(static_cast<Angle<T>>(angle3.z))));

        ////////////////////////////////////////////////////////////
        /// \brief Overload of binary operator ==
        ///
        /// This operator compares strict equality between two vectors.
        ///
        /// \note In C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (an angle).
        /// \param right: Right operand (an angle).
        ///
        /// \return True if \a left is equal to \a right.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr bool
        operator==(const Angle3<T> &left, const Angle3<T> &right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Return the angle's value in degrees.
        ///
        /// \return Angle in degrees.
        ///
        /// \see asRadians.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Vector3<const T &> asDegrees() const noexcept(
            noexcept(Vector3<const T &>(static_cast<const Angle2<T> &>(*this).asDegrees(), this->z.asDegrees())));

        ////////////////////////////////////////////////////////////
        /// \brief Return the angle's value in radians
        ///
        /// \return Angle in radians
        ///
        /// \see asDegrees
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Vector3<T> asRadians() const noexcept(
            noexcept(Vector3<T>(static_cast<const Angle2<T> &>(*this).asRadians(), this->z.asRadians())));

        ////////////////////////////////////////////////////////////
        /// \brief Wrap to a range such that -180° <= angle < 180°
        ///
        /// Similar to a modulo operation, this returns a copy of the angle
        /// constrained to the range [-180°, 180°) == [-Pi, Pi).
        /// The resulting angle represents a rotation which is equivalent to *this.
        ///
        /// \return Signed angle, wrapped to [-180°, 180°)
        ///
        /// \see wrapUnsigned
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Angle3<T> wrapSigned() const noexcept(
            noexcept(Angle3<T>(static_cast<const Angle2<T> &>(*this).wrapSigned(), this->z.wrapSigned())));

        ////////////////////////////////////////////////////////////
        /// \brief Wrap to a range such that 0° <= angle < 360°
        ///
        /// Similar to a modulo operation, this returns a copy of the angle
        /// constrained to the range [0°, 360°) == [0, Tau) == [0, 2*Pi).
        /// The resulting angle represents a rotation which is equivalent to *this.
        ///
        /// \return Unsigned angle, wrapped to [0°, 360°)
        ///
        /// \see wrapSigned
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Angle3<T> wrapUnsigned() const noexcept(
            noexcept(Angle3<T>(static_cast<const Angle2<T> &>(*this).wrapUnsigned(), this->z.wrapUnsigned())));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle3 of (0_deg, 0_deg, 0_deg).
        ///
        /// It's equivalent to (0_rad, 0_rad, 0_rad).
        ///
        /// \return A Angle3 of (0, 0, 0).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle3<T> zero() noexcept(
            noexcept(Angle3<T>(Angle2<T>::zero(), static_cast<Angle<T>>(0.0_deg))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle3 of (1_deg, 1_deg, 1_deg).
        ///
        /// \return A Angle3 of (1_deg, 1_deg, 1_deg).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle3<T> one_deg() noexcept(
            noexcept(Angle3<T>(Angle2<T>::one_deg(), static_cast<Angle<T>>(1.0_deg))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle3 of (1_deg, 0_deg, 0_deg).
        ///
        /// \return A Angle3 of (1_deg, 0_deg, 0_deg).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle3<T> unitX_deg() noexcept(
            noexcept(Angle3<T>(Angle2<T>::unitX_deg(), static_cast<Angle<T>>(0.0_deg))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle3 of (0, 1, 0).
        ///
        /// \return A Angle3 of (0, 1, 0).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle3<T> unitY_deg() noexcept(
            noexcept(Angle3<T>(Angle2<T>::unitY_deg(), static_cast<Angle<T>>(0.0_deg))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle3 of (0, 0, 1).
        ///
        /// \return A Angle3 of (0, 0, 1).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle3<T> unitZ_deg() noexcept(
            noexcept(Angle3<T>(Angle2<T>::zero(), static_cast<Angle<T>>(1.0_deg))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle3 of (1_rad, 1_rad, 1_rad).
        ///
        /// \return A Angle3 of (1_rad, 1_rad, 1_rad).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle3<T> one_rad() noexcept(
            noexcept(Angle3<T>(Angle2<T>::one_rad(), static_cast<Angle<T>>(1.0_rad))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle3 of (1_rad, 0_rad, 0_rad).
        ///
        /// \return A Angle3 of (1_rad, 0_rad, 0_rad).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle3<T> unitX_rad() noexcept(
            noexcept(Angle3<T>(Angle2<T>::unitX_rad(), static_cast<Angle<T>>(0.0_rad))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle3 of (0, 1, 0).
        ///
        /// \return A Angle3 of (0, 1, 0).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle3<T> unitY_rad() noexcept(
            noexcept(Angle3<T>(Angle2<T>::unitY_rad(), static_cast<Angle<T>>(0.0_rad))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle3 of (0, 0, 1).
        ///
        /// \return A Angle3 of (0, 0, 1).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle3<T> unitZ_rad() noexcept(
            noexcept(Angle3<T>(Angle2<T>::zero(), static_cast<Angle<T>>(1.0_rad))));
    };

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator +
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Memberwise addition of both vectors.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle3<T>
    operator+(const Angle3<T> &left, const Angle3<T> &right) noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(left) + static_cast<const Angle2<T> &>(right),
                           left.z + right.z)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator +=
    ///
    /// This operator performs a memberwise addition of both vectors,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Const-reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle3<T> &operator+=(Angle3<T> &left, const Angle3<T> &right) noexcept(
        noexcept(static_cast<Angle2<T> &>(left) += static_cast<const Angle2<T> &>(right))
            && noexcept(left.z += right.z));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of unary operator -
    ///
    /// \param right: Vector to negate.
    ///
    /// \return Memberwise opposite of the vector.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle3<T>
    operator-(const Angle3<T> &right) noexcept(
        noexcept(Angle3<T>(-static_cast<const Angle2<T> &>(right), -right.z)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator -
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Memberwise subtraction of both vectors.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle3<T>
    operator-(const Angle3<T> &left, const Angle3<T> &right) noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(left) - static_cast<const Angle2<T> &>(right),
                           left.z - right.z)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator -=
    ///
    /// This operator performs a memberwise subtraction of both vectors,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle3<T> &operator-=(Angle3<T> &left, const Angle3<T> &right) noexcept(
        noexcept(static_cast<Angle2<T> &>(left) -= static_cast<const Angle2<T> &>(right))
            && noexcept(left.z -= right.z));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Memberwise multiplication by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle3<T>
    operator*(const Angle3<T> &left, const T right) noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(left) * right, left.z *right)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *
    ///
    /// \param left: Left operand (a scalar value).
    /// \param right: Right operand (an angle).
    ///
    /// \return Memberwise multiplication by \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle3<T>
    operator*(const T left, const Angle3<T> &right) noexcept(
        noexcept(Angle3<T>(left * static_cast<const Angle2<T> &>(right), left *right.z)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *=
    ///
    /// This operator performs a memberwise multiplication by \a right,
    /// and assigns the result to \a left.
    ///
    /// \param left:  Left operand (an angle).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Reference to \a left.
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle3<T> &operator*=(Angle3<T> &left, const T right) noexcept(
        noexcept(static_cast<Angle2<T> &>(left) *= right) && noexcept(left.z *= right));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator /
    ///
    /// \param left:  Left operand (an angle).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Memberwise division by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle3<T>
    operator/(const Angle3<T> &left, const T right) noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(left) / right, left.z / right)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator /=
    ///
    /// This operator performs a memberwise division by \a right,
    /// and assigns the result to \a left.
    ///
    /// \param left:  Left operand (an angle).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle3<T> &operator/=(Angle3<T> &left, const T right) noexcept(
        noexcept(static_cast<Angle2<T> &>(left) /= right) && noexcept(left.z /= right));

    // Define common types.

    using Angle3f = Angle3<float>;
    using Angle3d = Angle3<double>;
    using Angle3ld = Angle3<long double>;
    using Angle3f16 = Angle3<std::float16_t>;
    using Angle3bf16 = Angle3<std::bfloat16_t>;
    using Angle3f32 = Angle3<std::float32_t>;
    using Angle3f64 = Angle3<std::float64_t>;
    using Angle3f128 = Angle3<std::float128_t>;
}

#include "Angle3.inl"
