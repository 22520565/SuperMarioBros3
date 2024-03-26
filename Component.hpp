#pragma once
#include "tstring.hpp"

// Forward declaration
namespace game {
	class GameObject;

	class GameObjectSharer;
}

namespace game {

	class Component {
	public:
		const tstring typeName = L"";
		const tstring specificTypeName = L"";
		bool enabled = false;

		constexpr virtual ~Component() = default;

		constexpr virtual void start(GameObjectSharer* pGameObjectSharer, GameObject* self) noexcept = 0;

	protected:
		constexpr explicit Component(const tstring_view typeName, const tstring_view specificTypeName) noexcept;
	};
}

#include "Component.inl"
