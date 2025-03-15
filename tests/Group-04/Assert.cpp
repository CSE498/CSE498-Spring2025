#include "catch.hpp"

#define TEST_CSE_ASSERT
#include "CseAssert.hpp"

TEST_CASE("Test basic assert functionality", "[assert]") {
  // test most basic asserts
  REQUIRE_NOASSERT(cse_assert(true));
  REQUIRE_ASSERT(cse_assert(false));

  // test assert with message
  REQUIRE_NOASSERT(cse_assert(true, "hello world"));
  REQUIRE_ASSERT(cse_assert(false, "hello world"));

  // test asserts with comma in condition
}

TEST_CASE("Test argument splitting", "[assert]") {
  REQUIRE_NOASSERT(cse_assert(std::is_same_v<int, int>));
  REQUIRE_NOASSERT(cse_assert(std::is_same_v<int, int>, "hello, world!"));
  REQUIRE_ASSERT(cse_assert(std::is_same_v<int, double>));
  REQUIRE_ASSERT(cse_assert(std::is_same_v<int, double>, "hello, world!"));

  REQUIRE_ASSERT(cse_assert_eq(std::is_same_v<int, int>,
                               std::is_same_v<bool, int>, "hello, world!"));
  REQUIRE_NOASSERT(
      cse_assert_neq(std::is_same_v<int, int>, std::is_same_v<bool, int>),
      "hello, world!");

  REQUIRE_ASSERT(
      cse_assert_neq(std::is_same_v<int, int>, std::is_same_v<int, int>));
  REQUIRE_NOASSERT(
      cse_assert_eq(std::is_same_v<int, int>, std::is_same_v<int, int>));

  // stress test
  REQUIRE_NOASSERT(cse_assert(
      std::is_same_v<
          std::tuple_element_t<2, std::tuple<int, bool, double, float>>,
          double>,
      "hello, world!"));
  REQUIRE_ASSERT(cse_assert(
      std::is_same_v<
          std::tuple_element_t<3, std::tuple<int, bool, double, float>>,
          double>,
      "hello, world!"));
}

TEST_CASE("Test assert never", "[assert]") {
  REQUIRE_ASSERT(cse_assert_never());
  REQUIRE_ASSERT(cse_assert_never("hello world"));
}

TEST_CASE("Test assert equal", "[assert]") {
  // basic assert_eq (printable)
  REQUIRE_ASSERT(cse_assert_eq(1, 2));
  REQUIRE_NOASSERT(cse_assert_eq(1, 1));

  // basic assert_eq (non-printable)
  REQUIRE_ASSERT(cse_assert_eq(std::vector<int>{0}, std::vector<int>{1}));
  REQUIRE_NOASSERT(cse_assert_eq(std::vector<int>{0}, std::vector<int>{0}));
}

TEST_CASE("Test assert not equal", "[assert]") {
  // basic assert_eq (printable)
  REQUIRE_ASSERT(cse_assert_neq(1, 1));
  REQUIRE_NOASSERT(cse_assert_neq(1, 2));

  // basic assert_eq (non-printable)
  REQUIRE_ASSERT(cse_assert_neq(std::vector<int>{0}, std::vector<int>{0}));
  REQUIRE_NOASSERT(cse_assert_neq(std::vector<int>{0}, std::vector<int>{1}));
}

TEST_CASE("Test asserts with side effects", "[assert]") {
  int i = 0;
  REQUIRE_NOASSERT(cse_assert(i++ == 0));
  REQUIRE(i == 1);

  int j = 0;
  REQUIRE_ASSERT(cse_assert_eq(i++, j++));
  REQUIRE_NOASSERT(cse_assert_eq(i++, (j++) + 1));
  REQUIRE(i == 3);
  REQUIRE(j == 2);

  REQUIRE_NOASSERT(cse_assert_neq(++i, ++j));
  REQUIRE(i == 4);
  REQUIRE(j == 3);
}

TEST_CASE("Test debug asserts", "[assert]") {
#ifndef NDEBUG
  // test debug basic asserts
  REQUIRE_NOASSERT(dbg_assert(true));
  REQUIRE_ASSERT(dbg_assert(false));

  // test debug assert with message
  REQUIRE_NOASSERT(dbg_assert(true, "hello world"));
  REQUIRE_ASSERT(dbg_assert(false, "hello world"));

  // test assert eq and neq
  REQUIRE_ASSERT(cse_assert_eq(1, 2));
  REQUIRE_NOASSERT(cse_assert_eq(1, 1));
  REQUIRE_ASSERT(cse_assert_neq(1, 1));
  REQUIRE_NOASSERT(cse_assert_neq(1, 2));
#else
  // ensure all are no-ops when debug mode is disabled
  REQUIRE_NOASSERT(dbg_assert(true));
  REQUIRE_NOASSERT(dbg_assert(false));
  REQUIRE_NOASSERT(dbg_assert(true, "hello world"));
  REQUIRE_NOASSERT(dbg_assert(false, "hello world"));
  REQUIRE_NOASSERT(cse_assert_eq(1, 2));
  REQUIRE_NOASSERT(cse_assert_eq(1, 1));
  REQUIRE_NOASSERT(cse_assert_neq(1, 1));
  REQUIRE_NOASSERT(cse_assert_neq(1, 2));
#endif
}
