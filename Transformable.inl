#include "Transformable.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::setPosition(const Vector3<T> &newPosition) noexcept {
        this->position = newPosition;
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::setRotation(const Angle3<T> &newAngle3) noexcept {
        this->rotation = newAngle3.wrapUnsigned();
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::setScale(const Vector3<T> &newFactors) noexcept {
        this->scaleFactors = newFactors;
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::setOrigin(const Vector3<T> &newOrigin) noexcept {
        this->origin = newOrigin;
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Vector3<T> &Transformable<T>::getPosition() const noexcept { return this->position; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Angle3<T> &Transformable<T>::getRotation() const noexcept { return this->rotation; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Vector3<T> &Transformable<T>::getScale() const noexcept { return this->scaleFactors; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Vector3<T> &Transformable<T>::getOrigin() const noexcept { return this->origin; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::move(const Vector3<T> &offset) noexcept {
        this->setPosition(this->position + offset);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::rotate(const Angle3<T> &angle3) noexcept {
        this->setRotation(this->rotation + angle3);
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::scale(const Vector3<T> &factors) noexcept {
        this->setScale(Vector3<T>(
            this->scaleFactors.x * factors.x,
            this->scaleFactors.y * factors.y,
            this->scaleFactors.z * factors.z));
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Transform<T> &Transformable<T>::getTransform() const noexcept {
        if (this->transformNeedUpdate) [[likely]] {
            this->transform = Transform<T>()
                                  .translate(this->position - this->origin)
                                  .rotate(this->rotation, this->origin)
                                  .scale(this->scaleFactors, this->origin);
            this->transformNeedUpdate = false;
        }

        return this->transform;
    }
}
