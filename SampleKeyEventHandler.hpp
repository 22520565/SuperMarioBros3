#pragma once

#include "Scene.hpp"

class CSampleKeyHandler : public CSceneKeyHandler {
public:
    virtual void KeyState(BYTE *states);
    virtual void OnKeyDown(int KeyCode);
    virtual void OnKeyUp(int KeyCode);
    CSampleKeyHandler(LPSCENE s) : CSceneKeyHandler(s){};
};
