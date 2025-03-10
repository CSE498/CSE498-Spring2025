#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../../Group-01/Graph/Vertex.hpp"
#include "../../../Group-01/Graph/Edge.hpp"

#include <vector>
#include <sstream>

using Catch::Matchers::WithinAbs;

TEST_CASE("Test cse::Edge", "[base]")
{
  auto v1 = std::make_shared<cse::Vertex>("id1");
  auto v2 = std::make_shared<cse::Vertex>("id2");

  auto e1 = std::make_shared<cse::Edge>("edge1", v1, v2);
  CHECK(!e1->IsBidirectional());
  CHECK(e1->IsConnected(v1, v2));
  CHECK(!e1->IsConnected(v2, v1));

  std::shared_ptr<cse::Edge> e2 = std::make_shared<cse::BidirectionalEdge>("edge2", v1, v2);
  CHECK(e2->IsBidirectional());
  CHECK(e2->IsConnected(v1, v2));
  CHECK(e2->IsConnected(v2, v1));

  std::shared_ptr<cse::Edge> e3 = std::make_shared<cse::BidirectionalEdge>("edge3", v2, v1);
  CHECK(e3->IsBidirectional());
  CHECK(e3->IsConnected(v1, v2));
  CHECK(e3->IsConnected(v2, v1));
}
