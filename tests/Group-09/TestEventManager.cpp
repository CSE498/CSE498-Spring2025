/**
 * @file TestEventManager.cpp
 * @author Grace Fitzgerald
 */

#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-09/EventManager/EventManager.cpp"
#include "../../Group-09/EventQueue/EventQueue.cpp"

using namespace cse;

TEST_CASE("Add event to EventManager", "[EventManager]")
{
  EventManager eM;

  Event e1(0, 1, "Event 1");
  CHECK(eM.AddEvent(1, "Event 1").value() == e1);
  CHECK(eM.getNumEvents() == 1);

  Event e2(1, 3, "Event 2!");
  CHECK(eM.AddEvent(3, "Event 2!").value() == e2);
  CHECK(eM.getNumEvents() == 2);

  Event e3(2, 3, "Event 3\n");
  CHECK(eM.AddEvent(3, "Event 3\n").value() == e3);
  CHECK(eM.getNumEvents() == 3);
}

TEST_CASE("Pause EventManager event - valid", "[EventManager]")
{
  EventManager eM;

  Event e1 = eM.AddEvent(1, "Event 1").value();
  Event e2 = eM.AddEvent(3, "Event 2!").value();
  Event e3 = eM.AddEvent(3, "Event 3\n").value();
  Event e4 = eM.AddEvent(3, "_Event_4_").value();

  REQUIRE(eM.getNumEvents() == 4);
  CHECK(eM.PauseEvent(e1) == true);
  CHECK(eM.getNumPaused() == 1); //Add to event manager
  CHECK(eM.PauseEvent(e3) == true);
  CHECK(eM.getNumPaused() == 2);

}

TEST_CASE("Resume EventManager event", "[EventManager]")
{
  EventManager eM;

  Event e1 = eM.AddEvent(1, "E0").value();
  Event e2 = eM.AddEvent(3, "E1").value();
  Event e3 = eM.AddEvent(1202, "E2").value();
  Event e4 = eM.AddEvent(3, "E3").value();
  Event e5 = eM.AddEvent(5, "E4").value();

  REQUIRE(eM.getNumEvents() == 5);
  eM.PauseEvent(e1);
  eM.PauseEvent(e3);
  CHECK(eM.ResumeEvent(e1) == true);
  CHECK(eM.getNumPaused() == 1);
  CHECK(eM.ResumeEvent(e3) == true);
  CHECK(eM.getNumPaused() == 0);
  CHECK(eM.ResumeEvent(e2) == true);
  CHECK(eM.getNumPaused() == 0);

}

TEST_CASE("Trigger events", "[EventManager]")
{
  EventManager eM;

  eM.AddEvent(1, "Event 1");
  eM.AddEvent(3, "Event 2");
  eM.AddEvent(5, "Event 3");

  REQUIRE(eM.getNumEvents() == 3);
  eM.StartQueue();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eM.getNumEvents() == 2);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eM.getNumEvents() == 1);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eM.getNumEvents() == 0);
}

TEST_CASE("Trigger Events with Repeat Events", "[EventManager]")
{
  EventManager eM;
  std::optional<Event> e1 = eM.AddEvent(1, "Event 1");
  CHECK(e1.has_value());
  std::optional<Event> e2 = eM.AddEvent(3, "Event 2");
  CHECK(e2.has_value());
  std::optional<Event> e3 = eM.AddEvent(5, "Event 3");
  CHECK(e3.has_value());
  Event e4(4, 10, "Event 4");
  CHECK(eM.RepeatEvent(e1.value(), 4) == true);
  CHECK(eM.RepeatEvent(e4, 10) == false);

  std::cout << "Beginning Trigger Events - Repeat Events Test Case" << std::endl;
  REQUIRE(eM.getNumEvents() == 3);
  eM.StartQueue();
  std::this_thread::sleep_for(std::chrono::seconds(2)); //e1 triggered and readd to queue
  CHECK(eM.getNumEvents() == 3);
  std::this_thread::sleep_for(std::chrono::seconds(2)); //e2 triggered
  CHECK(eM.getNumEvents() == 2);
  std::this_thread::sleep_for(std::chrono::seconds(2)); //e1 and e3 triggered, readd e1
  CHECK(eM.getNumEvents() == 1);
}

TEST_CASE("Trigger Events with Pause/Resume", "[EventManager]")
{
  EventManager eM;

  Event e1 = eM.AddEvent(1, "Event 1").value();
  eM.AddEvent(3, "Event 2");
  eM.AddEvent(5, "Event 3");

  eM.PauseEvent(e1);
  std::cout << "Beginning Trigger Events - Pause/Resume" << std::endl;
  REQUIRE(eM.getNumEvents() == 3);
  eM.StartQueue();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eM.getNumEvents() == 3);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eM.getNumEvents() == 2);
  eM.ResumeEvent(e1);
  std::this_thread::sleep_for(std::chrono::seconds(4));
  CHECK(eM.getNumEvents() == 0);
}



