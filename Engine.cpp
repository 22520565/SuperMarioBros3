#include "Engine.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    void Engine::input() {
        for (const MSG *msg = window.pollMsg(); msg != nullptr; msg = window.pollMsg()) {
            switch (msg->message) {
            case WM_QUIT:
                std::ignore = this->window.close();
                break;

            default:
                break;
            }
        }
    }

    ////////////////////////////////////////////////////////////
    void Engine::draw() {
        this->window.clear();
        std::ignore = this->window.display();
    }
}
