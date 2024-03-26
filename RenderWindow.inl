#include "RenderTarget.hpp"
#include "RenderWindow.hpp"
#include "Vector2.hpp"
#include "Window.hpp"
#include "WindowSettings.hpp"
#include <dxgi.h>
#include <dxgicommon.h>
#include <dxgiformat.h>
#include <dxgitype.h>
#include <minwindef.h>

namespace game {
    ////////////////////////////////////////////////////////////
   inline RenderWindow::RenderWindow(const WindowSettings& windowSettings) noexcept
    : Window(windowSettings),
        RenderTarget(DXGI_SWAP_CHAIN_DESC{
            .BufferDesc = DXGI_MODE_DESC{
                .Width = static_cast<UINT>(windowSettings.size.x),
                .Height = static_cast<UINT>(windowSettings.size.y),
                .RefreshRate = DXGI_RATIONAL{
                    .Numerator = 60,
                    .Denominator = 1,
                },
                .Format = DXGI_FORMAT_R8G8B8A8_UNORM,
                .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER(),
                .Scaling = DXGI_MODE_SCALING(),
            },
            .SampleDesc = DXGI_SAMPLE_DESC{
                .Count = 1,
                .Quality = 0,
            },
            .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
            .BufferCount = 1,
            .OutputWindow = this->getWindowHandler(),
            .Windowed = true,
            .SwapEffect = DXGI_SWAP_EFFECT(),
            .Flags = UINT(),
            }) {}

   ////////////////////////////////////////////////////////////
   inline Vector2<int> RenderWindow::getSize() const noexcept { return Window::getSize(); }
}
