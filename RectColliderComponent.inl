#include "ColliderComponent.hpp"
#include "RectColliderComponent.hpp"
#include "tstring.hpp"

namespace game {
	////////////////////////////////////////////////////////////
	constexpr RectColliderComponent::RectColliderComponent(const tstring_view name) noexcept 
	: ColliderComponent(L"rect"), tag(name) {}
}
