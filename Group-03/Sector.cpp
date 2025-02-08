#include <Sector.h>

Sector::Sector(int x, int y) 
    : x(x), y(y) {}

void Sector::add_circle(Circle* circle) {
    circles.push_back(circle);  // Vector of circles that will be part of the game
}

void Sector::remove_circle(Circle* circle) {
    circles.erase(std::remove(circles.begin(), circles.end(), circle), circles.end());
}