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

    vector<LPGAMEOBJECT> objects;

    void _ParseSection_SPRITES(string line);
    void _ParseSection_ANIMATIONS(string line);

    void _ParseSection_ASSETS(string line);
    void _ParseSection_OBJECTS(string line);

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
