#pragma once
#include <string>
#include <winnt.h>
#include "tchar.hpp"

namespace game {
	using tstring = std::basic_string<tchar, std::char_traits<tchar>, std::allocator<tchar>>;;
}
