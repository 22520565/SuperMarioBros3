#pragma once

namespace game {
    class NonCopyable {
    public:
        constexpr virtual ~NonCopyable() noexcept = default;

    protected:
        constexpr NonCopyable() noexcept = default;

    private:
        constexpr NonCopyable(const NonCopyable &) noexcept = delete;
        constexpr NonCopyable(NonCopyable &&) noexcept = delete;
        constexpr NonCopyable &operator=(const NonCopyable &) noexcept = delete;
        constexpr NonCopyable &operator=(NonCopyable &&) noexcept = delete;
    };
}
