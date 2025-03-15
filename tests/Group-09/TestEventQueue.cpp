/**
 * @file TestEventQueue.cpp
 *
 * @author Owen Haiar
 */

#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-09/EventQueue/EventQueue.cpp"

using namespace cse;

/**
 * @brief Assert the queue is empty upon creation
 */
TEST_CASE("Test EventQueue", "[base]")
{
  EventQueue eq;
  CHECK(eq.size() == 0);
}

/**
 * @brief Assert adding an event to the queue increments the size and adds to the heap
 */
TEST_CASE("Test EventQueue Add", "[base]")
{
  EventQueue eq;
  Event e1(0, 1, "data");
  Event e2(1, 2, "data");
  eq.add(e1);
  eq.add(e2);
  CHECK(eq.peek() == e1);
  CHECK(eq.size() == 2);
}

/**
 * @brief Assert adding an event with the same ID as an existing event throws an exception.
 */
TEST_CASE("Test EventQueue Add Duplicate ID", "[base]")
{
  EventQueue eq;
  Event e1(0, 1, "data");
  eq.add(e1);
  REQUIRE_THROWS(eq.add(e1));
}

/**
 * @brief Assert peeking at the queue returns the event at the top of the heap
 */
TEST_CASE("Test EventQueue Peek", "[base]")
{
  EventQueue eq;
  Event e1(0, 0, "data");
  Event e2(1, 1, "data");
  Event e3(3, 3, "data");
  Event e4(4, 4, "data");
  eq.add(e1);
  eq.add(e2);
  eq.add(e3);
  eq.add(e4);
  CHECK(eq.peek() == e1);
}

/**
 * @brief Assert popping an event from the queue decrements the size and removes the event from the heap
 */
TEST_CASE("Test EventQueue Pop", "[base]")
{
  EventQueue eq;
  Event e1(0, 0, "data");
  Event e2(1, 1, "data");
  Event e3(3, 3, "data");
  Event e4(4, 4, "data");
  eq.add(e1);
  eq.add(e2);
  eq.add(e3);
  eq.add(e4);
  CHECK(eq.pop() == e1);
  CHECK(eq.pop() == e2);
  CHECK(eq.size() == 2);
  CHECK(eq.pop() == e3);
  CHECK(eq.pop() == e4);
  CHECK(eq.size() == 0);
}

/**
 * @brief Assert removing an event from the queue decrements the size and removes the event from the heap
 */
TEST_CASE("Test EventQueue Valid Remove", "[base]")
{
  EventQueue eq;
  Event e1(0, 0, "data");
  Event e2(1, 1, "data");
  Event e3(3, 3, "data");
  Event e4(4, 4, "data");
  eq.add(e1);
  eq.add(e2);
  eq.add(e3);
  eq.add(e4);
  eq.remove(e3);
  CHECK(eq.size() == 3);
  CHECK(eq.pop() == e1);
  CHECK(eq.pop() == e2);
  CHECK(eq.pop() == e4);
  CHECK(eq.size() == 0);
}

/**
 * @brief Assert removing an event that does not exist in the queue does not change the queue
 */
TEST_CASE("Test EventQueue Invalid Remove", "[base]")
{
  EventQueue eq;
  Event e1(0, 0, "data");
  Event e2(1, 1, "data");
  Event e3(3, 3, "data");
  Event e4(4, 4, "data");
  eq.add(e1);
  eq.add(e2);
  eq.add(e3);
  eq.add(e4);
  auto remove = eq.remove(e3);
  CHECK(remove.has_value());
  remove = eq.remove(e3);
  CHECK(!remove.has_value());
}

/**
 * @brief Assert updating an event in the queue updates the event's time and maintains the heap
 */
TEST_CASE("Test EventQueue Valid Update", "[base]")
{
  EventQueue eq;
  Event e1(0, 0, "data");
  Event e2(1, 1, "data");
  Event e3(3, 3, "data");
  Event e4(4, 4, "data");
  Event e1_updated(0, 100, "data");
  eq.add(e1);
  eq.add(e2);
  eq.add(e3);
  eq.add(e4);
  eq.update(e1_updated);
  CHECK(eq.size() == 4);
  CHECK(eq.pop() == e2);
  CHECK(eq.pop() == e3);
  CHECK(eq.pop() == e4);
  CHECK(eq.peek() == e1);
  CHECK(eq.pop().getTime() == 100);
}

/**
 * @brief Assert updating an event that does not exist in the queue throws an exception
 */
TEST_CASE("Test EventQueue Invalid Update", "[base]")
{
  EventQueue eq;
  Event e2(1, 1, "data");
  Event e3(3, 3, "data");
  Event e4(4, 4, "data");
  Event e1_updated(0, 100, "data");
  eq.add(e2);
  eq.add(e3);
  eq.add(e4);
  REQUIRE_THROWS(eq.update(e1_updated));
}
