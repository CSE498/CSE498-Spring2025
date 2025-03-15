#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include <vector>



TEST_CASE("Test std::vector", "[base]")
{
  std::vector<int> v{0, 1, 2, 3, 4};

  REQUIRE(v.size() == 5);
  CHECK(v[2] == 2);
  CHECK(v[3] == 3);
}
