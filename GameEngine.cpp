#include "GameEngine.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    void GameEngine::input() {
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
    void GameEngine::draw() {
        this->window.clear();
        std::ignore = this->window.display();
    }
}
