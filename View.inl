#include "View.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr View<T>::View(const Rect3<T> &rect3) noexcept(
        noexcept(Vector3<T>(rect3.getCenter())) && noexcept(Vector3<T>(rect3.getSize())))
        : center(rect3.getCenter()), size(rect3), transformNeedUpdate(true) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr View<T>::View(const Vector3<T> &center, const Vector3<T> &size) noexcept(
        noexcept(Vector3<T>(center)) && noexcept(Vector3<T>(size)))
        : center(center), size(size), transformNeedUpdate(true) {}
}
