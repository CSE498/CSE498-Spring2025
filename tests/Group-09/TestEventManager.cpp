/**
 * @file TestEventManager.cpp
 * @author Grace Fitzgerald
 */

#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-09/EventManager/EventManager.cpp"
#include "../../Group-09/EventQueue/EventQueue.cpp"

using namespace cse;

TEST_CASE("Check empty EventManager", "[EventManager]")
{
  EventManager eventManager;
  CHECK(eventManager.getNumEvents() == 0);
  CHECK(eventManager.getNumPaused()== 0);
  CHECK(eventManager.getTime()== 0);
}

TEST_CASE("Add event to EventManager", "[EventManager]")
{
  EventManager eventManager;

  Event e1(0, 1, "Event 1");
  CHECK(eventManager.AddEvent(1, "Event 1").value() == e1);
  CHECK(eventManager.getNumEvents() == 1);

  Event e2(1, 3, "Event 2!");
  CHECK(eventManager.AddEvent(3, "Event 2!").value() == e2);
  CHECK(eventManager.getNumEvents() == 2);

  Event e3(2, 3, "Event 3\n");
  CHECK(eventManager.AddEvent(3, "Event 3\n").value() == e3);
  CHECK(eventManager.getNumEvents() == 3);
}

TEST_CASE("Pause EventManager event - valid", "[EventManager]")
{
  EventManager eventManager;

  Event e1 = eventManager.AddEvent(1, "Event 1").value();
  Event e2 = eventManager.AddEvent(3, "Event 2!").value();
  Event e3 = eventManager.AddEvent(3, "Event 3\n").value();
  Event e4 = eventManager.AddEvent(3, "_Event_4_").value();

  REQUIRE(eventManager.getNumEvents() == 4);
  CHECK(eventManager.PauseEvent(e1) == true);
  CHECK(eventManager.getNumPaused() == 1); //Add to event manager
  CHECK(eventManager.PauseEvent(e3) == true);
  CHECK(eventManager.getNumPaused() == 2);

}

TEST_CASE("Resume EventManager event", "[EventManager]")
{
  EventManager eventManager;

  Event e1 = eventManager.AddEvent(1, "E0").value();
  Event e2 = eventManager.AddEvent(3, "E1").value();
  Event e3 = eventManager.AddEvent(1202, "E2").value();
  Event e4 = eventManager.AddEvent(3, "E3").value();
  Event e5 = eventManager.AddEvent(5, "E4").value();

  REQUIRE(eventManager.getNumEvents() == 5);
  eventManager.PauseEvent(e1);
  eventManager.PauseEvent(e3);
  CHECK(eventManager.ResumeEvent(e1) == true);
  CHECK(eventManager.getNumPaused() == 1);
  CHECK(eventManager.ResumeEvent(e3) == true);
  CHECK(eventManager.getNumPaused() == 0);
  CHECK(eventManager.ResumeEvent(e2) == true);
  CHECK(eventManager.getNumPaused() == 0);

}

TEST_CASE("Trigger events", "[EventManager]")
{
  EventManager eventManager;

  eventManager.AddEvent(1, "Event 1");
  eventManager.AddEvent(3, "Event 2");
  eventManager.AddEvent(5, "Event 3");

  REQUIRE(eventManager.getNumEvents() == 3);
  eventManager.StartQueue();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eventManager.getNumEvents() == 2);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eventManager.getNumEvents() == 1);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eventManager.getNumEvents() == 0);
}

TEST_CASE("Trigger Events with Repeat Events", "[EventManager]")
{
  EventManager eventManager;
  std::optional<Event> e1 = eventManager.AddEvent(1, "Event 1");
  CHECK(e1.has_value());
  std::optional<Event> e2 = eventManager.AddEvent(3, "Event 2");
  CHECK(e2.has_value());
  std::optional<Event> e3 = eventManager.AddEvent(5, "Event 3");
  CHECK(e3.has_value());
  Event e4(4, 10, "Event 4");
  CHECK(eventManager.RepeatEvent(e1.value(), 3) == true);
  CHECK(eventManager.RepeatEvent(e1.value(), 4) == true);
  CHECK(eventManager.RepeatEvent(e4, 10) == false);

  std::cout << "Beginning Trigger Events - Repeat Events Test Case" << std::endl;
  REQUIRE(eventManager.getNumEvents() == 3);
  eventManager.StartQueue();
  std::this_thread::sleep_for(std::chrono::seconds(2)); //e1 triggered and readd to queue
  CHECK(eventManager.getNumEvents() == 3);
  std::this_thread::sleep_for(std::chrono::seconds(2)); //e2 triggered
  CHECK(eventManager.getNumEvents() == 2);
  std::this_thread::sleep_for(std::chrono::seconds(2)); //e1 and e3 triggered, readd e1
  CHECK(eventManager.getNumEvents() == 1);
}

TEST_CASE("Trigger Events with Pause/Resume", "[EventManager]")
{
  EventManager eventManager;

  Event e1 = eventManager.AddEvent(1, "Event 1").value();
  eventManager.AddEvent(3, "Event 2");
  eventManager.AddEvent(5, "Event 3");

  eventManager.PauseEvent(e1);
  std::cout << "Beginning Trigger Events - Pause/Resume" << std::endl;
  REQUIRE(eventManager.getNumEvents() == 3);
  eventManager.StartQueue();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eventManager.getNumEvents() == 3);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  CHECK(eventManager.getNumEvents() == 2);
  eventManager.ResumeEvent(e1);
  std::this_thread::sleep_for(std::chrono::seconds(4));
  CHECK(eventManager.getNumEvents() == 0);
}



