#include "Textures.hpp"
#include "Texture.hpp"
#include <mutex>
#include <optional>
#include <windows.h>

namespace game {
    const Texture *Textures::getTexture(const TCHAR *const &fileName) {
        const std::scoped_lock lock = std::scoped_lock(mutex);

        const Texture *textureToGet = nullptr;
        if (const auto [itTexture, newTextureAdded] = textures.try_emplace(fileName);
            (!newTextureAdded) || itTexture->second.loadFromFile(fileName)) [[likely]] {
            textureToGet = &(itTexture->second);
        }
        return textureToGet;
    }
}
