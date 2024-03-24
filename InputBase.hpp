#pragma once
#include <dinput.h>
#include <atlcomcli.h>

namespace game {
    class InputBase {
      public:
          CComPtr<IDirectInput8W> pDirectInput = nullptr;

        explicit InputBase(const HINSTANCE hInstance) noexcept;

    };
}

#include "InputBase.inl"
