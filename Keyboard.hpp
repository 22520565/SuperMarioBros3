#pragma once
#include "InputBase.hpp"

namespace game {
    class Keyboard final {
      public:
        static constexpr DWORD bufferSize = 1024UL;

        explicit Keyboard(InputBase &inputBase);

        [[nodiscard]]
        bool isKeyDown(const uint8_t keycode) noexcept;

      private:
        CComPtr<IDirectInputDevice8W> pDirectInputDevice = nullptr;
    };
}

#include "Keyboard.inl"
