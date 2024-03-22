#pragma once

#include "Drawable.hpp"
#include "Rect2.hpp"
#include "RenderTarget.hpp"
#include "Texture.hpp"
#include "Transformable.hpp"

namespace game {
    class Sprite : public Drawable, public Transformable<float> {
      public:
        constexpr Sprite() = default;

        explicit Sprite(const Texture &texture) noexcept(
            noexcept(Rect2uf32(Vector2uf32::zero(), texture.getSize())));

        explicit Sprite(const Texture &texture, const Rect2uf32 &textureRect) noexcept;

        const Texture *getTexture() const noexcept;

        constexpr const Rect2uf32 &getTextureRect() const noexcept;

        void setTexture(const Texture &newTexture) noexcept(
            noexcept(Rect2uf32(Vector2uf32::zero(), newTexture.getSize())));

        void setTexture(const Texture &newTexture, const Rect2uf32 &newTextureRect) noexcept;

        void setTextureRect(const Rect2uf32 &newTextureRect) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the local bounding rectangle of the entity.
        ///
        /// The returned rectangle is in local coordinates, which means
        /// that it ignores the transformations (translation, rotation,
        /// scale, ...) that are applied to the entity.
        /// In other words, this function returns the bounds of the
        /// entity in the entity's coordinate system.
        ///
        /// \return Local bounding rectangle of the entity.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Rect2f getLocalBounds() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the global bounding rectangle of the entity.
        ///
        /// The returned rectangle is in global coordinates, which means
        /// that it takes into account the transformations (translation,
        /// rotation, scale, ...) that are applied to the entity.
        /// In other words, this function returns the bounds of the
        /// sprite in the global 2D world's coordinate system.
        ///
        /// \return Global bounding rectangle of the entity.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Rect2f getGlobalBounds() const noexcept;

      private:
        //   int id; // Sprite ID in the sprite database
        const Texture *pTexture = nullptr;

        mutable D3DX10_SPRITE dxSprite = D3DX10_SPRITE{
            .matWorld = D3DXMATRIX(),
            .TexCoord = D3DXVECTOR2(),
            .TexSize = D3DXVECTOR2(),
            .ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
            .pTexture = nullptr, // Set the sprite's shader resource view
            .TextureIndex = 0U,
        };

        bool draw(const RenderTarget &target) const noexcept override;

        Rect2uf32 textureRect = Rect2uf32();
    };

    typedef Sprite *LPSPRITE;
}

#include "Sprite.inl"
