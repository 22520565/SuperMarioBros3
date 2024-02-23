#pragma once
#include "Texture.hpp"
#include <d3dx10.h>
#include <unordered_map>

namespace game {
    /*
        Manage texture database
    */
    class Textures {
        static Textures *__instance;

        std::unordered_map<int, LPTEXTURE> textures;

      public:
        Textures();
        void add(int id, LPCWSTR filePath);
        LPTEXTURE Get(unsigned int i);
        void Clear();

        static Textures *GetInstance();
    };
}
