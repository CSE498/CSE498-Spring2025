/**
 * @file TestEventQueue.cpp
 *
 * @author Owen Haiar
 */

#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-09/EventQueue/EventQueue.cpp"

using namespace cse;

TEST_CASE("Test EventQueue", "[base]")
{
  EventQueue eq;
  CHECK(eq.size() == 0);
}

TEST_CASE("Test EventQueue Add", "[base]")
{
  EventQueue eq;
  Event e1(0, 1, "data");
  Event e2(1, 2, "data");
  eq.add(e1);
  eq.add(e2);
  CHECK(eq.size() == 2);
}

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
