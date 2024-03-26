#pragma once
#include "ColliderComponent.hpp"
#include "Component.hpp"
#include "tstring.hpp"

namespace game {
	////////////////////////////////////////////////////////////
	constexpr ColliderComponent::ColliderComponent(const tstring_view specificTypeName) noexcept
		: Component(L"collider", specificTypeName){}

	////////////////////////////////////////////////////////////
	constexpr void start(GameObjectSharer* pGameObjectSharer, GameObject* self) noexcept {}
}
