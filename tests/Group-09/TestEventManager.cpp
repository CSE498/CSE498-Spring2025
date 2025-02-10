/**
 * @file TestEventManager.cpp
 * @author Grace Fitzgerald
 */

#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-09/EventManager/EventManager.cpp"
#include "../../Group-09/EventQueue/EventQueue.cpp"

using namespace cse;

///Not currently passing - working on way to incorporate duplicate checking

TEST_CASE("Add event to EventManager", "[EventManager]")
{
  EventManager eM;

  Event e1(1, 1, "Event 1");
  CHECK(eM.AddEvent(e1) == true);
  CHECK(eM.AddEvent(e1) == false);
  CHECK(eM.getNumEvents() == 1);

  Event e2(2,3,"Event 2!");
  CHECK(eM.AddEvent(e2) == true);
  CHECK(eM.getNumEvents() == 2);

  Event e3(2, 3, "Event 3\n");
  CHECK(eM.AddEvent(e3) == false);
  CHECK(eM.getNumEvents() == 2);
}

TEST_CASE("Pause EventManager event - valid", "[EventManager]")
{
  EventManager eM;

  Event e1(1, 1, "Event 1");
  Event e2(2,3,"Event 2!");
  Event e3(4, 3, "Event 3\n");
  Event e4(1792, 3, "Event 3\n");

  REQUIRE(eM.getNumEvents() == 4);
  CHECK(eM.PauseEvent(1) == true);
  CHECK(eM.getNumPaused() == 1); //Add to event manager
  CHECK(eM.PauseEvent(1792) == true);
  CHECK(eM.getNumPaused() == 2);

}

TEST_CASE("Pause EventManager event - invalid", "[EventManager]")
{
  EventManager eM;

  Event e1(1, 1, "Time 1");
  Event e2(2,3,"Time 3");
  Event e3(4, 3, "Time 3 - id 4");
  Event e4(931, 3, "Id 931");

  REQUIRE(eM.getNumEvents() == 4);
  eM.PauseEvent(1);

  CHECK(eM.PauseEvent(3) == false);
  CHECK(eM.getNumPaused() == 2);
  CHECK(eM.PauseEvent(-12) == false);
  CHECK(eM.getNumPaused() == 2);
  CHECK(eM.PauseEvent(1) == false);



}

