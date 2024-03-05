#pragma once
#include "Transform.hpp"
#include <cmath>
#include <cstdint>

namespace game {
    class Transformable {
      public:
        static constexpr FLOAT maxDegrees = 360.0F;

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Transformable() noexcept = default;

        ////////////////////////////////////////////////////////////
        /// \brief Virtual destructor
        ///
        ////////////////////////////////////////////////////////////
        constexpr virtual ~Transformable() noexcept = default;

        ////////////////////////////////////////////////////////////
        /// \brief Set the position of the object.
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable object is (0, 0, 0).
        ///
        /// \param newPosition: New position.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setPosition(const Vector3<FLOAT> &newPosition) noexcept {
            this->transform = this->transform.translate(newPosition - this->position);
            this->position = newPosition;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Set the rotation of the object.
        ///
        /// This function completely overwrites the previous rotation.
        /// See the rotate function to add an angle based on the previous rotation instead.
        /// The default rotation angles of a transformable object is (0, 0, 0).
        /// The default coordinate of rotation center point of a transformable object is (0, 0, 0).
        ///
        /// \param angle: Rotation angle in three dimensions, in degrees.
        /// \param center: Coordinate of the center point to rotate.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setRotation(Vector3<FLOAT> angle, const Vector3<FLOAT> &center) noexcept {
            angle = Vector3(std::fmod(angle.x, maxDegrees),
                            std::fmod(angle.y, maxDegrees),
                            std::fmod(angle.z, maxDegrees));
            if (angle.x < 0.0F) [[unlikely]] {
                angle.x += maxDegrees;
            }
            if (angle.y < 0.0F) [[unlikely]] {
                angle.y += maxDegrees;
            }
            if (angle.z < 0.0F) [[unlikely]] {
                angle.z += maxDegrees;
            }
            this->transform = this->transform
                                  .rotate(-this->rotationAngle, this->rotationCenter)
                                  .rotate(angle, center);
            this->rotationAngle = angle;
            this->rotationCenter = center;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Set the scalation of the object.
        ///
        /// This function completely overwrites the previous scalation.
        /// See the scale function to add a factor based on the previous scale instead.
        /// The default scalation factors of a transformable object is (1, 1, 1).
        /// The default coordinate of scalation center point of a transformable object is (0, 0, 0).
        ///
        /// \param factor: Scaling factor in three dimensions.
        /// \param center: Coordinate of the center point to scale.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setScalation(const Vector3<FLOAT> &factors, const Vector3<FLOAT> &center) noexcept {
            this->transform = this->transform.scale(factors, center);
            this->scalationFactor = factors;
            this->scalationCenter = center;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get the position of the object.
        ///
        /// \return Current position.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard("Use the return value of this method or remove this redundant statement!")]]
        constexpr const Vector3<FLOAT> &getPosition() const noexcept { return this->position; }

        ////////////////////////////////////////////////////////////
        /// \brief Get the rotation angle of the object.
        /// The value of every angle is always in the range [0, 360).
        ///
        /// \return Current rotation angle in three dimensions, in degrees.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard("Use the return value of this method or remove this redundant statement!")]]
        constexpr const Vector3<FLOAT> &getRotationAngle() const noexcept { return this->rotationAngle; }

        ////////////////////////////////////////////////////////////
        /// \brief Get the rotation center point of the object.
        ///
        /// \return Coordinate of the current rotation center point.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard("Use the return value of this method or remove this redundant statement!")]]
        constexpr const Vector3<FLOAT> &getRotationCenter() const noexcept { return this->rotationCenter; }

        ////////////////////////////////////////////////////////////
        /// \brief Get the current scalation factor of the object.
        ///
        /// \return Current scaling factor in three dimensions.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard("Use the return value of this method or remove this redundant statement!")]]
        constexpr const Vector3<FLOAT> &getScalationFactor() const noexcept { return this->scalationFactor; }

