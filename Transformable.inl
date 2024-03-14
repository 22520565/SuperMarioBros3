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
    constexpr void Transformable<T>::setRotation(const Rotation3<T> &newRotation) noexcept {
        this->rotation = newRotation;
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::setScalation(const Vector3<T> &factor) noexcept {
        this->scalationFactor = factor;
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::setScalation(const Vector3<T> &factor, const Vector3<T> &center) noexcept {
        this->scalationFactor = factor;
        this->scalationCenter = center;
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Vector3<T> &Transformable<T>::getPosition() const noexcept { return this->position; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Rotation3<T> &Transformable<T>::getRotation() const noexcept { return this->rotation; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Vector3<T> &Transformable<T>::getScalationFactor() const noexcept { return this->scalationFactor; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Vector3<T> &Transformable<T>::getScalationCenter() const noexcept { return this->scalationCenter; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::move(const Vector3<T> &offset) noexcept {
        this->setPosition(this->position + offset);
    }
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::rotate(const Angle3<T> &angle3) noexcept {
        this->setRotation(Rotation3<T>(
            this->rotation.getAngle() + angle3,
            this->rotation.getCenter()));
    }

    template <std::floating_point T>
    constexpr void Transformable<T>::scale(const Vector3<T> &factor) noexcept {
        this->setScalation(Vector3<T>(this->scalationFactor.x * factor.x,
                                      this->scalationFactor.y * factor.y,
                                      this->scalationFactor.z * factor.z));
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Transform<T> &Transformable<T>::getTransform() const {
        if (this->transformNeedUpdate) [[likely]] {
        //    const Vector3<T> rad = this->rotationAngle3.asRadians();

            // TODO: calc this
            this->transform = Transform<T>()
                                  .translate(this->position)
                                  .rotate(this->rotation)
                                  .scale(this->scalationFactor, this->scalationCenter);
            this->transformNeedUpdate = false;
        }

        return this->transform;
    }
}
