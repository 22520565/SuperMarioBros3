#include "AssetIDs.hpp"
#include <fstream>
#include <iostream>

#include "Coin.hpp"
#include "Platform.hpp"
#include "PlayScene.hpp"
#include "Portal.hpp"
#include "Sprites.hpp"
#include "Textures.hpp"
#include "Utils.hpp"

#include "SampleKeyEventHandler.hpp"

namespace game {
    PlayScene::PlayScene(int id, LPCWSTR filePath) : Scene(id, filePath) {
        player = NULL;
        key_handler = new SampleKeyHandler(this);
    }

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS 1
#define SCENE_SECTION_OBJECTS 2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

    void PlayScene::_ParseSection_SPRITES(std::string line) {
        std::vector<std::string> tokens = split(line);

        if (tokens.size() < 6)
            return; // skip invalid lines

        int ID = atoi(tokens[0].c_str());
        int l = atoi(tokens[1].c_str());
        int t = atoi(tokens[2].c_str());
        int r = atoi(tokens[3].c_str());
        int b = atoi(tokens[4].c_str());
        int texID = atoi(tokens[5].c_str());

        LPTEXTURE tex = Textures::GetInstance()->Get(texID);
        if (tex == NULL) {
            DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
            return;
        }

        Sprites::GetInstance()->add(ID, l, t, r, b, tex);
    }

    void PlayScene::_ParseSection_ASSETS(std::string line) {
        std::vector<std::string> tokens = split(line);

        if (tokens.size() < 1)
            return;

        std::wstring path = ToWSTR(tokens[0]);

        LoadAssets(path.c_str());
    }

    void PlayScene::_ParseSection_ANIMATIONS(std::string line) {
        std::vector<std::string> tokens = split(line);

        if (tokens.size() < 3)
            return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

        // DebugOut(L"--> %s\n",ToWSTR(line).c_str());

        LPANIMATION ani = new Animation();

        int ani_id = atoi(tokens[0].c_str());
        for (int i = 1; i < tokens.size(); i += 2) // why i+=2 ?  sprite_id | frame_time
        {
            int sprite_id = atoi(tokens[i].c_str());
            int frame_time = atoi(tokens[i + 1].c_str());
            ani->add(sprite_id, frame_time);
        }

        Animations::GetInstance()->add(ani_id, ani);
    }

    /*
        Parse a line in section [OBJECTS]
    */
    void PlayScene::_ParseSection_OBJECTS(std::string line) {
        std::vector<std::string> tokens = split(line);

        // skip invalid lines - an object set must have at least id, x, y
        if (tokens.size() < 2)
            return;

        int object_type = atoi(tokens[0].c_str());
        float x = (float)atof(tokens[1].c_str());
        float y = (float)atof(tokens[2].c_str());

        GameObject *obj = NULL;

        switch (object_type) {
        case OBJECT_TYPE_MARIO:
            if (player != NULL) {
                DebugOut(L"[ERROR] MARIO object was created before!\n");
                return;
            }
            obj = new Mario(x, y);
            player = (Mario *)obj;

            DebugOut(L"[INFO] Player object has been created!\n");
            break;
        case OBJECT_TYPE_GOOMBA:
            obj = new Goomba(x, y);
            break;
        case OBJECT_TYPE_BRICK:
            obj = new Brick(x, y);
            break;
        case OBJECT_TYPE_COIN:
            obj = new Coin(x, y);
            break;

        case OBJECT_TYPE_PLATFORM: {

            float cell_width = (float)atof(tokens[3].c_str());
            float cell_height = (float)atof(tokens[4].c_str());
            int length = atoi(tokens[5].c_str());
            int sprite_begin = atoi(tokens[6].c_str());
            int sprite_middle = atoi(tokens[7].c_str());
            int sprite_end = atoi(tokens[8].c_str());

            obj = new Platform(
                x, y,
                cell_width, cell_height, length,
                sprite_begin, sprite_middle, sprite_end);

            break;
        }

        case OBJECT_TYPE_PORTAL: {
            float r = (float)atof(tokens[3].c_str());
            float b = (float)atof(tokens[4].c_str());
            int scene_id = atoi(tokens[5].c_str());
            obj = new Portal(x, y, r, b, scene_id);
        } break;

        default:
            DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
            return;
        }

        // General object setup
        obj->SetPosition(x, y);

        objects.push_back(obj);
    }

