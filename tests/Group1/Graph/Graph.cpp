#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../../Group-01/Graph/Vertex.hpp"
#include "../../../Group-01/Graph/Edge.hpp"
#include "../../../Group-01/Graph/Graph.hpp"
#include "../Utils/TestUtils.hpp"

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
  CHECK(graph.IsConnected(v1, v2));
  CHECK(!graph.IsConnected(v2, v1));
  CHECK(graph.IsConnected("id1", "id2"));
  CHECK(!graph.IsConnected("id2", "id1"));
  {
    auto e1_sh = e1.lock();
    CHECK(!e1_sh->IsBidirectional());
  }
  // Edge should only be owned by graph
  CHECK(e1.use_count() == 1);

  // Testing Adding Edges by reference
  auto v4 = graph.AddVertex("id4");
  auto v5 = graph.AddVertex("id5");
  CHECK(!graph.IsConnected(v1, v4));
  CHECK(!graph.IsConnected(v4, v5));
  CHECK(!graph.IsConnected(v4, v4));

  auto e2 = graph.AddEdge(v4, v5, false);
  // TODO @lspecht: Should check if nodes are connected via Graph Interface
  CHECK(graph.IsConnected(v4, v5));
  CHECK(!graph.IsConnected(v5, v4));
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

  CHECK(graph.IsConnected(v1, v2));
  CHECK(graph.IsConnected(v2, v1));
  {
    auto e3_sh = e3.lock();
    CHECK(e3_sh->IsBidirectional());
  }
  auto e4 = graph.AddEdge("id1", "id2", true);
}

TEST_CASE("Test cse::Graph - To file", "Export to file")
{
  cse::Graph graph;

  // Test adding vertices
  auto v1 = graph.AddVertex("id1");
  auto v2 = graph.AddVertex("id2", 1.5);
  std::stringstream s;

  graph.ToFile(s);

  std::vector<std::string> lines{"GRAPH:",
                                 "  Vertices:",
                                 "    VERTEX:id2",
                                 "      X:1.5",
                                 "      Y:0",
                                 "    VERTEX:id1",
                                 "      X:0",
                                 "      Y:0",
                                 ""};
  REQUIRE(cse_test_utils::CheckForStringFile(lines, s));
}

TEST_CASE("Test cse::Graph - From file", "Read from file")
{
  std::vector<std::string> lines{"GRAPH:",
                                 "  Vertices:",
                                 "    VERTEX:id2",
                                 "      X:1.5",
                                 "      Y:0",
                                 "    VERTEX:id1",
                                 "      X:1",
                                 "      Y:1",
                                 ""};
  std::stringstream s;
  cse_test_utils::BuildFileFromVector(lines, s);

  cse::Graph graph(s);
  CHECK(graph.GetVertex("id1")->GetId() == "id1");
  REQUIRE_THAT(graph.GetVertex("id1")->GetX(), WithinAbs(1, cse_test_utils::FLOAT_DELTA));
  REQUIRE_THAT(graph.GetVertex("id1")->GetY(), WithinAbs(1, cse_test_utils::FLOAT_DELTA));
  REQUIRE_THAT(graph.GetVertex("id2")->GetX(), WithinAbs(1.5, cse_test_utils::FLOAT_DELTA));
  REQUIRE_THAT(graph.GetVertex("id2")->GetY(), WithinAbs(0, cse_test_utils::FLOAT_DELTA));
  CHECK(graph.GetVertex("id2")->GetId() == "id2");
}
