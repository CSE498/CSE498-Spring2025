#pragma once

#include <vector>
#include <iostream>
#include "Sector.h"

namespace cse{
class Surface {
    public:
        // These will be changed to fixed points in the future
        int surface_size;
        int surface_width;
        int surface_height;
        int sector_width;
        int sector_height;
        std::vector<std::vector<Sector>> sectors;

        Surface(int width, int height, int sector_size);

        void add_circle(Circle* circle);
        void move_circle(Circle* circle, int x_pos, int y_pos);
        void check_collision();
        void update();
};
}