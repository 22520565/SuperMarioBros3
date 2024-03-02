#pragma once
#include "NonConstructible.hpp"
#include "Texture.hpp"
#include <mutex>
#include <optional>
#include <unordered_map>
#include <winnt.h>

namespace game {
    // Manage textures' database
    class Textures : public NonConstructible {
      public:
        static const Texture *getTexture(const TCHAR *const &fileName, const CComPtr<ID3D10Device>& device=nullptr);

      private:
        static inline std::unordered_map<const TCHAR * , Texture> textures =
            std::unordered_map<const TCHAR* , Texture>();
        static inline std::mutex mutex = std::mutex();
    };
}
