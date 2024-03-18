#include "AnimationFrame.hpp"

namespace game {
	inline AnimationFrame::AnimationFrame(const Texture& texture, const Rect2f& textureRect, const Time time)
		:texture(&texture), textureRect(textureRect), time(time){}

	constexpr const Time& AnimationFrame::getTime() const noexcept { return this->time; }
}
