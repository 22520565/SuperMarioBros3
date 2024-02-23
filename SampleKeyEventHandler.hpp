#pragma once

#include "Scene.hpp"

namespace game {
    class CSampleKeyHandler : public CSceneKeyHandler {
    public:
        virtual void KeyState(BYTE *states);
        virtual void OnKeyDown(int KeyCode);
        virtual void OnKeyUp(int KeyCode);
        CSampleKeyHandler(LPSCENE s) : CSceneKeyHandler(s){};
    };
}
