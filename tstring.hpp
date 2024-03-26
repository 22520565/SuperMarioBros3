#pragma once
#include "tchar.hpp"
#include <string>
#include <memory>

namespace game {
	using tstring = std::basic_string<tchar, std::char_traits<tchar>, std::allocator<tchar>>;
	using tstring_view = std::basic_string_view<tchar>;
}
