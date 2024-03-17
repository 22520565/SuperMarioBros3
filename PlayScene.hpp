#pragma once
#include "Brick.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Goomba.hpp"
#include "Mario.hpp"
#include "Scene.hpp"
#include "TextureHolder.hpp"

namespace game {
    class PlayScene : public Scene {
      protected:
        // A play scene has to have player, right?
         GameObject * player;

        std::vector< GameObject *> objects;

        void _ParseSection_SPRITES(std::string line);
        void _ParseSection_ANIMATIONS(std::string line);

        void _ParseSection_ASSETS(std::string line);
        void _ParseSection_OBJECTS(std::string line);

        void LoadAssets(LPCWSTR assetFile);

      public:
        PlayScene(int id, LPCWSTR filePath);

        virtual void Load();
        virtual void update(DWORD dt);
        virtual void render();
        virtual void Unload();

         GameObject * GetPlayer() { return player; }

        void clear();
        void PurgeDeletedObjects();

        static bool IsGameObjectDeleted(const GameObject *const &o);
    };

    typedef PlayScene *LPPLAYSCENE;
}
