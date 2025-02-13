/**
 * @file TestEvent.cpp
 *
 * @author Owen Haiar
 */

#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-09/Event/Event.hpp"

using namespace cse;

TEST_CASE("Test Event", "[base]")
{
  Event e(0, 1, "data");
  CHECK(e.getID() == 0);
  CHECK(e.getTime() == 1);
  CHECK(e.getData() == "data");
}