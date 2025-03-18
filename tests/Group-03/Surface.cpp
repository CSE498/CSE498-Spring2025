#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include <vector>
#include "../../Group-03/src/Sector.h"
#include "../../Group-03/src/Surface.h"
#include "../../Group-03/src/Circle.h"
#define CATCH_CONFIG_MAIN
namespace cse {
    TEST_CASE("SectorTest 1", "Add") {
        Sector sector(0, 0);
        Circle circle(0, 0, 1, 1, 1, "red");
        sector.add_circle(&circle);
        CHECK(sector.circles.size() == 1);
    }

    TEST_CASE("SectorTest 2", "Remove") {
        Sector sector(0, 0);
        Circle circle(0, 0, 1, 1, 1, "red");
        sector.add_circle(&circle);
        sector.remove_circle(&circle);
        CHECK(sector.circles.size() == 0);
    }

    TEST_CASE("SurfaceTest 1", "Add") {
        Surface surface(100, 100, 10);
        Circle circle(5, 5, 1, 1, 1, "red");
        surface.add_circle(&circle);
        CHECK(surface.sectors[0][0].circles.size() == 1);
    }

    TEST_CASE("SurfaceTest 2", "Move") {
        Surface surface(100, 100, 10);
        Circle circle(5, 5, 1, 1, 1, "blue");
        surface.add_circle(&circle);
        surface.move_circle(&circle, 15, 15); // Move to a different sector
        CHECK(surface.sectors[1][1].circles.size() == 1); // Check new sector
        CHECK(surface.sectors[0][0].circles.size() == 0); // Check old sector
    }

}