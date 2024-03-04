#pragma once
#include "Transform.hpp"
#include "Rotation.hpp"
#include "Scalation.hpp"

namespace game {
	class Transformable {
	public:
		/// \brief Default constructor.
		constexpr Transformable() noexcept = default;

		/// \brief Virtual destructor
		constexpr virtual ~Transformable() noexcept = default;

		/// \brief Set the position of the object.
		/// This function completely overwrites the previous position.
		/// See the move function to apply an offset based on the previous position instead.
		/// The default position of a transformable object is (0, 0, 0).
		///
		/// \param newPosition: New position.
		constexpr void setPosition(const Vector3<FLOAT>& newPosition) noexcept {
			this->transformNeedUpdate = true;
			this->position = newPosition;
		}

		/// \brief Set the rotation of the object.
		/// This function completely overwrites the previous rotation.
		/// See the rotate function to add an angle based on the previous rotation instead.
		/// 
		/// \param newRotation: New rotation
		constexpr void setRotation(const Rotation& newRotation) noexcept {
			this->transformNeedUpdate = true;
			this->rotation = newRotation;
		}

		/// \brief Set the scalation of the object.
		///
		/// This function completely overwrites the previous scalation.
		/// See the scale function to add a factor based on the previous scale instead.
		///
		/// \param newScale: New scale
		constexpr void setScalation(const Scalation& newScalation) noexcept {
			this->transformNeedUpdate = true;
			this->scalation = newScalation;
		}

		/// \brief Get the position of the object.
		///
		/// \return Current position.
		[[nodiscard("Use the return value of this method or remove this redundant statement!")]]
		constexpr const Vector3<FLOAT>& getPosition() const noexcept { return this->position; }

		/// \brief Get the rotation of the object.
		///
		/// \return Current rotation.
		[[nodiscard("Use the return value of this method or remove this redundant statement!")]]
		constexpr const Rotation& getRotation() const noexcept { return this->rotation; }

		/// \brief Get the current scalation of the object.
		///
		/// \return Current scalation
		[[nodiscard("Use the return value of this method or remove this redundant statement!")]]
		constexpr const Scalation& getScalation() const noexcept { return this->scalation; }

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
		constexpr void move(const Vector3<FLOAT>& offset) noexcept {
			if (!this->transformNeedUpdate) [[likely]] {
				this->transform = this->transform.translate(offset);
				}
			this->position += offset;
		}

		/// \brief Rotate the object.
		///
		/// This function adds to the current rotation of the object,
		/// unlike setRotation which overwrites it.
		/// Thus, it is equivalent to the following code:
		/// \code
		/// Rotation rotation = object.getRotation();
		/// object.setRotation(Rotation(rotation.getAngle() + angle, rotation.axis));
		/// \endcode
		///
		/// \param addingAngle: Angle of rotation, in degrees.
		void rotate(const FLOAT addingAngle) noexcept {
			if (!this->transformNeedUpdate) [[likely]] {
				this->transform = this->transform.rotate(addingAngle, this->rotation.axis);
				}
			this->rotation.addAngle(addingAngle);
		}

		/// \brief Scale the object.
		///
		/// This function multiplies the current scale of the object,
		/// unlike setScale which overwrites it.
		/// Thus, it is equivalent to the following code:
		/// \code
		/// Scalation scalation = object.getScalation();
		/// object.setScalation(Scalation(Vector3(scalation.factor.x * factorToScale.x,
		///														scalation.factor.y * factorToScale.y,
		///														scalation.factor.z * factorToScale.z),
		///												scalation.center);
		/// \endcode
		///
		/// \param factorToScale: Scale factors.
		constexpr void scale(const Vector3<FLOAT>& factorToScale) noexcept {
			if (!this->transformNeedUpdate)
			{
				this->transform = this->transform.scale(factorToScale, this->scalation.center);
			}
			this->scalation.factor.x *= factorToScale.x;
			this->scalation.factor.y *= factorToScale.y;
			this->scalation.factor.z *= factorToScale.z;
		}

		/// \brief get the combined transform of the object
		///
		/// \return Transform combining the position/rotation/scale of the object
		constexpr const Transform& getTransform() const {
			if (this->transformNeedUpdate) [[likely]] {
				this->transform = Transform()
					.scale(this->scalation.factor, this->scalation.center)
					.rotate(this->rotation.getAngle(), this->rotation.axis)
					.translate(this->position);
				this->transformNeedUpdate = false;
				}
			return this->transform;
		}

	private:
		Vector3<FLOAT> position = Vector3<FLOAT>(0.0F, 0.0F, 0.0F);
		Rotation rotation = Rotation();
		Scalation scalation = Scalation();
		mutable Transform transform = Transform();
		mutable bool transformNeedUpdate = false;
	};
}
