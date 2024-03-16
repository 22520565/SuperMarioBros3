#pragma once
#include "D3DX10core.h"
#include "D3DX10math.h"
#include "Drawable.hpp"
#include "DxResource.hpp"
#include "NonCopyable.hpp"
#include "Vector2.hpp"
#include "View.hpp"
#include <atlcomcli.h>
#include <d3d10.h>

namespace game {
    class RenderTarget {
      public:
        virtual ~RenderTarget() = default;

        [[nodiscard]]
        constexpr const CComPtr<ID3D10Device> &getDevice() const noexcept;

        [[nodiscard]]
        constexpr const CComPtr<ID3DX10Sprite> &getSpriteObject() const noexcept;

        void clear();

        void clear(D3DXCOLOR color);

        //   const D3D10_VIEWPORT& getViewPort() { return this->viewPort; }

        void setView(const View<float> &view);

        inline void draw(const Drawable &drawable);

        /// \brief Return the size of the rendering region of the target.
        ///
        /// \return Size in pixels
        virtual Vector2<int> getSize() const = 0;

      protected:
        CComPtr<ID3D10Device> pD3DDevice = CComPtr<ID3D10Device>();
        CComPtr<IDXGISwapChain> pSwapChain = CComPtr<IDXGISwapChain>();

        ID3D10RenderTargetView *pRenderTargetView = nullptr;
        CComPtr<ID3DX10Sprite> spriteObject = CComPtr<ID3DX10Sprite>();

        // create and set the viewport
        D3D10_VIEWPORT viewPort = D3D10_VIEWPORT();

        // To store alpha blending state
        CComPtr<ID3D10BlendState> pBlendStateAlpha = CComPtr<ID3D10BlendState>();
        CComPtr<ID3D10SamplerState> pPointSamplerState = CComPtr<ID3D10SamplerState>();

        explicit RenderTarget(const DXGI_SWAP_CHAIN_DESC &swapChainDesc);

      private:
        constexpr RenderTarget(const RenderTarget &) noexcept = delete;
        constexpr RenderTarget(RenderTarget &&) noexcept = delete;
        constexpr RenderTarget &operator=(const RenderTarget &) noexcept = delete;
        constexpr RenderTarget &operator=(RenderTarget &&) noexcept = delete;
    };
}

#include "RenderTarget.inl"
