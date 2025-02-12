#include "catch.hpp"

#define _cse_ASSERT_TEST
#include "CseAssert.hpp"

#define REQUIRE_ASSERT(...)                                                    \
  REQUIRE_THROWS_AS(__VA_ARGS__, cse::_assert_internal::AssertTestException)

#define REQUIRE_NOASSERT(...) REQUIRE_NOTHROW(__VA_ARGS__)

TEST_CASE("Test basic assert functionality", "[assert]") {
  // test most basic asserts
  REQUIRE_NOASSERT(cse_assert(true));
  REQUIRE_ASSERT(cse_assert(false));

  // test assert with message
  REQUIRE_NOASSERT(cse_assert(true, "hello world"));
  REQUIRE_ASSERT(cse_assert(false, "hello world"));

  // test asserts with comma in condition
  REQUIRE_NOASSERT(cse_assert(std::is_same_v<int, int>));
  REQUIRE_NOASSERT(cse_assert(std::is_same_v<int, int>, "hello world"));
  REQUIRE_ASSERT(cse_assert(std::is_same_v<int, double>));
  REQUIRE_ASSERT(cse_assert(std::is_same_v<int, double>, "hello world"));
}

TEST_CASE("Test debug asserts", "[assert]") {
#ifndef NDEBUG
  // test debug basic asserts
  REQUIRE_NOASSERT(dbg_assert(true));
  REQUIRE_ASSERT(dbg_assert(false));

  // test debug assert with message
  REQUIRE_NOASSERT(dbg_assert(true, "hello world"));
  REQUIRE_ASSERT(dbg_assert(false, "hello world"));
#else
  // ensure all are no-ops when debug mode is disabled
  REQUIRE_NOASSERT(dbg_assert(true));
  REQUIRE_NOASSERT(dbg_assert(false));
  REQUIRE_NOASSERT(dbg_assert(true, "hello world"));
  REQUIRE_NOASSERT(dbg_assert(false, "hello world"));
#endif
}
