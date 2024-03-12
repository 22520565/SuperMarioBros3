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
    constexpr void Transformable<T>::setRotation(const Angle3<T> &angle3) noexcept {
        this->rotationAngle3 = angle3.wrapUnsigned();
        this->transformNeedUpdate = true;
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr void Transformable<T>::setRotation(const Angle3<T> &angle3, const Vector3<T> &center) noexcept {
        this->rotationAngle3 = angle3.wrapUnsigned();
        this->rotationCenter = center;
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
    constexpr const Angle3<T> &Transformable<T>::getRotationAngle() const noexcept { return this->rotationAngle3; }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Vector3<T> &Transformable<T>::getRotationCenter() const noexcept { return this->rotationCenter; }

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
        this->setRotation(this->rotationAngle3 + angle3);
    }

    template <std::floating_point T>
    constexpr void Transformable<T>::scale(const Vector3<T> &factor) noexcept {
        this->setScalation(Vector3<T>(this->scalationFactor.x * factor.x,
                                      this->scalationCenter.y * factor.y,
                                      this->scalationCenter.z * factor.z));
    }

    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    constexpr const Transform<T> &Transformable<T>::getTransform() const {
        if (this->transformNeedUpdate) [[likely]] {
            const Vector3<T> rad = this->rotationAngle3.asRadians();

            // TODO: calc this
            this->transform = Transform<T>()
                                  .translate(this->position)
                                  .rotate(this->rotationAngle3, this->rotationCenter)
                                  .scale(this->scalationCenter, this->scalationFactor);
            this->transformNeedUpdate = false;
        }

        return this->transform;
    }
}
