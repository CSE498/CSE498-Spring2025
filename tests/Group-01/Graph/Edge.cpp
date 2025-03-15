#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../../Group-01/Graph/Vertex.hpp"
#include "../../../Group-01/Graph/Edge.hpp"
#include "../Utils/TestUtils.hpp"

#include <vector>
#include <sstream>

using Catch::Matchers::WithinAbs;

TEST_CASE("Test cse::Edge", "[base]")
{
  auto v1 = std::make_shared<cse::Vertex>("id1");
  auto v2 = std::make_shared<cse::Vertex>("id2");

  auto e1 = std::make_shared<cse::Edge>("edge1", v1, v2);
  CHECK(e1->IsConnected(*v1, *v2));
  CHECK(!e1->IsConnected(*v2, *v1));
  REQUIRE_THAT(e1->GetWeight(), WithinAbs(0, cse_test_utils::FLOAT_DELTA));
}
