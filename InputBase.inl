#include "InputBase.hpp"
#include "debug.hpp"

namespace game {
   inline InputBase::InputBase(const HINSTANCE hInstance) noexcept {
        if (const HRESULT hresult =
                ::DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
                                     reinterpret_cast<void **>(&this->pDirectInput), nullptr);
            FAILED(hresult) || (pDirectInput == nullptr)) [[unlikely]] {
            DebugOut(L"[ERROR] DirectInput8Create failed!\n");
        }
    }
}
