/* =============================================================
    INTRODUCTION TO GAME PROGRAMMING SE102

    SAMPLE 05 - SCENE MANAGER

    This sample illustrates how to:

        1/ Read scene (textures, sprites, animations and objects) from files
        2/ Handle multiple scenes in game

    Key classes/functions:
        Scene
        PlayScene


HOW TO INSTALL Microsoft.DXSDK.D3DX
===================================
1) Tools > NuGet package manager > Package Manager Console
2) execute command :  Install-Package Microsoft.DXSDK.D3DX


================================================================ */

#include <d3d10.h>
#include <d3dx10.h>
#include <list>
#include <windows.h>

#include "Animation.hpp"
#include "Animations.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Textures.hpp"
#include "debug.hpp"

#include "Brick.hpp"
#include "Coin.hpp"
#include "Goomba.hpp"
#include "Mario.hpp"
#include "Platform.hpp"

#include "SampleKeyEventHandler.hpp"

#include "AssetIDs.hpp"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f / 255, 200.0f / 255, 255.0f / 255, 0.0f)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

/*
    Update world status for this frame
    dt: time period between beginning of last frame and beginning of this frame
*/
void update(DWORD dt) {
    game::Game::GetInstance()->GetCurrentScene()->update(dt);
}

/*
    Render a frame
*/
void render() {
    game::Game *g = game::Game::GetInstance();

    ID3D10Device *pD3DDevice = g->GetDirect3DDevice();
    IDXGISwapChain *pSwapChain = g->GetSwapChain();
    ID3D10RenderTargetView *pRenderTargetView = g->GetRenderTargetView();
    ID3DX10Sprite *spriteHandler = g->GetSpriteHandler();

    pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

    spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

    FLOAT NewBlendFactor[4] = {0, 0, 0, 0};
    pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

    game::Game::GetInstance()->GetCurrentScene()->render();

    spriteHandler->End();
    pSwapChain->Present(0, 0);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight) {
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = hInstance;

    wc.lpfnWndProc = (WNDPROC)WinProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);

    HWND hWnd =
        CreateWindow(
            WINDOW_CLASS_NAME,
            MAIN_WINDOW_TITLE,
            WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            ScreenWidth,
            ScreenHeight,
            NULL,
            NULL,
            hInstance,
            NULL);

    if (!hWnd) {
        OutputDebugString(L"[ERROR] CreateWindow failed");
        DWORD ErrCode = GetLastError();
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return hWnd;
}

int Run() {
    MSG msg;
    int done = 0;
    ULONGLONG frameStart = GetTickCount64();
    DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

    while (!done) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                done = 1;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ULONGLONG now = GetTickCount64();

        // dt: the time between (beginning of last frame) and now
        // this frame: the frame we are about to render
        DWORD dt = (DWORD)(now - frameStart);

        if (dt >= tickPerFrame) {
            frameStart = now;

            game::Game::GetInstance()->ProcessKeyboard();
            update(dt);
            render();

            game::Game::GetInstance()->SwitchScene();
        } else
            Sleep(tickPerFrame - dt);
    }

    return 1;
}

int main() {
    auto hInstance = GetModuleHandle(nullptr);

    HWND hWnd = CreateGameWindow(hInstance, SW_SHOWNORMAL, SCREEN_WIDTH, SCREEN_HEIGHT);
    game::SetDebugWindow(hWnd);

    game::LPGAME game = game::Game::GetInstance();
    game->Init(hWnd, hInstance);
    game->InitKeyboard();

    // IMPORTANT: this is the only place where a hardcoded file name is allowed !
    game->Load(L"mario-sample.txt");

    SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

    Run();

    return 0;
}
