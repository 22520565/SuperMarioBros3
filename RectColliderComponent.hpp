#pragma once
#include "ColliderComponent.hpp"
#include "Rect3.hpp"
#include "tstring.hpp"

namespace game {
	class RectColliderComponent : public ColliderComponent {
	public:
		Rect3f collider = Rect3f();
		const tstring tag = tstring();

		constexpr explicit RectColliderComponent(const tstring_view name) noexcept;
		
		constexpr void start(GameObjectSharer* pGameObjectSharer, GameObject* self) noexcept;
};
}

#include "RectColliderComponent.inl"
