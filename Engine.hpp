#pragma once
#include "Clock.hpp"
#include "RenderWindow.hpp"
#include "TextureHolder.hpp"

namespace game {
    class Engine final {
      public:
        explicit Engine(const Vector2<int> &windowSize, const TCHAR *const windowTitle,
                        const TCHAR *const windowIconPath, const TCHAR *const windowClassName,
                        const HINSTANCE hInstance, const int nCmdShow) noexcept;
        void run();

      private:
        RenderWindow window = RenderWindow(Vector2i(800, 600), L"Mario", nullptr,
                                           L"GameWindow", GetModuleHandle(nullptr), SW_SHOWNORMAL);
        TextureHolder textureHolder = TextureHolder(window);
        void input();
        void update(const Time deltaTime);
        void draw();
    };
}

#include "Engine.inl"
