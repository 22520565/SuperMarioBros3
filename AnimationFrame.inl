#include "AnimationFrame.hpp"

namespace game {
	inline AnimationFrame::AnimationFrame(const Rect2f& textureRect, const Time time)
		:textureRect(textureRect), time(time){}
}
