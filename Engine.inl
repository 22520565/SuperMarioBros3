#include "Clock.hpp"
#include "Engine.hpp"
#include "Time.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    inline Engine::Engine(const WindowSettings& windowSettings) noexcept
        : window(windowSettings) {}

    ////////////////////////////////////////////////////////////
    inline void Engine::run() {
        Clock timeClock = Clock();

        while (this->window.isOpen()) {
            const Time deltaTime = timeClock.restart();

            this->input();
            this->update(deltaTime);
            this->draw();
        }
    }
}
