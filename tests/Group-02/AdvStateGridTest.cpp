/**
 * @file AdvStateGridTest.cpp
 * @author Dominik Leisinger
 */
#include <catch2/catch.hpp>
#include <cse/StateGrid.h>
#include <stdexcept>

TEST_CASE("Testing load_map returns a valid map")
{
    ///This test is assuming we have implemented a file manager
    ///that loads pre-built files from a CSV in load-map()

    cse::StateGrid grid("hard");

    ///Test if m_grid has been set through load_map
    REQUIRE(grid.m_grid);

    ///If test map was loaded, there was an error
    REQUIRE_FALSE(grid.get_state(1,2) != 'P');

    ///Test if correct map has been loaded
    /// ('hard' would load a larger and more challenging map)
    REQUIRE(grid.get_state(1,6) == 'P');
    REQUIRE(grid.get_state(11,10) == '0');

    ///Possible new state (boulder that can be pushed)
    REQUIRE(grid.get_state(2,6) == 'o')
    ///Want to implement a liquid type (water,lava)
    for(int i=0; i<6; i++)
    {
        REQUIRE(grid.get_state(6,i) == 'w');
    }

}


TEST_CASE("Testing find_properties returns correct values")
{
    ///For now, and clarity of purpose, assuming find_properties returns
    ///a map with the direction from agent as key, and a list of properties
    ///of the state in that direction as the value
    ///Using map info from above as context for testing

    cse::StateGrid grid("hard");
    SECTION("Testing initial position")
    {
        ///Current agent location will be a member variable
        auto props = grid.find_properties();

        REQUIRE(props.at("DOWN") == {"Boulder", "Open", "Pushable"});
        REQUIRE(props.at("LEFT")) == {"EmptySpace", "Open"});
        REQUIRE(props.at("RIGHT")) == {"EmptySpace", "Open"});
        REQUIRE(props.at("UP")) == {"Wall", "Closed"});
    }

    SECTION("Testing after movement")
    {
        grid.set_state(2,6);

        auto props = grid.find_properties();
        REQUIRE(props.at("DOWN") == {"Boulder", "Open", "Pushable"});
        REQUIRE(props.at("LEFT")) == {"Wall", "Closed"});
        REQUIRE(props.at("RIGHT")) == {"Wall", "Closed"});
        REQUIRE(props.at("UP") == {"EmptySpace", "Open"});

    }
}

TEST_CASE("Testing set_condition and remove_condition functioning correctly")
{
    cse::StateGrid grid("hard");

    auto props = grid.define_state('w');
    REQUIRE(props.find("Deadly") != props.end());

    ///In this example, the agent would have just picked up
    ///a possible power-up called "Lava Shoes"
    grid.remove_condition({'w',"Deadly");
    auto props = grid.define_state('w');

    ///Definition for Lava throughout the grid is now changed
    REQUIRE(props.find("Deadly") == props.end());

    ///Another example where a possible Agent just became
    ///low on health, and considered 'weakened'
    grid.set_condition({'o',"Immovable"});
    auto props = grid.define_state('o');

    ///Function would analyze differing properties like:
    ///Pushable and Immovable,not allowing both to be active at once
    REQUIRE(props.find("Pushable") == props.end());
    REQUIRE(props.find("Immovable") != props.end());

}