#pragma once
#include "D3DX10core.h"
#include "D3DX10math.h"
#include "DxResource.hpp"
#include "NonCopyable.hpp"
#include "Vector2.hpp"
#include <atlcomcli.h>
#include <d3d10.h>
#include "Drawable.hpp"
#include "View.hpp"

namespace game {
    class RenderTarget : public NonCopyable {
    public:
       constexpr const CComPtr<ID3D10Device> & getDevice() const noexcept { return this->pD3DDevice; }
      constexpr const CComPtr <ID3DX10Sprite>& getSpriteObject() const noexcept { return this->spriteObject; }

      protected:
          CComPtr<ID3D10Device> pD3DDevice = nullptr;
          CComPtr<IDXGISwapChain> pSwapChain = CComPtr<IDXGISwapChain>();

          ID3D10RenderTargetView* pRenderTargetView = nullptr;
         CComPtr <ID3DX10Sprite> spriteObject = CComPtr <ID3DX10Sprite>();

         // create and set the viewport
         D3D10_VIEWPORT viewPort = D3D10_VIEWPORT();

        // To store alpha blending state
        CComPtr <ID3D10BlendState>pBlendStateAlpha = CComPtr <ID3D10BlendState>();
        CComPtr <ID3D10SamplerState>pPointSamplerState = CComPtr < ID3D10SamplerState>();

        RenderTarget() = default;

      public:
       virtual ~RenderTarget() = default;
        void clear() { this->clear(D3DXCOLOR(0.0F, 0.0F, 0.0F, 0.0F)); }
        void clear(D3DXCOLOR color) { pD3DDevice->ClearRenderTargetView(pRenderTargetView, color); }
        const D3D10_VIEWPORT& getViewPort() { return this->viewPort; }
   /*     void setView(const View& view) {
            auto transform = view.getTransform();
            this->spriteObject->SetProjectionTransform(&transform);
        }*/
        void draw(const Drawable& drawable) { drawable.draw(*this); }

        /// \brief Return the size of the rendering region of the target
        ///
        /// \return Size in pixels
        virtual Vector2<int> getSize() const = 0;
        
        void setView();
        
    };
}