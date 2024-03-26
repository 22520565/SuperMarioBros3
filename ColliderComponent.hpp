#pragma once
#include "Component.hpp"

namespace game {
	class ColliderComponent :public Component {
	public:
		constexpr void start(GameObjectSharer* pGameObjectSharer, GameObject* self) noexcept override;
	protected:
		explicit ColliderComponent(const tstring_view specificTypeName) noexcept;
	};
}

#include "ColliderComponent.inl"
