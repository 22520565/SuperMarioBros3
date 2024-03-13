#pragma once
#include "NonCopyable.hpp"

namespace game {
    class NonConstructible : public NonCopyable {
      public:
        constexpr ~NonConstructible() noexcept override = default;

      private:
        constexpr NonConstructible() noexcept = delete;
    };
}
