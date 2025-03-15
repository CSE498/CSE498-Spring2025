/**
* @file AuditedVectorTestDebug.cpp
 * @author Matthew Hawkins
 *
 * Note: In debug mode the audited vector uses assert to check preconditions.
 * Because an assertion failure aborts the program, we only test valid operations here.
 */

#include <catch2/catch.hpp>
#include <cse/AuditedVector.h>

TEST_CASE("AuditedVector Debug: operator[] valid indices", "[AuditedVector][debug]") {
  cse::AuditedVector<int> vec { 10, 20, 30 };

  SECTION("Valid indices return correct values") {
    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 20);
    REQUIRE(vec[2] == 30);
  }

  // Note: Out-of-range access would cause the program to abort.
}

TEST_CASE("AuditedVector Debug: front(), back(), and pop_back() on non-empty vector", "[AuditedVector][debug]") {
  cse::AuditedVector<int> vec { 100, 200, 300 };

  SECTION("front() returns the first element") {
    REQUIRE(vec.front() == 100);
  }

  SECTION("back() returns the last element") {
    REQUIRE(vec.back() == 300);
  }

  SECTION("pop_back() removes the last element") {
    vec.pop_back();
    REQUIRE(vec.size() == 2);
    REQUIRE(vec.back() == 200);
  }

  // Note: Calling front(), back(), or pop_back() on an empty vector would trigger an assertion.
}
