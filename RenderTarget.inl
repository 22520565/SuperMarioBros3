#include "RenderTarget.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    constexpr const CComPtr<ID3D10Device> &RenderTarget::getDevice() const noexcept { return this->pD3DDevice; }

    ////////////////////////////////////////////////////////////
    constexpr const CComPtr<ID3DX10Sprite> &RenderTarget::getSpriteObject() const noexcept {
        return this->spriteObject;
    }

    constexpr const CComPtr<IDXGISwapChain> &RenderTarget::getSwapChain() const noexcept {
        return this->pSwapChain;
    }

    ////////////////////////////////////////////////////////////
    inline void RenderTarget::clear() { this->clear(D3DXCOLOR(0.0F, 0.0F, 0.0F, 0.0F)); }

    ////////////////////////////////////////////////////////////
    inline void RenderTarget::clear(const D3DXCOLOR color) { pD3DDevice->ClearRenderTargetView(pRenderTargetView, color); }

    ////////////////////////////////////////////////////////////
    inline bool RenderTarget::setView(const View<float> &view) noexcept {
        D3DXMATRIX d3dxMatrix = static_cast<D3DXMATRIX>(view.getTransform());
        return SUCCEEDED(this->spriteObject->SetProjectionTransform(&d3dxMatrix));
    }

    ////////////////////////////////////////////////////////////
    inline bool RenderTarget::draw(const Drawable &drawable) const noexcept { return drawable.draw(*this); }

    ////////////////////////////////////////////////////////////
    constexpr bool RenderTarget::display() const noexcept {
        return SUCCEEDED(this->pSwapChain->Present(1, 0));
    }
}
