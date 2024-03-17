#pragma once
#include "NonCopyable.hpp"
#include "Vector2.hpp"
#include <D3DX10.h>
#include <d3d10.h>
#include <tuple>

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"
#define WINDOW_ICON_PATH L"mario.ico"

namespace game {
    class WindowBase{
      public:
        ~WindowBase() noexcept;

        [[nodiscard]]
        bool isOpen() const noexcept;

        bool close() const noexcept;

        [[nodiscard]]
        const MSG *pollMsg() noexcept;

        [[nodiscard]]
        Vector2<int> getSize()const noexcept;

      protected:
          constexpr WindowBase() =default;

        WindowBase(const Vector2<int> &size, const TCHAR *const title, const int nCmdShow, 
            HINSTANCE hInstance,const TCHAR* const className) noexcept;

        [[nodiscard]]
        constexpr const HWND& getWindowHandler() const noexcept { return this->hWnd; }

      private:
        bool create(const Vector2<int> &size, const TCHAR *const title, const int nCmdShow, 
            HINSTANCE hInstance, const TCHAR* const className) noexcept;

        static LRESULT CALLBACK winProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

        HINSTANCE hInstance = nullptr;
        HWND hWnd = nullptr;
        const TCHAR* className = nullptr;
        MSG msg = MSG();

        constexpr WindowBase(const WindowBase&) noexcept = delete;
        constexpr WindowBase(WindowBase&&) noexcept = delete;
        constexpr WindowBase& operator=(const WindowBase&) noexcept = delete;
        constexpr WindowBase& operator=(WindowBase&&) noexcept = delete;
    };
}