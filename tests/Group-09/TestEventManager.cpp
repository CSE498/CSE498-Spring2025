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

  Event e2(2, 3, "Event 2!");
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
  Event e2(2, 3, "Event 2!");
  Event e3(4, 3, "Event 3\n");
  Event e4(1792, 3, "Event 3\n");

  eM.AddEvent(e1);
  eM.AddEvent(e2);
  eM.AddEvent(e3);
  eM.AddEvent(e4);

  REQUIRE(eM.getNumEvents() == 4);
  CHECK(eM.PauseEvent(1) == true);
  CHECK(eM.getNumPaused() == 1); //Add to event manager
  CHECK(eM.PauseEvent(1792) == true);
  CHECK(eM.getNumPaused() == 2);

}


TEST_CASE("Resume EventManager event", "[EventManager]")
{
  EventManager eM;

  Event e1(1, 1, "Event 1");
  Event e2(323, 3, "Event 2!");
  Event e3(2, 1202, "Event 3\n");
  Event e4(1792, 3, "Event 3\n");
  Event e5(213, 5, "Event 5.0");

  eM.AddEvent(e1);
  eM.AddEvent(e2);
  eM.AddEvent(e3);
  eM.AddEvent(e4);
  eM.AddEvent(e5);

  REQUIRE(eM.getNumEvents() == 5);
  eM.PauseEvent(1);
  eM.PauseEvent(323);
  CHECK(eM.ResumeEvent(323) == true);
  CHECK(eM.getNumPaused() == 1);
  CHECK(eM.ResumeEvent(1) == true);
  CHECK(eM.getNumPaused() == 0);
  CHECK(eM.ResumeEvent(1) == true);
  CHECK(eM.getNumPaused() == 0);

}

TEST_CASE("Trigger events", "[EventManager]")
{
  EventManager eM;

  Event e1(1, 1, "Event 1");
  Event e2(2, 3, "Event 2");
  Event e3(3, 5, "Event 3");

  eM.AddEvent(e1);
  eM.AddEvent(e2);
  eM.AddEvent(e3);

  REQUIRE(eM.getNumEvents() == 3);
  eM.StartQueue();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eM.getNumEvents() == 2);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eM.getNumEvents() == 1);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eM.getNumEvents() == 0);
}






