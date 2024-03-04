#pragma once
#include <D3DX10.h>
#include "Vector3.hpp"

namespace game {
	class Rotation final {
	public:
		static constexpr short MAX_DEGREESS = 360;

		/// The unit vector of the rotation axis.
		Vector3<FLOAT> axis = Vector3<FLOAT>::zero;

		/// \brief Default constructor.
		///
		/// The default rotation angle of a transformable object in degreess is 0.
		/// The default unit vector of the rotation axis is (0, 0, 0).
		constexpr Rotation() noexcept = default;

		constexpr Rotation(const FLOAT angle, const Vector3<FLOAT>& axis) noexcept
			: angle(angle), axis(axis) {}

		constexpr void setAngle(FLOAT newAngle) noexcept {
			newAngle -= static_cast<FLOAT>(static_cast<short>(newAngle / MAX_DEGREESS)) * MAX_DEGREESS;
			if (newAngle < 0.0F) [[unlikely]] {
				newAngle += MAX_DEGREESS;
				}
			this->angle = newAngle;
		}

		constexpr void addAngle(const FLOAT addingAngle) noexcept {
			this->angle += addingAngle;
			this->angle -= static_cast<FLOAT>(static_cast<short>(this->angle / MAX_DEGREESS)) * MAX_DEGREESS;
			if (this->angle < 0.0F) [[unlikely]] {
				this->angle += MAX_DEGREESS;
				}
		}

		/// \brief Get rotation angle of the object.
		///
		/// The rotation angle is always in the range [0, 360).
		constexpr const FLOAT& getAngle() const noexcept { return this->angle; }
	private:
		/// The rotation angle of a transformable object in degreess.
		FLOAT angle = 0.0F;
	};
}
