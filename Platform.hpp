#pragma once

#include "GameObject.hpp"

namespace game {
    //
    // The most popular type of object in Mario!
    //
    class Platform : public GameObject {
      protected:
        int length; // Unit: cell
        float cellWidth;
        float cellHeight;
        int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

      public:
        Platform(const Vector2<std::float32_t>& position,
                 float cell_width, float cell_height, int length,
                 int sprite_id_begin, int sprite_id_middle, int sprite_id_end) : GameObject(position) {
            this->length = length;
            this->cellWidth = cell_width;
            this->cellHeight = cell_height;
            this->spriteIdBegin = sprite_id_begin;
            this->spriteIdMiddle = sprite_id_middle;
            this->spriteIdEnd = sprite_id_end;
        }

        void render();
        void update(DWORD dt) {}
        void getBoundingBox(float &l, float &t, float &r, float &b);
        void RenderBoundingBox();
    };

    typedef Platform *LPPLATFORM;
}
