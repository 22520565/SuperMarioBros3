#include "RenderTarget.hpp"
#include "tchar.hpp"
#include "Texture.hpp"
#include "TextureHolder.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    inline TextureHolder::TextureHolder(const RenderTarget &renderTarget) noexcept
         : pRenderTarget(&renderTarget) {}

    ////////////////////////////////////////////////////////////
    inline const Texture *TextureHolder::getTexture(const tchar *const &fileName) const noexcept {
       const Texture * textureToGet = nullptr;

        if (const auto [itTexture, newTextureAdded] = textures.try_emplace(fileName, *this->pRenderTarget);
            (!newTextureAdded) || itTexture->second.loadFromFile(fileName)) [[likely]] {
            textureToGet = &(itTexture->second);
        }

        return textureToGet;
    }
}
