#pragma once

#include <vector>
#include <Circle.h>

class Sector {
    public:
        int x, y;                       // Sector coordinates
        std::vector<Circle*> circles;   // Circles in the sector
        
        Sector(int x, int y);
        void add_circle(Circle* circle);
        void remove_circle(Circle* circle);
};