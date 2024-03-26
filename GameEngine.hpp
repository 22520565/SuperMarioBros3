#pragma once
#include "Clock.hpp"
#include "RenderWindow.hpp"
#include "TextureHolder.hpp"
#include "Keyboard.hpp"
#include "Mario.hpp"

namespace game {
    class GameEngine final {
      public:
        explicit GameEngine(const WindowSettings& windowSettings) noexcept;
        void run();

      private:
        InputBase inputBase = InputBase(GetModuleHandle(nullptr));
        Keyboard keyboard = Keyboard(inputBase);

        Mario mario = Mario();

        RenderWindow window = RenderWindow(WindowSettings());
        TextureHolder textureHolder = TextureHolder(window);
        void input();
        void update(const Time deltaTime);
        void draw();
    };
}

#include "GameEngine.inl"
