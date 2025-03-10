#include "Sector.h"
#include <algorithm>  // Include this for std::remove

namespace cse {
Sector::Sector(int x, int y)
    : x(x), y(y) {}

void Sector::add_circle(Circle* circle) {
    circles.push_back(circle);  // Vector of circles that will be part of the game
}

void Sector::remove_circle(Circle* circle) {
    circles.erase(std::remove(circles.begin(), circles.end(), circle), circles.end());
}

int Sector::get_circle_count() const {
    return circles.size();
}

Circle* Sector::get_circle_at(size_t index) const {
    if (index < circles.size()) {
        return circles[index];
    }
    return nullptr;
}
}