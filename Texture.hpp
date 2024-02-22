#pragma once

#include <cstdint>
#include <d3d10.h>
#include <d3dx10.h>

//
// Warpper class to simplify texture manipulation. See also CGame::LoadTexture
//
class Texture final {
private:
    ID3D10Texture2D *texture = nullptr;
    ID3D10ShaderResourceView *shaderResourceView = nullptr;
    uint_fast32_t width = 0U;
    uint_fast32_t height = 0U;

public:
    constexpr Texture() noexcept = default;

    Texture(ID3D10Texture2D *const texture, ID3D10ShaderResourceView *const shaderResourceView)
        : texture(texture), shaderResourceView(shaderResourceView) {
        D3D10_TEXTURE2D_DESC desc = D3D10_TEXTURE2D_DESC();
        this->texture->GetDesc(&desc);
        this->width = desc.Width;
        this->height = desc.Height;
    }

    [[nodiscard]] ID3D10ShaderResourceView *getShaderResourceView() const noexcept { return this->shaderResourceView; }

    constexpr uint_fast32_t getWidth() const noexcept { return this->width; }
    constexpr uint_fast32_t getHeight() const noexcept { return this->height; }

    ~Texture() {
        if (shaderResourceView != nullptr) {
            this->shaderResourceView->Release();
        }
        if (texture != nullptr) {
            this->texture->Release();
        }
    }
};

// TODO: remove unneccessary aliasing
typedef Texture *LPTEXTURE;
