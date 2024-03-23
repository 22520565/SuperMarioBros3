#include "Collidable.hpp"

namespace game {
    constexpr bool game::Collidable::isCollided(const Collidable &collidable) const noexcept {
        return this->getGlobalBounds().findIntersection(collidable.getGlobalBounds()).has_value();
    }
}
