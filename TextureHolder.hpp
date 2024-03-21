#pragma once
#include "NonConstructible.hpp"
#include "RenderWindow.hpp"
#include "Texture.hpp"
#include <mutex>
#include <optional>
#include <unordered_map>
#include <winnt.h>

namespace game {
    // Manage textures' database
    class TextureHolder {
      public:
       explicit TextureHolder(const RenderTarget& renderTarget) noexcept;

     [[nodiscard]]const Texture * getTexture(const TCHAR *const &fileName);

      private:
        const RenderTarget*const pRenderTarget=nullptr;
        std::unordered_map<const TCHAR *, Texture> textures =
            std::unordered_map<const TCHAR *, Texture>();

        constexpr TextureHolder(const TextureHolder &) noexcept = delete;
        constexpr TextureHolder(TextureHolder &&) noexcept = delete;
        constexpr TextureHolder &operator=(const TextureHolder &) noexcept = delete;
        constexpr TextureHolder &operator=(TextureHolder &&) noexcept = delete;
    };
}

#include "TextureHolder.inl"
