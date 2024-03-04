#pragma once
#include "Vector3.hpp"
#include <D3DX10.h>

namespace game {
	struct Scalation final {
	public:
		/// The scale factors of a transformable object.
		Vector3<FLOAT> factor = Vector3<FLOAT>::one;

		/// The scale center of a transformable object.
		Vector3<FLOAT> center = Vector3<FLOAT>::zero;

		/// \brief Default constructor.
		/// 
		/// The default scale factors of a transformable object is (1, 1, 1).
		/// The default scale center of a transformable object is (0, 0, 0).
		constexpr Scalation() noexcept = default;

		constexpr Scalation(const Vector3<FLOAT>& factor, const Vector3<FLOAT>& center) noexcept
			: factor(factor), center(center) {}
	};
}
