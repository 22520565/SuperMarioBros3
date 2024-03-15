#include "Rect2.hpp"
#include "Rect3.hpp"
#include "Vector3.hpp"
#include <type_traits>

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect3<T>::Rect3(const Vector3<T> &position, const Vector3<T> &size) noexcept(
        noexcept(Rect2<T>(position, size)) && noexcept(T(position.z)) && noexcept(T(size.z)))
        : Rect2<T>(position, size), front(position.z), depth(size.z) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect3<T>::Rect3(const Rect2<T> &rect2) noexcept(
        noexcept(Rect2<T>(rect2)) && noexcept(T(T())))
        : Rect2<T>(rect2), front(T()), depth(T()) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect3<T>::Rect3(const Rect2<T> &rect2, const T front, const T depth) noexcept(
        noexcept(Rect2<T>(rect2)) && noexcept(T(front)) && noexcept(T(depth)))
        : Rect2<T>(rect2), front(front), depth(depth) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    template <typename U>
        requires std::is_arithmetic_v<std::remove_reference_t<U>>
    constexpr Rect3<T>::Rect3(const Rect3<U> &rect3) noexcept(
        noexcept(Rect2<T>(rect3)) && noexcept(T(static_cast<T>(rect3.front)))
            && noexcept(T(static_cast<T>(rect3.depth))))
        : Rect2<T>(rect3), front(static_cast<T>(rect3.front)), depth(static_cast<T>(rect3.depth)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector3<T> Rect3<T>::getPosition() const noexcept {
        return Vector3<T>(this->Rect2<T>::getPosition(), this->front);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector3<T> Rect3<T>::getSize() const noexcept {
        return Vector3<T>(this->Rect2<T>::getSize(), this->depth);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect3<T> Rect3<T>::wrapSizeUnsigned() const noexcept(
        noexcept(Rect3<T>(Rect2<T>::wrapSizeUnsigned(), T(), T()))) {
        const Rect3<T> newRect3 = Rect3<T>(this->Rect2<T>::wrapSizeUnsigned(), this->front, this->depth);

        if (newRect3.depth < T()) [[unlikely]] {
            newRect3.front += newRect3.depth;
            newRect3.depth = -newRect3.depth;
        }

        return newRect3;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr bool Rect3<T>::contains(const Vector3<T> &point) const noexcept(
        noexcept(wrapSizeUnsigned()) && noexcept(Rect2<T>::contains(point))) {
        const Rect3<T> wrappedSizeRect3 = this->wrapSizeUnsigned();
        return wrappedSizeRect3.Rect2<T>::contains(point) &&
               (point.z >= wrappedSizeRect3.front) &&
               (point.z < (wrappedSizeRect3.front + wrappedSizeRect3.depth));
    }
}
