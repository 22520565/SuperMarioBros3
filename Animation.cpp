#include "Animation.hpp"
#include "debug.hpp"
#include <format>

namespace game {
    void Animation::add(const int_fast32_t spriteId, const DWORD time) {
        if (const LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
            sprite == nullptr) {
            DebugOut(L"[ERROR] Sprite ID %d not found!\n", spriteId);
        } else {
            frames.push_back(new AnimationFrame(sprite, time));
        }
    }

    void Animation::render(const std::float32_t x, const std::float32_t y) {
        const auto now = ::GetTickCount64();
        if (currentFrame == -1) {
            currentFrame = 0;
            lastFrameTime = now;
        } else {
            const auto t = frames[currentFrame]->GetTime();
            if ((now - lastFrameTime) > t) {
                ++currentFrame;
                lastFrameTime = now;
                if (currentFrame == frames.size()) {
                    currentFrame = 0;
                }
            }
        }

        frames[currentFrame]->GetSprite()->Draw(x, y);
    }
}
