#pragma once
#include <unordered_map>
#include <windows.h>

#include <d3dx10.h>

#include "Sprite.hpp"
#include "Texture.hpp"

namespace game {
    /*
        Manage sprite database
    */
    class Sprites {
        static Sprites *__instance;

        std::unordered_map<int, LPSPRITE> sprites;

    public:
        void Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex);
        LPSPRITE Get(int id);
        void Clear();

        static Sprites *GetInstance();
    };
}
