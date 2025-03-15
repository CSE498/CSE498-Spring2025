/**
 * @file AuditedArrayTest.cpp
 * @author Siddhartha Bhattacharya
 */
#include "../../Group-07/Team07Library/AuditedArray.h"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#if defined(NDEBUG) || !defined(AUDIT)
template <typename T, size_t N>
using AuditedArray = std::array<T, N>;
#else 


TEST_CASE("AuditedArray Construction", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;
}

TEST_CASE("AuditedArray Copy Construction", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;
  cse::AuditedArray<int, 5> arr2 = arr;
}

TEST_CASE("AuditedArray Size", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;
  REQUIRE(arr.size() == 5);
}

TEST_CASE("AuditedArray Access", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;
  arr[0] = 1;
  REQUIRE(arr[0] == 1);

  // test const access
  arr[3] = 2;
  const int val = arr[3];
  REQUIRE(val == 2);

  // test invalid access throws out_of_range
  REQUIRE_THROWS_AS(arr[5], std::out_of_range);
  REQUIRE_THROWS_AS(arr[-1], std::out_of_range);
}

TEST_CASE("AuditedArray Assignment", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;
  arr[0] = 1;
  cse::AuditedArray<int, 5> arr2 = arr;

  for (int i = 0; i < 5; i++) {
    REQUIRE(arr2[i] == arr[i]);
  }
}

TEST_CASE("AuditedArray Fill", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;
  arr.fill(1);

  for (int i = 0; i < 5; i++) {
    REQUIRE(arr[i] == 1);
  }

  std::string str = "hello";
  cse::AuditedArray<std::string, 5> arr2;
  arr2.fill(str);
  for (int i = 0; i < 5; i++) {
    REQUIRE(arr2[i] == str);
  }
}

TEST_CASE("AuditedArray Contains", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;
  arr.fill(1);
  arr[1] = 3;

  REQUIRE(arr.contains(3));
  REQUIRE_FALSE(arr.contains(2));
}

TEST_CASE("AuditedArray IndexOf", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;
  arr.fill(1);
  arr[1] = 3;

  REQUIRE(arr.indexOf(1) == 0);
  REQUIRE(arr.indexOf(2) == -1);
}

TEST_CASE("AuditedArray isValidIndex", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;

  REQUIRE(arr.isValidIndex(0));
  REQUIRE_FALSE(arr.isValidIndex(-1));
  REQUIRE_FALSE(arr.isValidIndex(5));
}

TEST_CASE("AuditedArray iterator", "[AuditedArray]") {
  cse::AuditedArray<int, 5> arr;
  arr.fill(1);
  int i = 0;
  for (auto it = arr.begin(); it != arr.end(); it++) {
    REQUIRE(*it == 1);
    i++;
  }
  REQUIRE(i == 5);

  // const iterator
  const cse::AuditedArray<int, 5> arr2;
  i = 0;
  for (auto it = arr2.begin(); it != arr2.end(); it++) {
    i++;
  }
  REQUIRE(i == 5);
}

#endif