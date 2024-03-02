#pragma once
#include "Vector2.hpp"

namespace game {
	class Transformable {
	private:
		Vector2<float> origin = Vector2<float>();
		Vector2<float> position = Vector2<float>();
		float rotation = 0.0F;
		Vector2<float> scale = Vector2<float>();
	};
}