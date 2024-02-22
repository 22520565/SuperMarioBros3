#pragma once
#include <d3dx10.h>
#include <unordered_map>

#include "Texture.hpp"

using namespace std;

/*
    Manage texture database
*/
class CTextures {
    static CTextures *__instance;

    unordered_map<int, LPTEXTURE> textures;

public:
    CTextures();
    void Add(int id, LPCWSTR filePath);
    LPTEXTURE Get(unsigned int i);
    void Clear();

    static CTextures *GetInstance();
};