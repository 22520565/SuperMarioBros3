#pragma once
#include <atlcomcli.h>
#include <dinput.h>
#include <minwindef.h>

namespace game {
    class InputBase {
      public:
          CComPtr<IDirectInput8W> pDirectInput = nullptr;

        explicit InputBase(const HINSTANCE hInstance) noexcept;

    };
}

#include "InputBase.inl"
