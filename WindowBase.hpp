#pragma once
#include "Vector2.hpp"
#include <D3DX10.h>
#include <d3d10.h>
#include <tuple>
#include "tchar.hpp"

namespace game {
    class WindowBase {
      public:
        ~WindowBase() noexcept;

        [[nodiscard]]
        bool isOpen() const noexcept;

        bool close() const noexcept;

        [[nodiscard]]
        const MSG *pollMsg() noexcept;

        [[nodiscard]]
        Vector2<int> getSize() const noexcept;

      protected:
        constexpr WindowBase() = default;

       explicit WindowBase(const Vector2<int> &size, const tchar *const title, const tchar *const iconPath,
                   const tchar *const className, const HINSTANCE hInstance, const int nCmdShow) noexcept;

        [[nodiscard]]
        constexpr const HWND &getWindowHandler() const noexcept { return this->hWnd; }

      private:
        bool create(const Vector2<int> &size, const tchar *const title, const tchar *const iconPath,
                    const tchar *const className, const HINSTANCE hInstance, const int nCmdShow) noexcept;

        static LRESULT CALLBACK winProc(const HWND hWnd, const UINT message,
                                        const WPARAM wParam, const LPARAM lParam) noexcept;

        HINSTANCE hInstance = nullptr;
        HWND hWnd = nullptr;
        const tchar *className = nullptr;
        MSG msg = MSG();

        constexpr WindowBase(const WindowBase &) noexcept = delete;
        constexpr WindowBase(WindowBase &&) noexcept = delete;
        constexpr WindowBase &operator=(const WindowBase &) noexcept = delete;
        constexpr WindowBase &operator=(WindowBase &&) noexcept = delete;
    };
}

#include "WindowBase.inl"
