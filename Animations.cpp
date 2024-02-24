#include "Animations.hpp"
#include "debug.hpp"

namespace game {
    Animations *Animations::__instance = NULL;

    Animations *Animations::GetInstance() {
        if (__instance == NULL)
            __instance = new Animations();
        return __instance;
    }

    void Animations::add(int id, LPANIMATION ani) {
        if (animations[id] != NULL)
            DebugOut(L"[WARNING] Animation %d already exists\n", id);

        animations[id] = ani;
    }

    LPANIMATION Animations::getAnimation(int id) {
        LPANIMATION ani = animations[id];
        if (ani == NULL)
            DebugOut(L"[ERROR] Animation ID %d not found\n", id);
        return ani;
    }

    void Animations::clear() {
        for (auto x : animations) {
            LPANIMATION ani = x.second;
            delete ani;
        }

        animations.clear();
    }
}
