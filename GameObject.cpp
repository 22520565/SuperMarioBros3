#include <algorithm>
#include <d3dx9.h>

#include "debug.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Sprites.hpp"
#include "Textures.hpp"

namespace game {
	void GameObject::RenderBoundingBox() {
		D3DXVECTOR3 p(this->position.x, this->position.y, 0);
		RECT rect;

		LPTEXTURE bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);

		float l, t, r, b;

		getBoundingBox(l, t, r, b);
		rect.left = 0;
		rect.top = 0;
		rect.right = (int)r - (int)l;
		rect.bottom = (int)b - (int)t;

		float cx, cy;
		Game::GetInstance()->GetCamPos(cx, cy);

		Game::GetInstance()->Draw(this->position.x - cx, this->position.y - cy, bbox, &rect, BBOX_ALPHA);
	}
}
