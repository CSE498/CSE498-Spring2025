#include <string>

#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../InClass/Group-00/Any.hpp"

TEST_CASE("Test cse::Any", "[base]")
{
  cse::Any any1(100);
  std::string str("abcd");
  cse::Any any2(str);

  CHECK(any1.Get<int>() == 100);
  CHECK(any2.Get<std::string>() == "abcd");

  CHECK(any1.Is<int>() == true);
  CHECK(any1.Is<bool>() == false);

  any2 = 3.141592653589793238;
  CHECK(any2.Get<double>() == 3.141592653589793238);

  any2 = std::move(any1);
  CHECK(any2.Get<int>() == 100);

  CHECK(any2.AsString() == "100");
}