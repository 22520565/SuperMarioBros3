#include "Angle3.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle3<T>::Angle3(const Angle<T> x, const Angle<T> y, const Angle<T> z) noexcept(
        noexcept(Angle2<T>(x, y)) && noexcept(Angle<T>(z))) : Angle2<T>(x, y), z(z) {}

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle3<T>::Angle3(const Angle2<T> &angle2) noexcept(
        noexcept(Angle2<T>(angle2)) && noexcept(Angle<T>(0.0_deg))) : Angle2<T>(angle2), z(0.0_deg) {}

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle3<T>::Angle3(const Angle2<T> &angle2, const Angle<T> z) noexcept(
        noexcept(Angle2<T>(angle2)) && noexcept(Angle<T>(z))) : Angle2<T>(angle2), z(z) {}

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    template <std::floating_point U>
    constexpr Angle3<T>::Angle3(const Angle3<U> &angle3) noexcept(
        noexcept(Angle2<T>(angle3)) && noexcept(Angle<T>(static_cast<Angle<T>>(angle3.z))))
        : Angle2<T>(angle3), z(static_cast<Angle<T>>(angle3.z)) {}

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    template <std::floating_point U>
    constexpr Angle3<T>::Angle3(Angle3<U> &&angle3) noexcept(
        noexcept(Angle2<T>(angle3)) && noexcept(Angle<T>(static_cast<Angle<T>>(angle3.z))))
        : Angle2<T>(angle3), z(static_cast<Angle<T>>(angle3.z)) {}

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Vector3<const T &> Angle3<T>::asDegrees() const noexcept(
        noexcept(Vector3<const T &>(static_cast<const Angle2<T> &>(*this).asDegrees(), this->z.asDegrees()))) {
        return Vector3<const T &>(static_cast<const Angle2<T> &>(*this).asDegrees(), this->z.asDegrees());
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Vector3<T> Angle3<T>::asRadians() const noexcept(
        noexcept(Vector3<T>(static_cast<const Angle2<T> &>(*this).asRadians(), this->z.asRadians()))) {
        return Vector3<T>(static_cast<const Angle2<T> &>(*this).asRadians(), this->z.asRadians());
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle3<T> Angle3<T>::wrapSigned() const noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(*this).wrapSigned(), this->z.wrapSigned()))) {
        return Angle3<T>(static_cast<const Angle2<T> &>(*this).wrapSigned(), this->z.wrapSigned());
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    [[nodiscard]]
    constexpr Angle3<T> Angle3<T>::wrapUnsigned() const noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(*this).wrapUnsigned(), this->z.wrapUnsigned()))) {
        return Angle3<T>(static_cast<const Angle2<T> &>(*this).wrapUnsigned(), this->z.wrapUnsigned());
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle3<T> Angle3<T>::zero() noexcept(
        noexcept(Angle3<T>(Angle2<T>::zero(), static_cast<Angle<T>>(0.0_deg)))) {
        return Angle3<T>(Angle2<T>::zero(), static_cast<Angle<T>>(0.0_deg));
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle3<T> Angle3<T>::one_deg() noexcept(
        noexcept(Angle3<T>(Angle2<T>::one_deg(), static_cast<Angle<T>>(1.0_deg)))) {
        return Angle3<T>(Angle2<T>::one_deg(), static_cast<Angle<T>>(1.0_deg));
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle3<T> Angle3<T>::unitX_deg() noexcept(
        noexcept(Angle3<T>(Angle2<T>::unitX_deg(), static_cast<Angle<T>>(0.0_deg)))) {
        return Angle3<T>(Angle2<T>::unitX_deg(), static_cast<Angle<T>>(0.0_deg));
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle3<T> Angle3<T>::unitY_deg() noexcept(
        noexcept(Angle3<T>(Angle2<T>::unitY_deg(), static_cast<Angle<T>>(0.0_deg)))) {
        return Angle3<T>(Angle2<T>::unitY_deg(), static_cast<Angle<T>>(0.0_deg));
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle3<T> Angle3<T>::unitZ_deg() noexcept(
        noexcept(Angle3<T>(Angle2<T>::zero(), static_cast<Angle<T>>(1.0_deg)))) {
        return Angle3<T>(Angle2<T>::zero(), static_cast<Angle<T>>(1.0_deg));
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle3<T> Angle3<T>::one_rad() noexcept(
        noexcept(Angle3<T>(Angle2<T>::one_rad(), static_cast<Angle<T>>(1.0_rad)))) {
        return Angle3<T>(Angle2<T>::one_rad(), static_cast<Angle<T>>(1.0_rad));
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle3<T> Angle3<T>::unitX_rad() noexcept(
        noexcept(Angle3<T>(Angle2<T>::unitX_rad(), static_cast<Angle<T>>(0.0_rad)))) {
        return Angle3<T>(Angle2<T>::unitX_rad(), static_cast<Angle<T>>(0.0_rad));
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle3<T> Angle3<T>::unitY_rad() noexcept(
        noexcept(Angle3<T>(Angle2<T>::unitY_rad(), static_cast<Angle<T>>(0.0_rad)))) {
        return Angle3<T>(Angle2<T>::unitY_rad(), static_cast<Angle<T>>(0.0_rad));
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    consteval Angle3<T> Angle3<T>::unitZ_rad() noexcept(
        noexcept(Angle3<T>(Angle2<T>::zero(), static_cast<Angle<T>>(1.0_rad)))) {
        return Angle3<T>(Angle2<T>::zero(), static_cast<Angle<T>>(1.0_rad));
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle3<T> operator+(const Angle3<T> &left, const Angle3<T> &right) noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(left) + static_cast<const Angle2<T> &>(right),
                           left.z + right.z))) {
        return Angle3<T>(static_cast<const Angle2<T> &>(left) + static_cast<const Angle2<T> &>(right),
                         left.z + right.z);
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle3<T> &operator+=(Angle3<T> &left, const Angle3<T> &right) noexcept(
        noexcept(static_cast<Angle2<T> &>(left) += static_cast<const Angle2<T> &>(right))
            && noexcept(left.z += right.z)) {
        static_cast<Angle2<T> &>(left) += static_cast<const Angle2<T> &>(right);
        left.z += right.z;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle3<T> operator-(const Angle3<T> &right) noexcept(
        noexcept(Angle3<T>(-static_cast<const Angle2<T> &>(right), -right.z))) {
        return Angle3<T>(-static_cast<const Angle2<T> &>(right), -right.z);
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle3<T> operator-(const Angle3<T> &left, const Angle3<T> &right) noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(left) - static_cast<const Angle2<T> &>(right),
                           left.z - right.z))) {
        return Angle3<T>(static_cast<const Angle2<T> &>(left) - static_cast<const Angle2<T> &>(right),
                         left.z - right.z);
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle3<T> &operator-=(Angle3<T> &left, const Angle3<T> &right) noexcept(
        noexcept(static_cast<Angle2<T> &>(left) -= static_cast<const Angle2<T> &>(right))
            && noexcept(left.z -= right.z)) {
        static_cast<Angle2<T> &>(left) -= static_cast<const Angle2<T> &>(right);
        left.z -= right.z;
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle3<T> operator*(const Angle3<T> &left, const T right) noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(left) * right, left.z *right))) {
        return Angle3<T>(static_cast<const Angle2<T> &>(left) * right, left.z * right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle3<T> operator*(const T left, const Angle3<T> &right) noexcept(
        noexcept(Angle3<T>(left * static_cast<const Angle2<T> &>(right), left *right.z))) {
        return Angle3<T>(left * static_cast<const Angle2<T> &>(right), left * right.z);
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle3<T> &operator*=(Angle3<T> &left, const T right) noexcept(
        noexcept(static_cast<Angle2<T> &>(left) *= right) && noexcept(left.z *= right)) {
        static_cast<Angle2<T> &>(left) *= right;
        left.z *= right;
        return left;
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr Angle3<T> operator/(const Angle3<T> &left, const T right) noexcept(
        noexcept(Angle3<T>(static_cast<const Angle2<T> &>(left) / right, left.z / right))) {
        return Angle3<T>(static_cast<const Angle2<T> &>(left) / right, left.z / right);
    }

    ////////////////////////////////////////////////////////////
    template <typename T> requires std::is_floating_point_v<std::remove_reference_t<T>>
    constexpr const Angle3<T> &operator/=(Angle3<T> &left, const T right) noexcept(
        noexcept(static_cast<Angle2<T> &>(left) /= right) && noexcept(left.z /= right)) {
        static_cast<Angle2<T> &>(left) /= right;
        left.z /= right;
        return left;
    }
}
