#include "View.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr View<T>::View(const Rect3<T> &rect3, const Rotation3<T> &rotation3) noexcept(
        noexcept(Rect3<T>(rect3)) && noexcept(Rotation3<T>(rotation3)))
        : rect3(rect3), rotation3(rotation3), transformNeedUpdate(true) {}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void View<T>::setRect(const Rect3<T> &newRect3) noexcept {
        this->rect3 = newRect3;
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void View<T>::setRotation(const Rect3<T> &newRotation3) noexcept {
        this->rotation3 = newRotation3;
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Rect3<T> &View<T>::getRect() const noexcept { return this->rect3; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Rotation3<T> &View<T>::getRotation() const noexcept { return this->rotation3; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Transform<T> &View<T>::getTransform() const noexcept {
        if (this->transformNeedUpdate) [[likely]] {
            const Rect3<T> sizeWrappedRect3 = this->rect3.wrapSizeUnsigned();
            this->transform =
                Transform<T>(
                    (sizeWrappedRect3.front / sizeWrappedRect3.width) * static_cast<T>(2.0),
                    static_cast<T>(0.0),
                    ((sizeWrappedRect3.left * (static_cast<T>(-2.0))) / sizeWrappedRect3.width) - static_cast<T>(1.0),
                    static_cast<T>(0.0),
                    static_cast<T>(0.0),
                    (sizeWrappedRect3.front / sizeWrappedRect3.height) * static_cast<T>(2.0),
                    ((sizeWrappedRect3.top * static_cast<T>(-2.0)) / sizeWrappedRect3.height)+ static_cast<T>(1.0),
                    static_cast<T>(0.0),
                    static_cast<T>(0.0),
                    static_cast<T>(0.0),
                    (sizeWrappedRect3.front / sizeWrappedRect3.depth) + static_cast<T>(1.0),
                    -sizeWrappedRect3.front * ((sizeWrappedRect3.front / sizeWrappedRect3.depth)+ static_cast<T>(1.0)),
                    static_cast<T>(0.0),
                    static_cast<T>(0.0),
                    static_cast<T>(1.0),
                    static_cast<T>(0.0))
                    .rotate(this->rotation3);
            this->transformNeedUpdate = false;
        }
        return this->transform;
    }
}
