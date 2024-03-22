#include "Sprite.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    inline Sprite::Sprite(const Texture &texture) noexcept(
        noexcept(Rect2uf32(Vector2uf32::zero(), texture.getSize())))
        : Sprite(texture, Rect2uf32(Vector2uf32::zero(), texture.getSize())) {}

    ////////////////////////////////////////////////////////////
    inline Sprite::Sprite(const Texture &texture, const Rect2uf32 &textureRect) noexcept
        : pTexture(&texture),
          dxSprite(D3DX10_SPRITE{
              .matWorld = D3DXMATRIX(),
              .TexCoord = D3DXVECTOR2(
                  static_cast<FLOAT>(textureRect.left) / static_cast<FLOAT>(texture.getSize().x),
                  static_cast<FLOAT>(textureRect.top) / static_cast<FLOAT>(texture.getSize().y)),
              .TexSize = D3DXVECTOR2(
                  static_cast<FLOAT>(textureRect.width) / static_cast<FLOAT>(texture.getSize().x),
                  static_cast<FLOAT>(textureRect.height) / static_cast<FLOAT>(texture.getSize().y)),
              .ColorModulate = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F),
              .pTexture = texture.getShaderResourceView(),
              .TextureIndex = 0U,
          }) {}

    ////////////////////////////////////////////////////////////
    inline const Texture *Sprite::getTexture() const noexcept { return this->pTexture; }

    ////////////////////////////////////////////////////////////
    constexpr const Rect2uf32 &Sprite::getTextureRect() const noexcept {
        return this->textureRect;
    }

    ////////////////////////////////////////////////////////////
    inline void Sprite::setTexture(const Texture &newTexture) noexcept(
        noexcept(Rect2uf32(Vector2uf32::zero(), newTexture.getSize()))) {
        this->setTexture(newTexture, Rect2uf32(Vector2uf32::zero(), newTexture.getSize()));
    }

    ////////////////////////////////////////////////////////////
    inline void Sprite::setTexture(const Texture &newTexture, const Rect2uf32 &newTextureRect) noexcept {
        this->pTexture = &newTexture;
        this->dxSprite.pTexture = newTexture.getShaderResourceView();
        this->setTextureRect(newTextureRect);
    }

    ////////////////////////////////////////////////////////////
    inline void Sprite::setTextureRect(const Rect2uf32 &newTextureRect) noexcept {
        const auto &textureSize = this->pTexture->getSize();
        this->textureRect = newTextureRect;
        this->dxSprite.TexCoord = D3DXVECTOR2(
            static_cast<FLOAT>(newTextureRect.left) / static_cast<FLOAT>(textureSize.x),
            static_cast<FLOAT>(newTextureRect.top) / static_cast<FLOAT>(textureSize.y));
        this->dxSprite.TexSize = D3DXVECTOR2(
            static_cast<FLOAT>(newTextureRect.width) / static_cast<FLOAT>(textureSize.x),
            static_cast<FLOAT>(newTextureRect.height) / static_cast<FLOAT>(textureSize.y));
    }

    ////////////////////////////////////////////////////////////
    constexpr Rect2f Sprite::getLocalBounds() const noexcept {
        return Rect2f(static_cast<Vector2f>(Vector2uf32::unitY() * this->textureRect.getSize().y),
                      static_cast<Vector2f>(this->textureRect.getSize()));
    }

    ////////////////////////////////////////////////////////////
    constexpr Rect2f Sprite::getGlobalBounds() const noexcept {
        return static_cast<Rect2f>(this->getTransform().transformRect(Rect3f(this->getLocalBounds())));
    }

    ////////////////////////////////////////////////////////////
    inline bool Sprite::draw(const RenderTarget &target) const noexcept {
        bool drawn = false;

        const CComPtr<ID3DX10Sprite> &spriteObject = target.getSpriteObject();
        dxSprite.matWorld = static_cast<D3DXMATRIX>(
            this->getTransform().scale(Vector3f(this->textureRect.width, this->textureRect.height, 1.0F)));

        if (HRESULT hresult = spriteObject->Begin(0);
            SUCCEEDED(hresult)) [[likely]] {
            if (hresult = spriteObject->DrawSpritesImmediate(&dxSprite, 1, 0, 0);
                SUCCEEDED(hresult)) [[likely]] {
                drawn = true;
            }
        }
        std::ignore = spriteObject->End();

        return drawn;
    }
}
