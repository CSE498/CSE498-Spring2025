/**
 * @file StateGridPositionTest.cpp
 * @author Bram Hogg
 */

#include <catch2/catch.hpp>
#include <cse/StateGridPosition.h>

TEST_CASE("default values are 0s")
{
    REQUIRE(1==1);
    cse::StateGridPosition position;

    SECTION("default central position (0, 0)") {
        cse::Point central_pos = position.get_grid_position();
        REQUIRE(central_pos.x_position == 0);
        REQUIRE(central_pos.y_position == 0);
    }

    SECTION("default object position (0, 0)") {
        cse::Point object_pos = position.get_object_position();
        REQUIRE(object_pos.x_position == 0);
        REQUIRE(object_pos.y_position == 0);
    }

    SECTION("default object orientation 0 degrees") {
        REQUIRE(position.get_object_orientation() == 0);
    }
}

TEST_CASE("set and get object position") {
    cse::StateGridPosition position;

    SECTION("set object position to (2, 3)") {
        position.set_object_position(2, 3);
        cse::Point object_pos = position.get_object_position();
        REQUIRE(object_pos.x_position == 2);
        REQUIRE(object_pos.y_position == 3);
    }

    SECTION("set object position to (-2.5, 2.5)") {
        position.set_object_position(-2.5, 2.5);
        cse::Point object_pos = position.get_object_position();
        REQUIRE(object_pos.x_position == -2.5);
        REQUIRE(object_pos.y_position == 2.5);
    }
}

TEST_CASE("set and get object orientation") {
    cse::StateGridPosition position;

    SECTION("object orientation 25 degrees") {
        position.set_object_orientation(25);
        REQUIRE(position.get_object_orientation() == 25);
    }

    SECTION("object orientation at 400 degrees calculates") {
        position.set_object_orientation(400);
        REQUIRE(position.get_object_orientation() == 40);
    }

    SECTION("object orientation of -30 degrees should be 330") {
        position.set_object_orientation(-30);
        REQUIRE(position.get_object_orientation() == 330);
    }
}

TEST_CASE("calculate object position correctly")
{
    cse::StateGridPosition position;

    SECTION("calculate_object_position is default (0, 0)")
    {
        cse::Point calculated_pos = position.calculate_object_position();
        REQUIRE(calculated_pos.x_position == 0);
        REQUIRE(calculated_pos.y_position == 0);
    }
}

TEST_CASE("default nullptr StateGrid") {
    cse::StateGridPosition position;

    SECTION("should be nullptr by default") {
        REQUIRE(position.get_state_grid() == nullptr);
    }
}
