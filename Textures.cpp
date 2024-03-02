#include "Textures.hpp"
#include "Texture.hpp"
#include <mutex>
#include <optional>
#include <windows.h>

namespace game {
    const Texture *Textures::getTexture(const TCHAR *const &fileName, const CComPtr<ID3D10Device> &device) {
        const std::scoped_lock lock = std::scoped_lock(mutex);

        const Texture *textureToGet = nullptr;
        if (const auto [itTexture, newTextureAdded] = textures.try_emplace(fileName);
            (!newTextureAdded) || itTexture->second.loadFromFile(fileName,device)) [[likely]] {
            textureToGet = &(itTexture->second);
        }
        return textureToGet;
    }
}
