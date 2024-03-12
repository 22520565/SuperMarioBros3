#include "Angle3.hpp"
#include "Vector3.hpp"
#include <iostream>

int main() {
    using game::operator""_deg;
    game::Angle3d a = game::Angle3d(3.4_deg, 4.5_deg, 2.4_deg);
    game::Vector3d b = game::Vector3d::one() * 3.0;
    game::Vector3f c(b * 3.0);
    std::cout << a.asRadians().x << ' ' << c.y;
}
