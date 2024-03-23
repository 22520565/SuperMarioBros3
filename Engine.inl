#include "Clock.hpp"
#include "Engine.hpp"
#include "Time.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    inline Engine::Engine(const Vector2<int> &windowSize, const TCHAR *const windowTitle,
                          const TCHAR *const windowIconPath, const TCHAR *const windowClassName,
                          const HINSTANCE hInstance, const int nCmdShow) noexcept
        : window(windowSize, windowTitle, windowIconPath, windowClassName, hInstance, nCmdShow) {}

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
