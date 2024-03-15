#include "Scalation3.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Scalation3<T>::Scalation3(const Vector3<T> &factor, const Vector3<T> &center) noexcept(
        noexcept(Scalation2<T>(factor, center)) && noexcept(T(factor.z)) && noexcept(T(center.z)))
        : Scalation2<T>(factor, center), factorZ(factor.z), centerZ(center.z) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    template <typename U>
        requires std::is_arithmetic_v<U>
    constexpr Scalation3<T>::Scalation3(const Scalation3<U> &scalation3) noexcept(
        noexcept(Scalation2<T>(scalation3)) && noexcept(T(static_cast<T>(scalation3.factorZ)))
            && noexcept(T(static_cast<T>(scalation3.centerZ))))
        : Scalation2<T>(scalation3), factorZ(static_cast<T>(scalation3.factorZ)),
          centerZ(static_cast<T>(scalation3.centerZ)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> Scalation3<T>::getFactor() const noexcept(
        noexcept(Vector3<T>(Scalation2<T>().getFactor(), T()))) {
        return Vector3<T>(this->Scalation2<T>::getFactor(), this->factorZ);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Vector3<T> Scalation3<T>::getCenter() const noexcept(
        noexcept(Vector3<T>(Scalation2<T>().getCenter(), T()))) {
        return Vector3<T>(this->Scalation2<T>::getCenter(), this->centerZ);
    }
}
