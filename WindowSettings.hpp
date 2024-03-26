#pragma once
#include "tstring.hpp"
#include "Vector2.hpp"
#include <libloaderapi.h>
#include <minwindef.h>
#include <WinUser.h>

namespace game {
	struct WindowSettings {
	public:
		Vector2i size = Vector2i::zero();
		tstring title = tstring();
		tstring iconPath = tstring();
		tstring className = tstring();
		HINSTANCE hInstance = GetModuleHandle(nullptr);
		int nCmdShow = SW_SHOWNORMAL;
	};
}