    void PlayScene::LoadAssets(LPCWSTR assetFile) {
        DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

        std::ifstream f = std::ifstream(assetFile);

        int section = ASSETS_SECTION_UNKNOWN;

        char str[MAX_SCENE_LINE];
        while (f.getline(str, MAX_SCENE_LINE)) {
            std::string line(str);

            if (line[0] == '#')
                continue; // skip comment lines

            if (line == "[SPRITES]") {
                section = ASSETS_SECTION_SPRITES;
                continue;
            };
            if (line == "[ANIMATIONS]") {
                section = ASSETS_SECTION_ANIMATIONS;
                continue;
            };
            if (line[0] == '[') {
                section = SCENE_SECTION_UNKNOWN;
                continue;
            }

            //
            // data section
            //
            switch (section) {
            case ASSETS_SECTION_SPRITES:
                _ParseSection_SPRITES(line);
                break;
            case ASSETS_SECTION_ANIMATIONS:
                _ParseSection_ANIMATIONS(line);
                break;
            }
        }

        DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
    }

    void PlayScene::Load() {
        DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

        std::ifstream f = std::ifstream(sceneFilePath);

        // current resource section flag
        int section = SCENE_SECTION_UNKNOWN;

        char str[MAX_SCENE_LINE];
        while (f.getline(str, MAX_SCENE_LINE)) {
            std::string line(str);

            if (line[0] == '#')
                continue; // skip comment lines
            if (line == "[ASSETS]") {
                section = SCENE_SECTION_ASSETS;
                continue;
            };
            if (line == "[OBJECTS]") {
                section = SCENE_SECTION_OBJECTS;
                continue;
            };
            if (line[0] == '[') {
                section = SCENE_SECTION_UNKNOWN;
                continue;
            }

            //
            // data section
            //
            switch (section) {
            case SCENE_SECTION_ASSETS:
                _ParseSection_ASSETS(line);
                break;
            case SCENE_SECTION_OBJECTS:
                _ParseSection_OBJECTS(line);
                break;
            }
        }

        DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
    }

    void PlayScene::update(DWORD dt) {
        // We know that Mario is the first object in the list hence we won't add him into the colliable object list
        // TO-DO: This is a "dirty" way, need a more organized way

        std::vector<LPGAMEOBJECT> coObjects;
        for (size_t i = 1; i < objects.size(); i++) {
            coObjects.push_back(objects[i]);
        }

        for (size_t i = 0; i < objects.size(); i++) {
            objects[i]->update(dt, &coObjects);
        }

        // skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
        if (player == NULL)
            return;

        // Update camera to follow mario
        float cx, cy;
        player->GetPosition(cx, cy);

        Game *game = Game::GetInstance();
        cx -= game->GetBackBufferWidth() / 2;
        cy -= game->GetBackBufferHeight() / 2;

        if (cx < 0)
            cx = 0;

        Game::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);

        PurgeDeletedObjects();
    }

    void PlayScene::render() {
        for (int i = 0; i < objects.size(); i++)
            objects[i]->render();
    }

    /*
     *	Clear all objects from this scene
     */
    void PlayScene::clear() {
        for (auto it = objects.begin(); it != objects.end(); it++) {
            delete (*it);
        }
        objects.clear();
    }

    /*
        Unload scene

        TODO: Beside objects, we need to clean up sprites, animations and textures as well

    */
    void PlayScene::Unload() {
        for (int i = 0; i < objects.size(); i++)
            delete objects[i];

        objects.clear();
        player = NULL;

        DebugOut(L"[INFO] Scene %d unloaded! \n", id);
    }

    bool PlayScene::IsGameObjectDeleted(const LPGAMEOBJECT &o) { return o == NULL; }

    void PlayScene::PurgeDeletedObjects() {
        for (auto it = objects.begin(); it != objects.end(); it++) {
            LPGAMEOBJECT o = *it;
            if (o->IsDeleted()) {
                delete o;
                *it = NULL;
            }
        }

        // NOTE: remove_if will swap all deleted items to the end of the vector
        // then simply trim the vector, this is much more efficient than deleting individual items
        objects.erase(
            std::remove_if(objects.begin(), objects.end(), PlayScene::IsGameObjectDeleted),
            objects.end());
    }
}