        ////////////////////////////////////////////////////////////
        /// \brief Get the coordinate of the current scalation center of the object.
        ///
        /// \return Current scalation center.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard("Use the return value of this method or remove this redundant statement!")]]
        constexpr const Vector3<FLOAT> &getScalationCenter() const noexcept { return this->scalationCenter; }

        ////////////////////////////////////////////////////////////
        /// \brief Move the object by a given offset.
        ///
        /// This function adds to the current position of the object,
        /// unlike setPosition which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// object.setPosition(object.getPosition() + offset);
        /// \endcode
        ///
        /// \param offset: Offset.
        ////////////////////////////////////////////////////////////
        constexpr void move(const Vector3<FLOAT> &offset) noexcept {
            this->transform = this->transform.translate(offset);
            this->position += offset;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Rotate the object.
        ///
        /// This function adds angle to the current rotation angle of the object,
        /// unlike setRotation which overwrites it. The rotation center point stays remain.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// object.setRotation(object.getRotationAngle() + angle, object.getRotationCenter());
        /// \endcode
        ///
        /// \param angle: Rotation angle in three dimensions, in degrees.
        ///
        ////////////////////////////////////////////////////////////
        void rotate(Vector3<FLOAT> angle) noexcept {
            angle = Vector3(std::fmod(angle.x, maxDegrees),
                            std::fmod(angle.y, maxDegrees),
                            std::fmod(angle.z, maxDegrees));
            if (angle.x < 0.0F) [[unlikely]] {
                angle.x += maxDegrees;
            }
            if (angle.y < 0.0F) [[unlikely]] {
                angle.y += maxDegrees;
            }
            if (angle.z < 0.0F) [[unlikely]] {
                angle.z += maxDegrees;
            }
            this->transform = this->transform.rotate(angle, this->rotationCenter);
            this->rotationAngle += angle;
            if (this->rotationAngle.x >= maxDegrees) [[unlikely]] {
                this->rotationAngle.x -= maxDegrees;
            }
            if (this->rotationAngle.y >= maxDegrees) [[unlikely]] {
                this->rotationAngle.y -= maxDegrees;
            }
            if (this->rotationAngle.z >= maxDegrees) [[unlikely]] {
                this->rotationAngle.z -= maxDegrees;
            }
        }

        ////////////////////////////////////////////////////////////
        /// \brief Scale the object.
        ///
        /// This function multiplies factors with the current scale factors of the object,
        /// unlike setScale which overwrites it. The scalation center point stays remain.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// auto scalationFactor = object.getScalationFactor();
        /// scalationFactor.x*=factor.x;
        /// scalationFactor.y*=factor.y;
        /// scalationFactor.z*=factor.z;
        /// object.setScalation(scalationFactor, object.getScalationCenter());
        /// \endcode
        ///
        /// \param factor: Scaling factor in three dimensions.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void scale(const Vector3<FLOAT> &factor) noexcept {
            this->transform = this->transform.scale(factor);
            this->scalationFactor.x *= factor.x;
            this->scalationFactor.y *= factor.y;
            this->scalationFactor.z *= factor.z;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get the combined transform of the object.
        ///
        /// \return Transform combining the position/rotation/scalation of the object.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard("Use the return value of this method or remove this redundant statement!")]]
        constexpr const Transform &getTransform() const { return this->transform; }

      private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        Vector3<FLOAT> position = Vector3<FLOAT>::zero();        // Position of the object.
        Vector3<FLOAT> rotationAngle = Vector3<FLOAT>::zero();   // Rotation angle of the object.
        Vector3<FLOAT> rotationCenter = Vector3<FLOAT>::zero();  // Rotation center point of the object.
        Vector3<FLOAT> scalationFactor = Vector3<FLOAT>::one();  // Scalation factor of the object.
        Vector3<FLOAT> scalationCenter = Vector3<FLOAT>::zero(); // Scalation center point of the object.
        Transform transform = Transform();                       // Combined transformation of the object.
    };
}
