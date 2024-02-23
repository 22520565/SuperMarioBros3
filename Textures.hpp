#pragma once
#include <d3dx10.h>
#include <unordered_map>

#include "Texture.hpp"

namespace game {
    /*
        Manage texture database
    */
    class Textures {
        static Textures *__instance;

        std::unordered_map<int, LPTEXTURE> textures;

    public:
        Textures();
        void Add(int id, LPCWSTR filePath);
        LPTEXTURE Get(unsigned int i);
        void Clear();

        static Textures *GetInstance();
    };
}
