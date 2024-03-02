#include "Sprite.hpp"

namespace game {
    Sprite::Sprite(const Texture& texture) : texture(&texture){
        D3DXMATRIX matTransform;
        D3DXMatrixIdentity(&matTransform);
       dxSprite = D3DX10_SPRITE{
           .matWorld= matTransform,
           .TexCoord=D3DXVECTOR2(),
           .TexSize=D3DXVECTOR2(texture.getSize().x,texture.getSize().y),
           .ColorModulate= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
           .pTexture= this->texture->getShaderResourceView(), // Set the sprite's shader resource view
           .TextureIndex=0U,
       };
    }

    Sprite::Sprite(int id, int left, int top, int right, int bottom, const Texture* tex) {
        //this->id = id;
        //this->left = left;
        //this->top = top;
        //this->right = right;
        //this->bottom = bottom;
        //this->texture = tex;

        //float texWidth = (float)tex->getSize().x;
        //float texHeight = (float)tex->getSize().y;

        //// Set the sprite's shader resource view
        //dxSprite.pTexture = tex->getShaderResourceView();

        //dxSprite.TexCoord.x = this->left / texWidth;
        //dxSprite.TexCoord.y = this->top / texHeight;

        //int spriteWidth = (this->right - this->left + 1);
        //int spriteHeight = (this->bottom - this->top + 1);

        //dxSprite.TexSize.x = spriteWidth / texWidth;
        //dxSprite.TexSize.y = spriteHeight / texHeight;

        //dxSprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        //dxSprite.TextureIndex = 0;

        //D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);
    }

    void Sprite::draw(RenderTarget& target) const {
        CComPtr<ID3DX10Sprite> g_pSprite = nullptr;
        HRESULT hr = D3DX10CreateSprite(target.getDevice(), 0, &g_pSprite);
        g_pSprite->Begin(0);;
        g_pSprite->DrawSpritesImmediate(&dxSprite, 1, 0, 0); 
        g_pSprite->End();
        }

    void Sprite::Draw(float x, float y) {
        /*Game *g = Game::GetInstance();
        float cx, cy;
        g->GetCamPos(cx, cy);

        cx = (FLOAT)floor(cx);
        cy = (FLOAT)floor(cy);

        D3DXMATRIX matTranslation;

        x = (FLOAT)floor(x);
        y = (FLOAT)floor(y);

        D3DXMatrixTranslation(&matTranslation, x - cx, g->GetBackBufferHeight() - y + cy, 0.1f);

        this->dxSprite.matWorld = (this->matScaling * matTranslation);

        g->GetSpriteHandler()->DrawSpritesImmediate(&dxSprite, 1, 0, 0);*/
    }
}
