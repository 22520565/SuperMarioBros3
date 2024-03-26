#include "Clock.hpp"
#include "GameEngine.hpp"
#include "Time.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    inline GameEngine::GameEngine(const WindowSettings& windowSettings) noexcept
        : window(windowSettings) {}

    ////////////////////////////////////////////////////////////
    inline void GameEngine::run() {
        Clock timeClock = Clock();

        while (this->window.isOpen()) {
            const Time deltaTime = timeClock.restart();

            this->input();
            this->update(deltaTime);
            this->draw();
        }
    }
}
