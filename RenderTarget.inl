#include "RenderTarget.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    constexpr const CComPtr<ID3D10Device> &RenderTarget::getDevice() const noexcept { return this->pD3DDevice; }

    ////////////////////////////////////////////////////////////
    constexpr const CComPtr<ID3DX10Sprite> &RenderTarget::getSpriteObject() const noexcept {
        return this->spriteObject;
    }

    ////////////////////////////////////////////////////////////
    inline void RenderTarget::clear() { this->clear(D3DXCOLOR(0.0F, 0.0F, 0.0F, 0.0F)); }

    ////////////////////////////////////////////////////////////
    inline void RenderTarget::clear(D3DXCOLOR color) { pD3DDevice->ClearRenderTargetView(pRenderTargetView, color); }

    ////////////////////////////////////////////////////////////
    inline void RenderTarget::setView(const View<float>& view) {
        D3DXMATRIX d3dxMatrix = static_cast<D3DXMATRIX>(view.getTransform());
        this->spriteObject->SetProjectionTransform(&d3dxMatrix);
    }

    ////////////////////////////////////////////////////////////
    inline void RenderTarget::draw(const Drawable& drawable) { drawable.draw(*this); }
}
