#pragma once
#include "Window.hpp"
#include "RenderTarget.hpp"

namespace game {
	class RenderWindow final : public Window, public RenderTarget {
	private:
	public:
        RenderWindow(const Vector2<int>& size, const TCHAR* const title, int nCmdShow,
            HINSTANCE hInstance, const TCHAR* const className)
            : Window(size, title, nCmdShow, hInstance, className),
            RenderTarget(DXGI_SWAP_CHAIN_DESC{
                   .BufferDesc = DXGI_MODE_DESC{
                       .Width = backBufferSize.x,
                       .Height = backBufferSize.y,
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

     inline Vector2<int> getSize() const override { return WindowBase::getSize(); }

	constexpr void display() const noexcept { pSwapChain->Present(1, 0); }
	};
}
