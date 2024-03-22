#pragma once
#include "Sprite.hpp"

namespace game {
	class Object {
	public:
		bool enabled = true;
		bool collidable = true;
		Sprite sprite = Sprite();

		void loadFromFile(const TCHAR* const fileName);

		void update();
};
}
