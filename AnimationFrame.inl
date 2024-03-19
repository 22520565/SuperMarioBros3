#include "AnimationFrame.hpp"

namespace game {
    constexpr AnimationFrame::AnimationFrame(const Rect2f &textureRect, const Time frameTime)
        : textureRect(textureRect), frameTime(frameTime) {}
}
