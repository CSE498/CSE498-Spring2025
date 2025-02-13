/**
* @file AuditedVectorTestRelease.cpp
 * @author Matthew Hawkins
 *
 * In release mode, our audited vector is just an alias for std::vector.
 * Thus, we test its behavior as a normal vector.
 */

#define NDEBUG
#include <cassert>
#include "../../include/third-party/Catch/single_include/catch2/catch.hpp"
#include "../../include/cse/AuditedVector.h"

TEST_CASE("AuditedVector Release: operator[] works like std::vector", "[AuditedVector][release]") {
  cse::AuditedVector<int> vec { 10, 20, 30 };

  SECTION("Valid index access returns the correct elements") {
    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 20);
    REQUIRE(vec[2] == 30);
  }
}

TEST_CASE("AuditedVector Release: front(), back(), and pop_back() work normally", "[AuditedVector][release]") {
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
}

TEST_CASE("AuditedVector Release: behaves like std::vector overall", "[AuditedVector][release]") {
  cse::AuditedVector<int> vec;
  for (int i = 0; i < 5; ++i)
    vec.push_back(i * 10);
  REQUIRE(vec.size() == 5);
  for (int i = 0; i < 5; ++i)
    REQUIRE(vec[i] == i * 10);
}
