#pragma once

#include <vector>
#include <Sector.h>

class Surface {
    public:
        int width, height, sector_width, sector_height, surface_size;
        std::vector<std::vector<Sector>> sectors;
        
        Surface(int width, int height, int sector_size);

        void add_circle(Circle* circle);
        void move_circle(Circle* circle, float x_pos, float y_pos);
        void check_collision();
        // void update();
};