#pragma once
#include "NonCopyable.hpp"
#include "Vector2.hpp"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"
#define WINDOW_ICON_PATH L"mario.ico"

namespace game {
    class WindowBase : public NonCopyable {
    public:
       const HWND getSystemHandler() const { return this->hWnd; }

       bool isOpen() { return IsWindow(hWnd); }

       bool pollMsg(MSG& msg) {
           bool result = false;
           if (PeekMessage(&msg, hWnd, 0U, 0U, PM_REMOVE)) {
               TranslateMessage(&msg);
               DispatchMessage(&msg);
               result = true;
           }
           return result;
       }
    
       bool close() { return DestroyWindow(hWnd); }
    protected:
        HWND hWnd = nullptr;
        MSG msg = MSG();
        const Vector2<int> size = Vector2<int>();
        WindowBase();
        WindowBase(const Vector2<int> &size, int nCmdShow):size(size) {
            WNDCLASSEX wc = WNDCLASSEX{
                .cbSize = sizeof(WNDCLASSEX),
                .style = CS_HREDRAW | CS_VREDRAW,
                .lpfnWndProc = (WNDPROC)WinProc,
                .cbClsExtra = 0,
                .cbWndExtra = 0,
                .hInstance = GetModuleHandle(nullptr),
                .hIcon = static_cast<HICON>(
                    LoadImage(wc.hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE)),
                .hCursor = LoadCursor(nullptr, IDC_ARROW),
                .lpszMenuName = nullptr,
                .lpszClassName = WINDOW_CLASS_NAME,
                .hIconSm = nullptr,
            };
            RegisterClassEx(&wc);
            hWnd = CreateWindow(
                WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE, WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
                CW_USEDEFAULT, CW_USEDEFAULT, size.x, size.y,
                nullptr, nullptr, wc.hInstance, nullptr);
            if (hWnd != nullptr) [[likely]] {
                ShowWindow(hWnd, nCmdShow);
                UpdateWindow(hWnd);
            } else [[unlikely]] {
                OutputDebugString(L"[ERROR] CreateWindow failed");
                DWORD ErrCode = GetLastError();
            }
        }
        virtual Vector2<int> getSize() const { return this->size; }

        static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
            LRESULT lresult = 0;

            switch (message) {
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            default:
                lresult = DefWindowProc(hWnd, message, wParam, lParam);
                break;
            }

            return lresult;
        }
    };
}