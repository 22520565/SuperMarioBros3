#pragma once
#include "Vector2.hpp"
#include "WindowSettings.hpp"
#include <minwindef.h>
#include <windef.h>
#include <WinUser.h>

namespace game {
    class Window {
      public:
        virtual ~Window() noexcept;

        [[nodiscard]]
        bool isOpen() const noexcept;

        bool close() const noexcept;

        [[nodiscard]]
        const MSG *pollMsg() noexcept;

        [[nodiscard]]
       constexpr const Vector2<int>& getSize() const noexcept;

      protected:
        constexpr Window() = default;

       explicit Window(const WindowSettings &newSettings) noexcept;

        [[nodiscard]]
        constexpr const HWND &getWindowHandler() const noexcept { return this->hWnd; }

      private:
        bool create(const WindowSettings& newSettings) noexcept;

        static LRESULT CALLBACK winProc(const HWND hWnd, const UINT message,
                                        const WPARAM wParam, const LPARAM lParam) noexcept;

        WindowSettings settings = WindowSettings();
        HWND hWnd = nullptr;
        MSG msg = MSG();

        constexpr Window(const Window &) noexcept = delete;
        constexpr Window(Window &&) noexcept = delete;
        constexpr Window &operator=(const Window &) noexcept = delete;
        constexpr Window &operator=(Window &&) noexcept = delete;
    };
}

#include "Window.inl"
