#include "D3DX10core.h"
#include "debug.hpp"
#include "RenderTarget.hpp"
#include <atlcomcli.h>
#include <basetsd.h>
#include <d3d10.h>
#include <d3d10misc.h>
#include <dxgi.h>
#include <limits>
#include <minwindef.h>
#include <winerror.h>
#include <windows.h>

namespace game {
    ////////////////////////////////////////////////////////////
    RenderTarget::RenderTarget(DXGI_SWAP_CHAIN_DESC swapChainDesc) {
        // Create the D3D device and the swap chain
        if (HRESULT hresult = ::D3D10CreateDeviceAndSwapChain(
                nullptr, D3D10_DRIVER_TYPE_HARDWARE, nullptr,
                0, D3D10_SDK_VERSION, &swapChainDesc,
                &pSwapChain, &pD3DDevice);
            hresult != S_OK) {
            DebugOut(L"[ERROR] D3D10CreateDeviceAndSwapChain has failed %s %d", _W(__FILE__), __LINE__);
        } else {
            // Get the back buffer from the swapchain
            CComPtr<ID3D10Texture2D> pBackBuffer = CComPtr<ID3D10Texture2D>();
            if (hresult = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void **>(&pBackBuffer));
                hresult != S_OK) {
                DebugOut(L"[ERROR] pSwapChain->GetBuffer has failed %s %d", _W(__FILE__), __LINE__);
            }
            // create the render target view
            else if (hresult = pD3DDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
                     hresult != S_OK) {
                DebugOut(L"[ERROR] CreateRenderTargetView has failed %s %d", _W(__FILE__), __LINE__);
            } else {
                // set the render target
                pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, nullptr);

                // create and set the viewport
                viewPort = D3D10_VIEWPORT{
                    .TopLeftX = 0,
                    .TopLeftY = 0,
                    .Width = swapChainDesc.BufferDesc.Width,
                    .Height = swapChainDesc.BufferDesc.Height,
                    .MinDepth = 0.0F,
                    .MaxDepth = 1.0F,
                };
                pD3DDevice->RSSetViewports(1, &viewPort);

                //
                //
                //

                const D3D10_SAMPLER_DESC desc = D3D10_SAMPLER_DESC{
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
                if (hresult = D3DX10CreateSprite(pD3DDevice, 0, &this->spriteObject);
                    hresult != S_OK) {
                    DebugOut((wchar_t *)L"[ERROR] D3DX10CreateSprite has failed %s %d", _W(__FILE__), __LINE__);
                } else {
                   // D3DXMATRIX matProjection = D3DXMATRIX();

                    // Create the projection matrix using the values in the viewport
                   /* D3DXMatrixPerspectiveOffCenterLH(
                        &matProjection,
                        -750,
                        750,
                        -750,
                        750,
                        0.10F, 1000.10F);*/
                    // D3DXMatrixOrthoOffCenterLH(
                    //     &matProjection,
                    //     static_cast<FLOAT>(viewPort.TopLeftX),
                    //     static_cast<FLOAT>(viewPort.Width),
                    //     static_cast<FLOAT>(viewPort.TopLeftY),
                    //     static_cast<FLOAT>(viewPort.Height),
                    //     -1000.0F, 1000.0F);
                   // spriteObject->SetProjectionTransform(&matProjection);
                    // Initialize the blend state for alpha drawing
                  const  D3D10_BLEND_DESC stateDesc = D3D10_BLEND_DESC{
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
                    DebugOut(L"[INFO] InitDirectX has been successful\n");
                }
            }
        }
    }
}
