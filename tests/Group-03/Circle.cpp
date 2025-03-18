#define CATCH_CONFIG_MAIN
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-03/src/Circle.h"
#include "../../Group-03/src/Surface.h"

TEST_CASE("CircleTest1", "CircleInitialization") {
    Circle circle(5.0, 10.0, 3.0, 2, 2, "red");
    CHECK(circle.getX() == 5.0);
    CHECK(circle.getY() == 10.0);
    CHECK(circle.getRadius() == 3.0);
}

TEST_CASE("CircleTest2", "CircleInvalidRadius") {
    CHECK_THROWS_AS(Circle(0.0, 0.0, -1.0, 2, 2, "red"), std::invalid_argument);
}

TEST_CASE("SurfaceTest1", "AddCircleToSurface") {
    cse::Surface surface(100, 100, 10);
    Circle circle(15.0, 25.0, 5.0, 2, 2, "red");
    surface.add_circle(&circle);

    int x = circle.getX() / surface.surface_size;
    int y = circle.getY() / surface.surface_size;
    CHECK(surface.sectors[x][y].circles.size() == 1);
    CHECK(surface.sectors[x][y].circles[0]->getX() == 15.0);
    CHECK(surface.sectors[x][y].circles[0]->getY() == 25.0);
    CHECK(surface.sectors[x][y].circles[0]->getRadius() == 5.0);
}

TEST_CASE("SurfaceTest2", "MoveCircleOnSurface") {
    cse::Surface surface(100, 100, 10);
    Circle circle(15.0, 25.0, 5.0, 2, 2, "red");
    surface.add_circle(&circle);

    surface.move_circle(&circle, 35.0, 45.0);

    int old_x = 15.0 / surface.surface_size;
    int old_y = 25.0 / surface.surface_size;
    int new_x = 35.0 / surface.surface_size;
    int new_y = 45.0 / surface.surface_size;

    CHECK(surface.sectors[old_x][old_y].circles.size() == 0);
    CHECK(surface.sectors[new_x][new_y].circles.size() == 1);
    CHECK(surface.sectors[new_x][new_y].circles[0]->getX() == 35.0);
    CHECK(surface.sectors[new_x][new_y].circles[0]->getY() == 45.0);
    CHECK(surface.sectors[new_x][new_y].circles[0]->getRadius() == 5.0);
}
