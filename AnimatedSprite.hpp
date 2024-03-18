#pragma once
#include "Sprite.hpp"
#include "AnimationFrame.hpp"
#include <vector>

namespace game {
	class AnimatedSprite :private Sprite {
	public:
		std::vector<AnimationFrame> animationFrames= std::vector<AnimationFrame>();
		AnimatedSprite(const Texture& texture, const std::vector<AnimationFrame>& animationFrames)
		: Sprite(texture), animationFrames(animationFrames) {

		}
};
}
