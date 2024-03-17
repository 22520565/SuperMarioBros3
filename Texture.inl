#include "RenderTarget.hpp"
#include "Texture.hpp"
#include <tuple>

namespace game {
    ////////////////////////////////////////////////////////////
    inline Texture::Texture(const RenderTarget &renderTarget) noexcept 
        :DxResource(&renderTarget.getDevice()) {}

    ////////////////////////////////////////////////////////////
    inline Texture::Texture(const RenderTarget &renderTarget, const TCHAR *const &fileName) noexcept(
        noexcept(Texture(renderTarget).loadFromFile(fileName)))
        : Texture(renderTarget) {
        std::ignore = this->loadFromFile(fileName);
    }

    ////////////////////////////////////////////////////////////
    constexpr const Vector2uf32 &Texture::getSize() const noexcept { return this->size; }

    ////////////////////////////////////////////////////////////
    constexpr const CComPtr<ID3D10ShaderResourceView> &Texture::getShaderResourceView() const noexcept {
        return this->shaderResourceView;
    }
}
