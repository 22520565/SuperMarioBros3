#pragma once
#include "tchar.hpp"
#include <string>
#include <memory>

namespace game {
	using tstring = std::basic_string<tchar, std::char_traits<tchar>, std::allocator<tchar>>;;
}
