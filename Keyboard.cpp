#include "Keyboard.hpp"
#include "debug.hpp"

namespace game {
    Keyboard::Keyboard(InputBase &inputBase) {
        if (inputBase.pDirectInput != nullptr) [[likely]] {
            if (HRESULT hresult = inputBase.pDirectInput->CreateDevice(::GUID_SysKeyboard, &pDirectInputDevice, nullptr);
                FAILED(hresult)) [[unlikely]] {
                DebugOut(L"[ERROR] CreateDevice failed!\n");
            }
            // Set the data format to "keyboard format" - a predefined data format
            //
            // A data format specifies which controls on a device we
            // are interested in, and how they should be reported.
            //
            // This tells DirectInput that we will be passing an array
            // of 256 bytes to IDirectInputDevice::GetDeviceState.
            else if (hresult = pDirectInputDevice->SetDataFormat(&::c_dfDIKeyboard);
                     FAILED(hresult)) [[unlikely]] {
                DebugOut(L"Failed to set Data Format\n");
            } else [[likely]] {
                // IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
                //
                // DirectInput uses unbuffered I/O (buffer size = 0) by default.
                // If you want to read buffered data, you need to set a nonzero
                // buffer size.
                //
                // Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
                //
                // The buffer size is a DWORD property associated with the device.
                const DIPROPDWORD dipdw = DIPROPDWORD{
                    .diph = DIPROPHEADER{
                        .dwSize = sizeof(DIPROPDWORD),
                        .dwHeaderSize = sizeof(DIPROPHEADER),
                        .dwObj = 0UL,
                        .dwHow = DIPH_DEVICE},
                    .dwData = bufferSize};
                if (hresult = pDirectInputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
                    FAILED(hresult)) [[unlikely]] {
                    DebugOut(L"Failed to set property\n");
                } else if (hresult = pDirectInputDevice->Acquire();
                           FAILED(hresult)) {
                    DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
                } else {
                    DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
                }
            }
        }
    }
}
