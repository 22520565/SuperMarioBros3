#include "RenderWindow.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
   inline RenderWindow::RenderWindow(const Vector2<int>& size, const tchar* const title, const tchar* const className,
        const tchar* const iconPath, const HINSTANCE hInstance, const int nCmdShow) noexcept
    : Window(size, title, className, iconPath, hInstance, nCmdShow),
        RenderTarget(DXGI_SWAP_CHAIN_DESC{
            .BufferDesc = DXGI_MODE_DESC{
                .Width = static_cast<UINT>(size.x),
                .Height = static_cast<UINT>(size.y),
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
   inline Vector2<int> RenderWindow::getSize() const noexcept { return WindowBase::getSize(); }
}
