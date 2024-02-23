#pragma once
#include "Brick.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Goomba.hpp"
#include "Mario.hpp"
#include "Scene.hpp"
#include "Textures.hpp"

class CPlayScene : public CScene {
protected:
    // A play scene has to have player, right?
    LPGAMEOBJECT player;

   std::vector<LPGAMEOBJECT> objects;

    void _ParseSection_SPRITES(std::string line);
    void _ParseSection_ANIMATIONS(std::string line);

    void _ParseSection_ASSETS(std::string line);
    void _ParseSection_OBJECTS(std::string line);

    void LoadAssets(LPCWSTR assetFile);

public:
    CPlayScene(int id, LPCWSTR filePath);

    virtual void Load();
    virtual void Update(DWORD dt);
    virtual void Render();
    virtual void Unload();

    LPGAMEOBJECT GetPlayer() { return player; }

    void Clear();
    void PurgeDeletedObjects();

    static bool IsGameObjectDeleted(const LPGAMEOBJECT &o);
};

typedef CPlayScene *LPPLAYSCENE;
