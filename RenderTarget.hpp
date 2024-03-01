#pragma once
#include "NonCopyable.hpp"
#include "Vector2.hpp"
#include <cstdint>

namespace game {
    class RenderTarget : public NonCopyable {
    public:
        ID3D10Device*const getD3Device() const { return this->pD3DDevice; }
      protected:
        ID3D10RenderTargetView *pRenderTargetView = nullptr;
        static inline ID3D10Device *pD3DDevice = nullptr;
        static inline IDXGISwapChain *pSwapChain = nullptr;
        // Backbuffer width & height, will be set during Direct3D initialization
        Vector2<uint_fast32_t> backBufferSize = Vector2<uint_fast32_t>();

        // To store alpha blending state
        ID3D10BlendState *pBlendStateAlpha = nullptr;
        // Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????
        LPD3DX10SPRITE spriteObject = nullptr;

        ID3D10SamplerState *pPointSamplerState = nullptr;

        RenderTarget(HWND hWnd) {
            RECT rect = RECT();
            GetClientRect(hWnd, &rect);

            backBufferSize = Vector2<uint_fast32_t>(rect.right + 1, rect.bottom + 1);

            DebugOut(L"[INFO] Window's client area: width= %d, height= %d\n", rect.right - 1, rect.bottom - 1);

            // Create & clear the DXGI_SWAP_CHAIN_DESC structure
            // Fill in the needed values
            DXGI_SWAP_CHAIN_DESC swapChainDesc = DXGI_SWAP_CHAIN_DESC{
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
                .OutputWindow = hWnd,
                .Windowed = true,
                .SwapEffect = DXGI_SWAP_EFFECT(),
                .Flags = UINT(),
            };

            // Create the D3D device and the swap chain
            HRESULT hr = D3D10CreateDeviceAndSwapChain(
                nullptr, D3D10_DRIVER_TYPE_HARDWARE, nullptr,
                0, D3D10_SDK_VERSION, &swapChainDesc,
                &pSwapChain, &pD3DDevice);

            if (hr != S_OK) {
                DebugOut((wchar_t *)L"[ERROR] D3D10CreateDeviceAndSwapChain has failed %s %d", _W(__FILE__), __LINE__);
                return;
            }
            // Get the back buffer from the swapchain
            ID3D10Texture2D *pBackBuffer = nullptr;
            hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID *)&pBackBuffer);
            if (hr != S_OK) {
                DebugOut((wchar_t *)L"[ERROR] pSwapChain->GetBuffer has failed %s %d", _W(__FILE__), __LINE__);
                return;
            }

            // create the render target view
            hr = pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

            pBackBuffer->Release();
            if (hr != S_OK) {
                DebugOut((wchar_t *)L"[ERROR] CreateRenderTargetView has failed %s %d", _W(__FILE__), __LINE__);
                return;
            }

            // set the render target
            pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

            // create and set the viewport
            D3D10_VIEWPORT viewPort = D3D10_VIEWPORT{
                .TopLeftX = 0,
                .TopLeftY = 0,
                .Width = backBufferSize.x,
                .Height = backBufferSize.y,
                .MinDepth = 0.0F,
                .MaxDepth = 1.0F,
            };
            pD3DDevice->RSSetViewports(1, &viewPort);

            //
            //
            //

            D3D10_SAMPLER_DESC desc = D3D10_SAMPLER_DESC{
                .Filter = D3D10_FILTER_MIN_MAG_POINT_MIP_LINEAR,
                .AddressU = D3D10_TEXTURE_ADDRESS_CLAMP,
                .AddressV = D3D10_TEXTURE_ADDRESS_CLAMP,
                .MipLODBias = 0,
                .MaxAnisotropy = 1,
                .ComparisonFunc = D3D10_COMPARISON_NEVER,
                .BorderColor = {1.0F, 1.0F, 1.0F, 1.0F},
                .MinLOD = std::numeric_limits<FLOAT>::lowest(),
                .MaxLOD = (std::numeric_limits<FLOAT>::max)(),
            };

            pD3DDevice->CreateSamplerState(&desc, &this->pPointSamplerState);

            // create the sprite object to handle sprite drawing
            hr = D3DX10CreateSprite(pD3DDevice, 0, &spriteObject);

            if (hr != S_OK) {
                DebugOut((wchar_t *)L"[ERROR] D3DX10CreateSprite has failed %s %d", _W(__FILE__), __LINE__);
                return;
            };

            D3DXMATRIX matProjection = D3DXMATRIX();

            // Create the projection matrix using the values in the viewport
            D3DXMatrixOrthoOffCenterLH(
                &matProjection,
                static_cast<FLOAT>(viewPort.TopLeftX),
                static_cast<FLOAT>(viewPort.Width),
                static_cast<FLOAT>(viewPort.TopLeftY),
                static_cast<FLOAT>(viewPort.Height),
                0.1F, 10.0F);
            hr = spriteObject->SetProjectionTransform(&matProjection);

            // Initialize the blend state for alpha drawing
            D3D10_BLEND_DESC stateDesc = D3D10_BLEND_DESC{
                .AlphaToCoverageEnable = false,
                .BlendEnable = {true, false, false, false, false, false, false, false},
                .SrcBlend = D3D10_BLEND_SRC_ALPHA,
                .DestBlend = D3D10_BLEND_INV_SRC_ALPHA,
                .BlendOp = D3D10_BLEND_OP_ADD,
                .SrcBlendAlpha = D3D10_BLEND_ZERO,
                .DestBlendAlpha = D3D10_BLEND_ZERO,
                .BlendOpAlpha = D3D10_BLEND_OP_ADD,
                .RenderTargetWriteMask = {
                    D3D10_COLOR_WRITE_ENABLE_ALL, UINT8(), UINT8(), UINT8(),
                    UINT8(), UINT8(), UINT8(), UINT8()},
            };
            pD3DDevice->CreateBlendState(&stateDesc, &this->pBlendStateAlpha);
            DebugOut((wchar_t *)L"[INFO] InitDirectX has been successful\n");
        }

      public:
        void clear() { this->clear(D3DXCOLOR(0.0F, 0.0F, 0.0F, 0.0F)); }
        void clear(D3DXCOLOR color) { pD3DDevice->ClearRenderTargetView(pRenderTargetView, color); }

        // Drawable
        void draw();

        /// \brief Return the size of the rendering region of the target
        ///
        /// \return Size in pixels
        virtual Vector2<int> getSize() const = 0;
    };
}