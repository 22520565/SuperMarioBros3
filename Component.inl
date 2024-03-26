#include "Component.hpp"

namespace game {
	////////////////////////////////////////////////////////////
	constexpr Component::Component(const tstring_view typeName, const tstring_view specificTypeName) noexcept
		:typeName(typeName), specificTypeName(specificTypeName){}
}
