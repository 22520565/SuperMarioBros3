#include "Rect3.hpp"

namespace game {
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect3<T>::Rect3(const Vector3<T> &position, const Vector3<T> &size) noexcept(
        noexcept(Rect2<T>(position, size)) && noexcept(T(position.z)) && noexcept(T(size.z)))
        : Rect2<T>(position, size), front(position.z), depth(size.z) {}

    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    template <typename U>
        requires std::is_arithmetic_v<std::remove_reference_t<U>>
    constexpr Rect3<T>::Rect3(const Rect3<U> &rect3) noexcept(
        noexcept(Rect2<T>(rect3)) && noexcept(T(rect3.front)) && noexcept(T(rect3.depth)))
        : Rect2<T>(rect3), front(rect3.front), depth(rect3.depth) {}
}
