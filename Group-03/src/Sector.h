#pragma once

#include <vector>
#include "Circle.h"

namespace cse{
class Sector {
    public:
        int x, y;                       // Sector coordinates
        std::vector<Circle*> circles;   // Circles in the sector

        Sector(int x, int y);
        void add_circle(Circle* circle);
        void remove_circle(Circle* circle);

        // New accessor methods
        int get_circle_count() const;
        Circle* get_circle_at(size_t index) const;
};
}