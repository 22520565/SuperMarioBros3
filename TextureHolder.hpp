#pragma once
#include "RenderWindow.hpp"
#include "Texture.hpp"
#include <mutex>
#include <optional>
#include <unordered_map>
#include "tchar.hpp"

namespace game {
    // Manage textures' database
    class TextureHolder {
      public:
       explicit TextureHolder(const RenderTarget& renderTarget) noexcept;

     [[nodiscard]]const Texture * getTexture(const tchar *const &fileName) const noexcept;

      private:
        const RenderTarget*const pRenderTarget=nullptr;
       mutable std::unordered_map<const tchar *, Texture> textures =
            std::unordered_map<const tchar *, Texture>();

        constexpr TextureHolder(const TextureHolder &) noexcept = delete;
        constexpr TextureHolder(TextureHolder &&) noexcept = delete;
        constexpr TextureHolder &operator=(const TextureHolder &) noexcept = delete;
        constexpr TextureHolder &operator=(TextureHolder &&) noexcept = delete;
    };
}

#include "TextureHolder.inl"
