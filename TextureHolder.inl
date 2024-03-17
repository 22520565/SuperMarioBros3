#include "Texture.hpp"
#include "TextureHolder.hpp"
#include <windows.h>

namespace game {
    ////////////////////////////////////////////////////////////
    inline TextureHolder::TextureHolder(const RenderTarget &renderTarget) noexcept
         : pRenderTarget(&renderTarget) {}

    ////////////////////////////////////////////////////////////
    inline const Texture *TextureHolder::getTexture(const TCHAR *const &fileName) {
       const Texture * textureToGet = nullptr;

        if (const auto [itTexture, newTextureAdded] = textures.try_emplace(fileName, *this->pRenderTarget);
            (!newTextureAdded) || itTexture->second.loadFromFile(fileName)) [[likely]] {
            textureToGet = &(itTexture->second);
        }

        return textureToGet;
    }
}
