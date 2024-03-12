#pragma once
#include "Angle.hpp"

namespace game {
    template <std::floating_point T>
    class Angle2 {
      public:
        Angle<T> x = 0_deg;
        Angle<T> y = 0_deg;

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a Angle2 of (0, 0).
        ///
        ////////////////////////////////////////////////////////////
        constexpr Angle2() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the angle from its angle.
        ///
        /// \param x: X coordinate.
        /// \param y: Y coordinate.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit(false) Angle2(const Angle<T> x, const Angle<T> y) noexcept(
            noexcept(Angle<T>(x)) && noexcept(Angle<T>(y)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the angle from another type of angle.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param angle2: Angle to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <std::floating_point U>
        constexpr explicit Angle2(const Angle2<U> &angle2) noexcept(
            noexcept(Angle<T>(static_cast<Angle<T>>(angle2.x)))
                && noexcept(Angle<T>(static_cast<Angle<T>>(angle2.y))));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the angle from another type of angle.
        ///
        /// This constructor doesn't replace the move constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param angle2: Angle to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <std::floating_point U>
        constexpr explicit Angle2(Angle2<U> &&angle2) noexcept(
            noexcept(Angle<T>(static_cast<Angle<T>>(angle2.x)))
                && noexcept(Angle<T>(static_cast<Angle<T>>(angle2.y))));

        ////////////////////////////////////////////////////////////
        /// \brief Overload of binary operator ==
        ///
        /// This operator compares strict equality between two angles.
        ///
        /// \note Since C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (an angle2).
        /// \param right: Right operand (an angle2).
        ///
        /// \return True if \a left is equal to \a right.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr bool
        operator==(const Angle2<T> &left, const Angle2<T> &right) = default;

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
        constexpr Angle2<T> wrapSigned() const noexcept(
            noexcept(Angle2<T>(this->x.wrapSigned(), this->y.wrapSigned())));

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
        constexpr Angle2<T> wrapUnsigned() const noexcept(
            noexcept(Angle2<T>(this->x.wrapUnsigned(), this->y.wrapUnsigned())));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle2 of (0_deg, 0_deg).
        ///
        /// It's equivalent to (0_rad, 0_rad).
        ///
        /// \return A Angle2 of (0_deg, 0_deg).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle2<T> zero() noexcept(
            noexcept(Angle2<T>(0.0_deg, 0.0_deg)));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle2 of (1_deg, 1_deg).
        ///
        /// \return A Angle2 of (1_deg, 1_deg).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle2<T> one_deg() noexcept(
            noexcept(Angle2<T>(1.0_deg, 1.0_deg)));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle2 of (1_deg, 0_deg).
        ///
        /// \return A Angle2 of (1_deg, 0_deg).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle2<T> unitX_deg() noexcept(
            noexcept(Angle2<T>(1.0_deg, 0.0_deg)));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle2 of (0_deg, 1_deg).
        ///
        /// \return A Angle2 of (0_deg, 1_deg).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle2<T> unitY_deg() noexcept(
            noexcept(Angle2<T>(0.0_deg, 1.0_deg)));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle2 of (1_rad, 1_rad).
        ///
        /// \return A Angle2 of (1_rad, 1_rad).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle2<T> one_rad() noexcept(
            noexcept(Angle2<T>(1.0_rad, 1.0_rad)));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle2 of (1_rad, 0_rad).
        ///
        /// \return A Angle2 of (1_rad, 0_rad).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle2<T> unitX_rad() noexcept(
            noexcept(Angle2<T>(1.0_rad, 0.0_rad)));

        ////////////////////////////////////////////////////////////
        /// \brief Get a Angle2 of (0_rad, 1_rad).
        ///
        /// \return A Angle2 of (0_rad, 1_rad).
        ///
        ////////////////////////////////////////////////////////////
        static consteval Angle2<T> unitY_rad() noexcept(
            noexcept(Angle2<T>(0.0_rad, 1.0_rad)));
    };

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator +
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Memberwise addition of both angles.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    [[nodiscard]]
    constexpr Angle2<T>
    operator+(const Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(left.x + right.x, left.y + right.y)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator +=
    ///
    /// This operator performs a memberwise addition of both angles,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Const-reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle2<T> &operator+=(Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(left.x += right.x) && noexcept(left.y += right.y));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of unary operator -
    ///
    /// \param right: Angle2 to negate.
    ///
    /// \return Memberwise opposite of the angle2.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    [[nodiscard]]
    constexpr Angle2<T>
    operator-(const Angle2<T> &right) noexcept(noexcept(Angle2<T>(-right.x, -right.y)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator -
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Memberwise subtraction of both angles.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    [[nodiscard]]
    constexpr Angle2<T>
    operator-(const Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(left.x - right.x, left.y - right.y)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator -=
    ///
    /// This operator performs a memberwise subtraction of both angle2,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (an angle).
    ///
    /// \return Reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle2<T> &operator-=(Angle2<T> &left, const Angle2<T> &right) noexcept(
        noexcept(left.x -= right.x) && noexcept(left.y -= right.y));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Memberwise multiplication by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    [[nodiscard]]
    constexpr Angle2<T>
    operator*(const Angle2<T> &left, const T right) noexcept(
        noexcept(Angle2<T>(left.x * right, left.y *right)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *
    ///
    /// \param left: Left operand (a scalar value).
    /// \param right: Right operand (an angle).
    ///
    /// \return Memberwise multiplication by \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    [[nodiscard]]
    constexpr Angle2<T>
    operator*(const T left, const Angle2<T> &right) noexcept(
        noexcept(Angle2<T>(left * right.x, left *right.y)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator *=
    ///
    /// This operator performs a memberwise multiplication by \a right,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle2<T> &operator*=(Angle2<T> &left, const T right) noexcept(
        noexcept(left.x *= right) && noexcept(left.y *= right));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator /
    ///
    /// \note Avoid 0 in the right operand.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Memberwise division by \a right.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    [[nodiscard]]
    constexpr Angle2<T>
    operator/(const Angle2<T> &left, const T right) noexcept(
        noexcept(Angle2<T>(left.x / right, left.y / right)));

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator /=
    ///
    /// \note Avoid 0 in the right operand.
    ///
    /// This operator performs a memberwise division by \a right,
    /// and assigns the result to \a left.
    ///
    /// \param left: Left operand (an angle).
    /// \param right: Right operand (a scalar value).
    ///
    /// \return Reference to \a left.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle2<T> &operator/=(Angle2<T> &left, const T right) noexcept(
        noexcept(left.x /= right) && noexcept(left.y /= right));

    // Define common types.

    using Angle2f = Angle2<float>;
    using Angle2d = Angle2<double>;
    using Angle2ld = Angle2<long double>;
    using Angle2f16 = Angle2<std::float16_t>;
    using Angle2bf16 = Angle2<std::bfloat16_t>;
    using Angle2f32 = Angle2<std::float32_t>;
    using Angle2f64 = Angle2<std::float64_t>;
    using Angle2f128 = Angle2<std::float128_t>;
}

#include "Angle2.inl"
