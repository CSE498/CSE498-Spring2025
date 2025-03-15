#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include <vector>

TEST_CASE("Test std::vector", "[base]")
{
  std::vector<int> v{0, 1, 2, 3, 4};

  CHECK(v.size() == 5);
}
