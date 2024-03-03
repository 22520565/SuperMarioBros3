#pragma once
#include "Transform.hpp"

namespace game {
    class Transformable {
      public:
        static constexpr FLOAT MAX_DEGREESS = 360.0F;

        /// \brief Default constructor
        ///
        /// The default position of a transformable object is (0, 0, 0).
        /// The default rotation of a transformable object in degreess is 0.
        /// The default scale of a transformable object is (1, 1, 1).
        /// The default local origin of a transformable object is (0, 0, 0).
        constexpr Transformable() noexcept = default;

        /// \brief Virtual destructor
        constexpr virtual ~Transformable() noexcept = default;

        /// \brief Set the position of the object.
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable object is (0, 0, 0).
        ///
        /// \param newPosition: New position.
        constexpr void setPosition(const Vector3<FLOAT> &newPosition) noexcept {
            this->transformNeedUpdate = true;
            this->position = newPosition;
        }

        /// \brief Set the orientation of the object.
        /// This function completely overwrites the previous rotation.
        /// See the rotate function to add an angle based on the previous rotation instead.
        /// The default rotation of a transformable object is 0.
        ///
        /// \param angle: New rotation, in degreess
        void setRotation(FLOAT angle) noexcept {
            this->transformNeedUpdate = true;
            angle = std::fmod(angle, MAX_DEGREESS);
            if (angle < 0.0F) [[unlikely]] {
                angle += MAX_DEGREESS;
            }
            this->rotation = angle;
        }

        /// \brief set the scale factors of the object
        ///
        /// This function completely overwrites the previous scale.
        /// See the scale function to add a factor based on the previous scale instead.
        /// The default scale of a transformable object is (1, 1, 1).
        ///
        /// \param factors: New scale factors
        ///
        /// \see scale, getScale
        constexpr void setScaleFactor(const Vector3<FLOAT> &factors) noexcept {
            this->transformNeedUpdate = true;
            this->scaleFactor = factors;
        }

        /// \brief Set the local origin of the object.
        /// The origin of an object defines the center point for
        /// all transformations (position, scale, rotation).
        /// The coordinates of this point must be relative to the
        /// center point of the object, and ignore all
        /// transformations (position, scale, rotation).
        /// The default local origin of a transformable object is (0, 0, 0).
        constexpr void setOrigin(const Vector3<FLOAT> &newOrigin) noexcept {
            this->transformNeedUpdate = true;
            this->origin = newOrigin;
        }

        /// \brief Get the position of the object.
        ///
        /// \return Current position
        constexpr const Vector3<FLOAT> &getPosition() const noexcept { return this->position; }

        /// \brief get the orientation of the object.
        ///
        /// The rotation is always in the range [0, 360).
        ///
        /// \return Current rotation, in degrees.
        constexpr const FLOAT &getRotation() const noexcept { return this->rotation; }

        /// \brief Get the current scale of the object.
        ///
        /// \return Current scale factors.
        constexpr const Vector3<FLOAT> &getScaleFactor() const noexcept { return this->scaleFactor; }

        /// \brief get the local origin of the object.
        ///
        /// \return Current origin.
        constexpr const Vector3<FLOAT> &getOrigin() const noexcept { return this->origin; }

        /// \brief Move the object by a given offset.
        ///
        /// This function adds to the current position of the object,
        /// unlike setPosition which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// object.setPosition(object.getPosition() + offset);
        /// \endcode
        ///
        /// \param offset: Offset
        constexpr void move(const Vector3<FLOAT> &offset) noexcept {
            this->transformNeedUpdate = true;
            this->position += offset;
        }

        /// \brief Rotate the object.
        ///
        /// This function adds to the current rotation of the object,
        /// unlike setRotation which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// object.setRotation(object.getRotation() + angle);
        /// \endcode
        ///
        /// \param angle: Angle of rotation, in degrees
        void rotate(const FLOAT angle) noexcept {
            this->transformNeedUpdate = true;
            this->rotation += angle;
            this->rotation = std::fmod(this->rotation, MAX_DEGREESS);
            if (this->rotation < 0.0F) [[unlikely]] {
                this->rotation += MAX_DEGREESS;
            }
        }

        /// \brief Scale the object.
        ///
        /// This function multiplies the current scale of the object,
        /// unlike setScale which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// sf::Vector2f scale = object.getScale();
        /// object.setScale(scale.x * factor.x, scale.y * factor.y);
        /// \endcode
        ///
        /// \param factor: Scale factors
        constexpr void scale(const Vector3<FLOAT> &factor) noexcept {
            this->transformNeedUpdate = true;
            this->scaleFactor.x *= factor.x;
            this->scaleFactor.y *= factor.y;
            this->scaleFactor.z *= factor.z;
        }

        /// \brief get the combined transform of the object
        ///
        /// \return Transform combining the position/rotation/scale/origin of the object
        constexpr const Transform &getTransform() const {
            if (this->transformNeedUpdate) [[likely]] {
                this->transform = Transform()
                                      .scale(this->scaleFactor, this->origin)
                                      .rotate(this->rotation, this->origin)
                                      .translate(this->position);
                this->transformNeedUpdate = false;
            }
            return this->transform;
        }

      private:
        Vector3<FLOAT> origin = Vector3<FLOAT>(0.0F, 0.0F, 0.0F);
        Vector3<FLOAT> position = Vector3<FLOAT>(0.0F, 0.0F, 0.0F);
        FLOAT rotation = 0.0F;
        Vector3<FLOAT> scaleFactor = Vector3<FLOAT>(1.0F, 1.0F, 1.0F);
        mutable Transform transform = Transform();
        mutable bool transformNeedUpdate = false;
    };
}
