#include "Keyboard.hpp"
#include <array>
#include <cstdint>
#include <limits>
#include <winerror.h>

namespace game {
    inline bool Keyboard::isKeyDown(const uint8_t keycode) noexcept {
        bool result = false;

        if (pDirectInputDevice != nullptr) [[unlikely]] {
            if (std::array<uint8_t, static_cast<size_t>((std::numeric_limits<uint8_t>::max)()) + 1UL> keyboardState =
                    std::array<uint8_t, static_cast<size_t>((std::numeric_limits<uint8_t>::max)()) + 1UL>();
                SUCCEEDED(pDirectInputDevice->GetDeviceState(
                    sizeof(keyboardState), reinterpret_cast<void **>(keyboardState.data()))) ||
                (SUCCEEDED(pDirectInputDevice->Acquire()) &&
                 SUCCEEDED(pDirectInputDevice->GetDeviceState(
                     sizeof(keyboardState), reinterpret_cast<void **>(keyboardState.data()))))) [[likely]] {
                result = ((keyboardState[keycode] & 0x80) != 0);
            }
        }

        return result;
    }
}
