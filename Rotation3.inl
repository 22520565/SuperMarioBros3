#include "Rotation3.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation3<T>::Rotation3(const Angle3<T> &angle3) noexcept(
        noexcept(Rotation2<T>(angle3)) && noexcept(Angle<T>(angle3.z)) && noexcept(T(T())))
        : Rotation2<T>(angle3), angleZ(angle3.z), centerZ(T()) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation3<T>::Rotation3(const Vector3<T> &center) noexcept(
        noexcept(Rotation2<T>(center)) && noexcept(T(center.z)) && noexcept(Angle<T>(Angle<T>::zero())))
        : Rotation2<T>(center), centerZ(center.z), angleZ(Angle<T>::zero()) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation3<T>::Rotation3(const Angle3<T> &angle3, const Vector3<T> &center) noexcept(
        noexcept(Rotation2<T>(angle3, center)) && noexcept(Angle<T>(angle3.z)) && noexcept(T(center.z)))
        : Rotation2<T>(angle3, center), angleZ(angle3.z), centerZ(center.z) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation3<T>::Rotation3(const Rotation2<T> &rotation2) noexcept(
        noexcept(Rotation2<T>(rotation2)) && noexcept(Angle<T>(Angle<T>::zero())) && noexcept(T(T())))
        : Rotation2<T>(rotation2), angleZ(Angle<T>::zero()), centerZ(T()) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation3<T>::Rotation3(const Rotation2<T> &rotation2, const T centerZ) noexcept(
        noexcept(Rotation2<T>(rotation2)) && noexcept(Angle<T>(Angle<T>::zero())) && noexcept(T(centerZ)))
        : Rotation2<T>(rotation2), angleZ(Angle<T>::zero()), centerZ(centerZ) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation3<T>::Rotation3(const Rotation2<T> &rotation2, const Angle<T> angleZ) noexcept(
        noexcept(Rotation2<T>(rotation2)) && noexcept(Angle<T>(angleZ)) && noexcept(T(T())))
        : Rotation2<T>(rotation2), angleZ(angleZ), centerZ(T()) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Rotation3<T>::Rotation3(const Rotation2<T> &rotation2, const Angle<T> angleZ, const T centerZ) noexcept(
        noexcept(Rotation2<T>(rotation2)) && noexcept(Angle<T>(angleZ)) && noexcept(T(centerZ)))
        : Rotation2<T>(rotation2), angleZ(angleZ), centerZ(centerZ) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    template <std::floating_point U>
    constexpr Rotation3<T>::Rotation3(const Rotation3<U> &rotation3) noexcept(
        noexcept(Rotation2<T>(rotation3)) && noexcept(Angle<T>(rotation3.angleZ))
            && noexcept(T(rotation3.centerZ)))
        : Rotation2<T>(rotation3), angleZ(rotation3.angleZ), centerZ(rotation3.centerZ) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Angle3<T> Rotation3<T>::getAngle() const noexcept(
        noexcept(Angle3<T>(Rotation2<T>().getAngle(), Angle<T>()))) {
        return Angle3<T>(this->Rotation2<T>::getAngle(), this->angleZ);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr Vector3<T> Rotation3<T>::getCenter() const noexcept(
        noexcept(Vector3<T>(Rotation2<T>().getCenter(), T()))) {
        return Vector3<T>(this->Rotation2<T>::getCenter(), this->centerZ);
    }
}
