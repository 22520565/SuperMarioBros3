#include "Animation.hpp"
#include "debug.hpp"
#include <format>

namespace game {
    void Animation::add(const int_fast32_t spriteId, const DWORD time) {
        if (const LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
            sprite == nullptr) {
            DebugOut(std::format(L"[ERROR] Sprite ID {} not found!\n", spriteId).data());
        } else {
            frames.push_back(new AnimationFrame(sprite, time));
        }
    }

    void Animation::render(const std::float32_t x, const std::float32_t y) {
        const auto now = ::GetTickCount64();

        // TODO: check if currentFrame should be uint or not? If yes, refactor the following statement
        if (currentFrame == -1) {
            currentFrame = 0;
            lastFrameTime = now;
        } else {
            const auto t = frames[currentFrame]->getTime();
            if ((now - lastFrameTime) > t) {
                ++currentFrame;
                lastFrameTime = now;
                if (currentFrame == frames.size()) {
                    currentFrame = 0;
                }
            }
        }

        frames[currentFrame]->getSprite()->Draw(x, y);
    }
}
