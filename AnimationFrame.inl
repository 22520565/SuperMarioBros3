#include "AnimationFrame.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    constexpr AnimationFrame::AnimationFrame(const Rect2uf32& textureRect, const Time frameTime) noexcept
        : textureRect(textureRect), frameTime(frameTime) {}
}