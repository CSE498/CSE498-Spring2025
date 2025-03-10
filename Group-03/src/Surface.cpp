#include "Surface.h"

namespace cse{
Surface::Surface(int width, int height, int sector_size)
    : surface_width(width), surface_height(height), surface_size(sector_size), sector_width(width/sector_size), sector_height(height/sector_size){

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

void Surface::move_circle(Circle* circle, int x_pos, int y_pos) {
    int x = circle->getX() / surface_size;          // Get the x coordinate of a circle
    int y = circle->getY() / surface_size;          // Get the y coordinate of a circle
    int new_x = x_pos / surface_size;               // Get new x coordinate
    int new_y = y_pos / surface_size;               // Get new y coordinate
    if (x != new_x || y != new_y) {                 // Check if the circle is in a different sector
        sectors[x][y].remove_circle(circle);        // Remove circle from old sector
        sectors[new_x][new_y].add_circle(circle);   // Add circle to new sector
    }
    circle->setPosition(x_pos, y_pos);              // Update the position of the circle
}

void Surface::check_collision() {
    // Iterate through all sectors
    for (int i = 0; i < sector_width; ++i) {
        for (int j = 0; j < sector_height; ++j) {
            Sector& current_sector = sectors[i][j];

            // Check for collisions within the same sector
            for (size_t a = 0; a < current_sector.circles.size(); ++a) {
                for (size_t b = a + 1; b < current_sector.circles.size(); ++b) {
                    if (current_sector.circles[a]->overlaps(*current_sector.circles[b])) {
                        // Collision detected, gotta figure out this part, will be done in next step
                        std::cout << "Collision detected in sector (" << i << ", " << j << ")\n";
                    }
                }
            }

            // Check collisions with neighboring sectors
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int neighbor_x = i + dx;
                    int neighbor_y = j + dy;

                    // Skip checking the sector with itself
                    if (dx == 0 && dy == 0) continue;

                    // Ensure neighbor is within bounds
                    if (neighbor_x >= 0 && neighbor_x < sector_width &&
                        neighbor_y >= 0 && neighbor_y < sector_height) {
                        Sector& neighbor_sector = sectors[neighbor_x][neighbor_y];

                        for (Circle* c1 : current_sector.circles) {
                            for (Circle* c2 : neighbor_sector.circles) {
                                if (c1->overlaps(*c2)) {
                                    std::cout << "Collision detected between sectors (" << i << ", " << j
                                              << ") and (" << neighbor_x << ", " << neighbor_y << ")\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Surface::update() {
    // Iterate through all sectors and update circle positions
    for (int i = 0; i < sector_width; ++i) {
        for (int j = 0; j < sector_height; ++j) {
            Sector& sector = sectors[i][j];

            for (size_t k = 0; k < sector.circles.size();) {
                Circle* circle = sector.circles[k];

                // Compute new sector based on updated position
                int new_x = circle->getX() / surface_size;
                int new_y = circle->getY() / surface_size;

                // Ensure new_x and new_y are within bounds
                new_x = std::max(0, std::min(new_x, sector_width - 1));
                new_y = std::max(0, std::min(new_y, sector_height - 1));

                // If the circle has moved to a new sector, remove and reassign
                if (new_x != i || new_y != j) {
                    sector.remove_circle(circle);
                    sectors[new_x][new_y].add_circle(circle);
                } else {
                    ++k;  // Only increment if no circle was removed (otherwise, we shift left)
                }
            }
        }
    }
}
}