#include <Surface.h>

Surface::Surface(int width, int height, int sector_size) 
    : width(width), height(height), surface_size(sector_size), sector_width(width/sector_size), sector_height(height/sector_size){
    
    // I got all of this from copilot, I was going to make something similar
    sectors.resize(sector_width, std::vector<Sector>(sector_height, Sector(0, 0))); // Resize sectors vector
    for (int i = 0; i < sector_width; ++i) {
        for (int j = 0; j < sector_height; ++j) {
            sectors[i][j] = Sector(i, j);       // Initialize each sector
        }
    }
}

void Surface::add_circle(Circle* circle) {
    int x = circle->getX() / surface_size;   // Get the x coordinate of a circle
    int y = circle->getY() / surface_size;   // Get the y coordinate of a circle
    sectors[x][y].add_circle(circle);        // Add a circle to the sector
}

void Surface::move_circle(Circle* circle, float x_pos, float y_pos) {
    int x = circle->getX() / surface_size;          // Get the x coordinate of a circle
    int y = circle->getY() / surface_size;          // Get the y coordinate of a circle
    int new_x = x_pos / surface_size;               // Get new x coordinate
    int new_y = y_pos / surface_size;               // Get new y coordinate
    if (x != new_x || y != new_y) {                 // Check if the circle is in a different sector
        sectors[x][y].remove_circle(circle);        // Remove circle from old sector
        sectors[new_x][new_y].add_circle(circle);   // Add circle to new sector
    }
    circle->setPosition(x_pos, y_pos);       // Update the position of the circle
}

void Surface::check_collision() {
    
}
