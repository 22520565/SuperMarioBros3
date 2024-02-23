#pragma once

#include "Sprite.hpp"

namespace game {
    /*
        Sprite animation
    */
    class CAnimationFrame {
        LPSPRITE sprite;
        DWORD time;

    public:
        CAnimationFrame(LPSPRITE sprite, int time) {
            this->sprite = sprite;
            this->time = time;
        }
        DWORD GetTime() { return time; }
        LPSPRITE GetSprite() { return sprite; }
    };

    typedef CAnimationFrame *LPANIMATION_FRAME;
}
