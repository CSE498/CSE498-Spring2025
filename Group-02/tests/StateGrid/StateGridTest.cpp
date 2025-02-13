/**
 * @file StateGridTest.cpp
 * @author Dominik Leisinger
 */

#define CATCH_CONFIG_MAIN
#include "../../include/third-party/Catch/single_include/catch2/catch.hpp"
#include "../../include/cse/StateGrid.h"
#include <stdexcept>

TEST_CASE("StateGrid loads test map correctly")
{
  REQUIRE(1==1);
  cse::StateGrid grid ("test");

  SECTION("Testing Agent Row")
  {
    std::string agentrow;
    for (int col =0; col < 5; col++)
    {
      agentrow.push_back(grid.get_state(1,col));
    }
    REQUIRE(agentrow == "# P #");
  }
  SECTION("Testing Exit Placement")
  {
    REQUIRE(grid.get_state(4,1) == '0');
  }
}

TEST_CASE("Testing validate_position")
{
  cse::StateGrid grid ("test");

  SECTION("Trying to move to a wall (Any of the first row)")
  {
    REQUIRE_FALSE(grid.validate_position({0,3}));
  }

  SECTION("Trying to move to an enemy (X)")
  {
    REQUIRE(grid.validate_position({2, 2}));
  }

  SECTION("Trying an empty space")
  {
    REQUIRE(grid.validate_position({3,2}));
  }

}

TEST_CASE("Testing get_state moves agent correctly")
{
  cse::StateGrid grid ("test");

  SECTION("Move agent 'P' from (1,2) to ' ' (1,3)")
  {
    REQUIRE(grid.get_state(1,2) == 'P');
    REQUIRE(grid.get_state(1,3) == ' ');

    grid.set_state({1,3},{1,2});

    REQUIRE(grid.get_state(1,2) == ' ');
    REQUIRE(grid.get_state(1,3) == 'P');
  }

  SECTION("Move agent 'P' from (1,3) to 'X' (2,2)")
  {
    REQUIRE(grid.get_state(2,2) == 'X');
    REQUIRE(grid.get_state(1,2) == 'P');

    grid.set_state({2,2},{1,2});

    REQUIRE(grid.get_state(2,2) == 'P');
    REQUIRE(grid.get_state(1,2) == ' ');
  }

}

TEST_CASE("Testing if find_moves finds correct valid moves for agent")
{
  cse::StateGrid grid ("test");

  SECTION("Finding moves {(1,1),(1,3),(2,2)} from start position (1,2)")
  {
    std::vector<std::pair<int,int>> moves = grid.find_moves(1,2);

    REQUIRE(moves.size() == 3);

    std::vector<std::pair<int,int>> expmoves = {{1,1},{1,3},{2,2}};

    for (auto move : moves){
      auto selectedmove = std::find(expmoves.begin(), expmoves.end(), move);
      REQUIRE(selectedmove != expmoves.end());
    }


  }
}