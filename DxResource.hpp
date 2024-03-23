#pragma once
#include "KeyEventHandler.hpp"
#include "stdfloat"
#include "Vector2.hpp"
#include <atlcomcli.h>
#include <cstdint>
#include <d3d10.h>
#include <dinput.h>
#include <dxgi.h>
#include <libloaderapi.h>
#include <minwindef.h>
#define MAX_FRAME_RATE 100
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

namespace game {
    class DxResource {
    public:
        const CComPtr<ID3D10Device>*const pD3DDevice = nullptr;

        constexpr ~DxResource() noexcept = default;

      protected:
     //   LPDIRECTINPUT8 di;         // The DirectInput object
       // LPDIRECTINPUTDEVICE8 didv; // The keyboard device

       // BYTE keyStates[KEYBOARD_STATE_SIZE];                // DirectInput keyboard state buffer
      //  DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data

  //      LPKEYEVENTHANDLER keyHandler;

//        Vector2<std::float32_t> cameraPosition = Vector2<std::float32_t>();

      //  std::unordered_map<int, LPSCENE> scenes;
        int current_scene=4;
        int next_scene = -1;


     constexpr explicit DxResource(const CComPtr<ID3D10Device>*const device) noexcept: pD3DDevice(device) {}
    private:

        constexpr DxResource(const DxResource&) noexcept = delete;
        constexpr DxResource(DxResource&&) noexcept = delete;
        constexpr DxResource& operator=(const DxResource&) noexcept = delete;
        constexpr DxResource& operator=(DxResource&&) noexcept = delete;
    };
}
