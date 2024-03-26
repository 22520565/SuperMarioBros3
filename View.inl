#include "Angle3.hpp"
#include "Rect3.hpp"
#include "Transform.hpp"
#include "Vector3.hpp"
#include "View.hpp"
#include <concepts>

namespace game {
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr View<T>::View(const Rect3<T>& rect3, const Angle3<T>& angle3) noexcept(
        noexcept(Rect3<T>(rect3)) && noexcept(Angle3<T>(angle3)))
        :rect3(rect3),rotation(angle3){}

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void View<T>::setRotation(const Angle3<T>& angle3) noexcept {
        this->rotation = angle3.wrapUnsigned();
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void View<T>::reset(const Rect3<T> &rect3) noexcept {
        this->rect3 = rect3;
        this->rotation = Angle3<T>::zero();
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void View<T>::reset(const Rect3<T>& rect3, const Angle3<T>& angle3) noexcept {
        this->rect3 = rect3;
        this->setRotation(angle3);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Rect3<T> &View<T>::getRect() const noexcept { return this->rect3; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle3<T>& View<T>::getRotation() const noexcept { return this->rotation; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void View<T>::move(const Vector3<T>& offset) noexcept { 
        this->rect3.left += offset.x;
        this->rect3.top += offset.y;
        this->rect3.front += offset.z;
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void View<T>::rotate(const Angle3<T>& angle3) noexcept {
        this->setRotation(this->rotation + angle3);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Transform<T> &View<T>::getTransform() const noexcept {
        if (this->transformNeedUpdate) [[likely]] {
           // Get a size-wrapped rect3.
            const Rect3<T> sizeWrappedRect3 = this->rect3.wrapSizeUnsigned(); 

            // A temp value for calculation.
            const T tmpVal = (sizeWrappedRect3.front / sizeWrappedRect3.depth) + static_cast<T>(1.0); 

            this->transform = Transform<T>(
                sizeWrappedRect3.front * static_cast<T>(2.0) / sizeWrappedRect3.width,
                static_cast<T>(0.0),
                (sizeWrappedRect3.left * static_cast<T>(-2.0) / sizeWrappedRect3.width) + static_cast<T>(-1.0),
                static_cast<T>(0.0),
                static_cast<T>(0.0),
                sizeWrappedRect3.front * static_cast<T>(2.0) / sizeWrappedRect3.height,
                (sizeWrappedRect3.top * static_cast<T>(-2.0) / sizeWrappedRect3.height) + static_cast<T>(1.0),
                static_cast<T>(0.0),
                static_cast<T>(0.0),
                static_cast<T>(0.0),
                tmpVal,
                (-sizeWrappedRect3.front) * tmpVal,
                static_cast<T>(0.0),
                static_cast<T>(0.0),
                static_cast<T>(1.0),
                static_cast<T>(0.0))
                .rotate(this->rotation, this->rect3.getCenter());
            
            this->transformNeedUpdate = false;
        }
        return this->transform;
    }
}
