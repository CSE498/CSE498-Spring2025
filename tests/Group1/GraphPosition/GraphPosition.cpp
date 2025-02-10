#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../../Group-01/GraphPosition/GraphPosition.hpp"
#include "../../../Group-01/Graph/Graph.hpp"

#include <vector>
#include <sstream>

using Catch::Matchers::WithinAbs;


TEST_CASE("GraphPosition Constructor Tests", "[GraphPosition]") {
    cse::Graph graph;

    SECTION("Valid GraphPosition Initialization") {
        auto v1 = graph.AddVertex("A");
        REQUIRE_NOTHROW(cse::GraphPosition(graph, v1));
    }

    SECTION("Invalid GraphPosition Initialization with nullptr Vertex") {
        REQUIRE_THROWS_AS(cse::GraphPosition(graph, nullptr), std::invalid_argument);
    }
}

TEST_CASE("GraphPosition Getters and Setters Tests", "[GraphPosition]") {
    cse::Graph graph;
    auto v1 = graph.AddVertex("A");
    auto v2 = graph.AddVertex("B");

    cse::GraphPosition pos(graph, v1);

    SECTION("GetCurrentVertex returns the correct vertex") {
        REQUIRE(pos.GetCurrentVertex() == v1);
    }

    SECTION("SetCurrentVertex updates current vertex") {
        pos.SetCurrentVertex(v2);
        REQUIRE(pos.GetCurrentVertex() == v2);
    }

    SECTION("SetCurrentVertex marks the new vertex as visited") {
        pos.SetCurrentVertex(v2);
        REQUIRE(pos.GetTraversalPath().back() == v2);
    }
}

TEST_CASE("GraphPosition Traversal Tests", "[GraphPosition]") {
    cse::Graph graph;
    auto v1 = graph.AddVertex("A");
    auto v2 = graph.AddVertex("B");
    auto v3 = graph.AddVertex("C");

    graph.AddEdge("A", "B");
    graph.AddEdge("B", "C");

    cse::GraphPosition pos(graph, v1);

    SECTION("AdvanceToNextNeighbor moves to unvisited neighbor") {
        REQUIRE(pos.AdvanceToNextNeighbor());
        REQUIRE(pos.GetCurrentVertex() == v2);
    }

    SECTION("AdvanceToNextNeighbor stops when no unvisited neighbors exist") {
        pos.AdvanceToNextNeighbor();
        pos.AdvanceToNextNeighbor();
        REQUIRE_FALSE(pos.AdvanceToNextNeighbor());
    }
}

TEST_CASE("GraphPosition Visited Vertices Tests", "[GraphPosition]") {
    cse::Graph graph;
    auto v1 = graph.AddVertex("A");
    auto v2 = graph.AddVertex("B");
    auto v3 = graph.AddVertex("C");

    graph.AddEdge("A", "B");
    graph.AddEdge("B", "C");

    cse::GraphPosition pos(graph, v1);

    SECTION("GraphPosition tracks visited vertices correctly") {
        pos.AdvanceToNextNeighbor();
        REQUIRE(pos.GetTraversalPath().size() == 2);
        REQUIRE(pos.GetTraversalPath().at(0) == v1);
        REQUIRE(pos.GetTraversalPath().at(1) == v2);
    }

    SECTION("GraphPosition does not revisit previously visited vertices") {
        pos.AdvanceToNextNeighbor();
        pos.AdvanceToNextNeighbor();
        REQUIRE_FALSE(pos.AdvanceToNextNeighbor()); // No more new neighbors
    }
}

TEST_CASE("GraphPosition Traversal Path Tests", "[GraphPosition]") {
    cse::Graph graph;
    auto v1 = graph.AddVertex("A");
    auto v2 = graph.AddVertex("B");
    auto v3 = graph.AddVertex("C");
    auto v4 = graph.AddVertex("D");

    graph.AddEdge("A", "B");
    graph.AddEdge("B", "C");
    graph.AddEdge("C", "D");

    cse::GraphPosition pos(graph, v1);

    SECTION("Traversal path is correct") {
        pos.AdvanceToNextNeighbor(); // Move to B
        pos.AdvanceToNextNeighbor(); // Move to C
        pos.AdvanceToNextNeighbor(); // Move to D

        std::vector<std::shared_ptr<cse::Vertex>> expectedPath = {v1, v2, v3, v4};
        REQUIRE(pos.GetTraversalPath() == expectedPath);
    }
}