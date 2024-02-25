#pragma once

#include "GameObject.hpp"

namespace game {
    /*
        Object that triggers scene switching
    */
    class Portal : public GameObject {
        int scene_id; // target scene to switch to

        float width;
        float height;

      public:
        Portal(const Vector2<std::float32_t>& position, float r, float b, int scene_id);
        virtual void render();
        virtual void getBoundingBox(float &l, float &t, float &r, float &b);

        void RenderBoundingBox(void);

        int GetSceneId() { return scene_id; }
        int IsBlocking() { return 0; }
    };
}
