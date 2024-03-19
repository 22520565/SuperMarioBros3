#include "Sprite.hpp"

namespace game {
    inline Sprite::Sprite(const Texture &texture) noexcept(
        noexcept(Rect2f(Vector2f::zero(), Vector2f(texture.getSize()))))
        : Sprite(texture, Rect2f(Vector2f::zero(), static_cast<Vector2f>(texture.getSize()))) {}

    inline Sprite::Sprite(const Texture &texture, const Rect2f &textureRect) noexcept
        : texture(&texture),
          dxSprite(D3DX10_SPRITE{
              .matWorld = D3DXMATRIX(),
              .TexCoord = D3DXVECTOR2(textureRect.left, textureRect.top),
              .TexSize = D3DXVECTOR2(textureRect.width, textureRect.height),
              .ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
              .pTexture = texture.getShaderResourceView(),
              .TextureIndex = 0U,
          }) {}

    inline const Texture *Sprite::getTexture() const noexcept { return this->texture; }

    constexpr const Rect2f& Sprite::getTextureRect() const noexcept {
        return this->textureRect;
    }

    inline void Sprite::setTexture(const Texture &newTexture) noexcept(
        noexcept(Rect2f(Vector2f::zero(), static_cast<Vector2f>(newTexture.getSize())))) {
        this->setTexture(newTexture, Rect2f(Vector2f::zero(), static_cast<Vector2f>(newTexture.getSize())));
    }

    inline void Sprite::setTexture(const Texture &newTexture, const Rect2f &newTextureRect) noexcept {
        this->texture = &newTexture;
        this->dxSprite.pTexture = newTexture.getShaderResourceView();
        this->setTextureRect(newTextureRect);
    }

    inline void Sprite::setTextureRect(const Rect2f &newTextureRect) noexcept {
        const auto& textureSize = this->texture->getSize();
        this->textureRect = newTextureRect;
        this->dxSprite.TexCoord = D3DXVECTOR2(newTextureRect.left/textureSize.x, newTextureRect.top/ textureSize.y);
        this->dxSprite.TexSize = D3DXVECTOR2(newTextureRect.width/ textureSize.x, newTextureRect.height/ textureSize.y);
    }

    inline bool Sprite::draw(const RenderTarget &target) const {
        bool drawn = false;

        dxSprite.matWorld =
            static_cast<D3DXMATRIX>(this->getTransform()
                                        .scale(Vector3f(this->textureRect.width, this->textureRect.height, 1.0F)));
        const CComPtr<ID3DX10Sprite> &spriteObject = target.getSpriteObject();

        if (HRESULT hresult = spriteObject->Begin(0);
            hresult == S_OK) {
            if (hresult = spriteObject->DrawSpritesImmediate(&dxSprite, 1, 0, 0);
                hresult == S_OK) {
                drawn = true;
            }
        }
        std::ignore = spriteObject->End();

        return drawn;
    }
}
