#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../../Group-01/Graph/Vertex.hpp"
#include "../../../Group-01/Graph/Edge.hpp"
#include "../../../Group-01/Graph/Graph.hpp"

#include <vector>
#include <sstream>

using Catch::Matchers::WithinAbs;

TEST_CASE("Test cse::Graph", "[base]")
{
  cse::Graph graph;

  // Test adding vertices
  auto v1 = graph.AddVertex("id1");
  auto v2 = graph.AddVertex("id2");
  CHECK(graph.GetVertex("id1")->GetId() == "id1");
  CHECK(graph.GetVertex("id2")->GetId() == "id2");

  CHECK_THROWS_AS(graph.AddVertex("id1"), std::runtime_error);

  // Test removing vertices
  graph.RemoveVertex("id1");
  CHECK_THROWS_AS(graph.GetVertex("id1"), std::out_of_range);

  // Test adding edges
  v1 = graph.AddVertex("id1");
  auto e1 = graph.AddEdge("id1", "id2", false);
  {
    auto e1_sh = e1.lock();
    CHECK(e1_sh->IsConnected(v1, v2));
    CHECK(!e1_sh->IsBidirectional());
    CHECK(!e1_sh->IsConnected(v2, v1));
  }
  // Edge should only be owned by graph
  CHECK(e1.use_count() == 1);

  // Testing Adding Edges by reference
  auto v4 = graph.AddVertex("id4");
  auto v5 = graph.AddVertex("id5");
  auto e2 = graph.AddEdge(v4, v5, false);
  // TODO @lspecht: Should check if nodes are connected via Graph Interface
  {
    auto e2_sh = e2.lock();
    CHECK(e2_sh->IsConnected(v4, v5));
    CHECK(!e2_sh->IsBidirectional());
    CHECK(!e2_sh->IsConnected(v5, v4));
  }
  CHECK(e2.use_count() == 1);

  // Testing removing Edges
  auto v4_v5_edge = graph.GetEdge(v4->GetId(), v5->GetId());
  CHECK(!v4_v5_edge.expired());
  graph.RemoveEdge(e2);
  CHECK(v4_v5_edge.expired());
  CHECK_THROWS_AS(graph.GetEdge(v4->GetId(), v5->GetId()), std::runtime_error);
  CHECK_THROWS_AS(graph.RemoveEdge(e2), std::out_of_range);
  CHECK_THROWS_AS(v4->GetEdge(v5), std::runtime_error);

  // Test bidirectional edges
  auto e3 = graph.AddEdge("id1", "id2", true);
  {
    auto e3_sh = e3.lock();
    CHECK(e3_sh->IsConnected(v1, v2));
    CHECK(e3_sh->IsConnected(v2, v1));
    CHECK(e3_sh->IsBidirectional());
  }
}