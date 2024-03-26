#pragma once
#include "debug.hpp"
#include "DxResource.hpp"
#include "tchar.hpp"
#include "Vector2.hpp"
#include <cstdint>
#include <D3DX10.h>

namespace game {
    class RenderTarget;

    //
    // Warpper class to simplify texture manipulation. See also Game::LoadTexture
    //
    class Texture final : public DxResource {
      public:
        explicit Texture(const RenderTarget &renderTarget) noexcept;

        explicit Texture(const RenderTarget& renderTarget, const tchar* const& fileName)noexcept(
            noexcept(Texture(renderTarget).loadFromFile(fileName)));

        bool loadFromFile(const tchar *const &fileName) noexcept;

        [[nodiscard]]
        constexpr const Vector2uf32 &getSize() const noexcept;

        [[nodiscard]]
        constexpr const CComPtr<ID3D10ShaderResourceView> &getShaderResourceView() const noexcept;

      private:
        CComPtr<ID3D10Texture2D> texture = CComPtr<ID3D10Texture2D>();
        CComPtr<ID3D10ShaderResourceView> shaderResourceView = CComPtr<ID3D10ShaderResourceView>();
        Vector2uf32 size = Vector2uf32();
    };

    // TODO: remove unneccessary aliasing
    typedef Texture *LPTEXTURE;
}

#include "Texture.inl"
