#include "../../../Group-01/GraphPosition/GraphPosition.hpp"

#include <sstream>
#include <vector>

#include "../../../Group-01/Graph/Graph.hpp"
#include "../../../third-party/Catch/single_include/catch2/catch.hpp"

using Catch::Matchers::WithinAbs;

TEST_CASE("GraphPosition Constructor Tests", "[GraphPosition]") {
  cse::Graph graph;

  SECTION("Valid GraphPosition Initialization") {
    auto &v1 = graph.AddVertex("A");
    REQUIRE_NOTHROW(cse::GraphPosition(graph, &v1));
  }

  SECTION("Invalid GraphPosition Initialization with nullptr Vertex") {
    REQUIRE_THROWS_AS(cse::GraphPosition(graph, nullptr),
                      std::invalid_argument);
  }
}

TEST_CASE("GraphPosition Getters and Setters Tests", "[GraphPosition]") {
  cse::Graph graph;
  auto &v1 = graph.AddVertex("A");
  auto &v2 = graph.AddVertex("B");

  cse::GraphPosition pos(graph, &v1);

  SECTION("GetCurrentVertex returns the correct vertex") {
    REQUIRE(pos.GetCurrentVertex() == v1);
  }

  SECTION("SetCurrentVertex updates current vertex") {
    pos.SetCurrentVertex(v2);
    REQUIRE(pos.GetCurrentVertex() == v2);
  }

  SECTION("SetCurrentVertex marks the new vertex as visited") {
    pos.SetCurrentVertex(v2);
    REQUIRE(!pos.IsVisited(pos.GetCurrentVertex()));
  }
}

TEST_CASE("GraphPosition Visited Vertices Tests", "[GraphPosition]") {
  cse::Graph graph;
  auto &v1 = graph.AddVertex("A");
  auto v2 = graph.AddVertex("B");
  graph.AddVertex("C");

  graph.AddEdge("A", "B");
  graph.AddEdge("B", "C");

  cse::GraphPosition pos(graph, &v1);
}

TEST_CASE("GraphPosition Depth-First Search Traversal", "[GraphPosition]") {
  cse::Graph graph;
  auto &v1 = graph.AddVertex("A");
  auto &v2 = graph.AddVertex("B");
  auto &v3 = graph.AddVertex("C");
  auto &v4 = graph.AddVertex("D");

  graph.AddEdge("A", "B");
  graph.AddEdge("A", "C");
  graph.AddEdge("B", "D");

  cse::GraphPosition pos(graph, &v1);

  SECTION("DFS follows deep traversal first") {
    std::vector<cse::Vertex *> order{&v4, &v2, &v3, &v1};
    size_t ind = 0;
    while ((bool)++pos) {
      auto &v = *(order.at(ind));
      CHECK(pos.GetCurrentVertex() == v);
      ind++;
    }
  }

  SECTION("BFS follows breadth traversal first") {
    std::vector<cse::Vertex *> order{&v1, &v2, &v3, &v4};
    pos.SetTraversalMode(cse::TraversalModes::BFS());
    pos.ResetTraversal(v1);
    size_t ind = 0;
    while ((bool)++pos) {
      auto &v = *(order.at(ind));
      CHECK(pos.GetCurrentVertex() == v);
      ind++;
    }
  }
}