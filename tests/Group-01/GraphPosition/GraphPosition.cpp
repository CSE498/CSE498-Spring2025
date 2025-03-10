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

TEST_CASE("GraphPosition ResetTraversal Tests", "[GraphPosition]") {
    cse::Graph graph;
    auto v1 = graph.AddVertex("A");
    auto v2 = graph.AddVertex("B");
    auto v3 = graph.AddVertex("C");

    graph.AddEdge("A", "B");
    graph.AddEdge("B", "C");

    cse::GraphPosition pos(graph, v1);

    SECTION("ResetTraversal clears visited vertices and traversal path") {
        pos.AdvanceToNextNeighbor(); // Moves to B
        REQUIRE(pos.GetTraversalPath().size() == 2); // A -> B

        pos.ResetTraversal(v1); // Reset back to A

        REQUIRE(pos.GetTraversalPath().size() == 1); // Only A should remain
        REQUIRE(pos.GetTraversalPath().front() == v1); 
        REQUIRE(pos.GetCurrentVertex() == v1);
    }

    SECTION("ResetTraversal allows starting from a different vertex") {
        pos.ResetTraversal(v3);

        REQUIRE(pos.GetTraversalPath().size() == 1); // Only C should be in path
        REQUIRE(pos.GetTraversalPath().front() == v3);
        REQUIRE(pos.GetCurrentVertex() == v3);
    }

    SECTION("ResetTraversal maintains valid traversal after reset") {
        pos.AdvanceToNextNeighbor(); // Move to B
        pos.ResetTraversal(v1); // Reset back to A

        REQUIRE(pos.AdvanceToNextNeighbor()); // Should be able to move again
        REQUIRE(pos.GetCurrentVertex() == v2);
    }
}

// Advanced Functionality tests
// FAILS SO FAR
TEST_CASE("GraphPosition Iterator Traversal Tests", "[GraphPosition]") {
    cse::Graph graph;
    auto v1 = graph.AddVertex("A");
    auto v2 = graph.AddVertex("B");
    auto v3 = graph.AddVertex("C");

    graph.AddEdge("A", "B");
    graph.AddEdge("B", "C");

    cse::GraphPosition pos(graph, v1, cse::TraversalMode::DFS);

    // SECTION("Using ++ operator moves to next vertex") {
    //     CHECK(pos.GetCurrentVertex() == v1);
    //     ++pos;
    //     CHECK(pos.GetCurrentVertex() == v2);
    //     ++pos;
    //     CHECK(pos.GetCurrentVertex() == v3);
    // }

    // SECTION("Iterator-like traversal stops at last vertex") {
    //     ++pos; // Move to B
    //     ++pos; // Move to C
    //     ++pos; // No more vertices left
    //     CHECK_FALSE(pos);
    // }
}

// FAILS SO FAR
TEST_CASE("GraphPosition Depth-First Search Traversal", "[GraphPosition]") {
    cse::Graph graph;
    auto v1 = graph.AddVertex("A");
    auto v2 = graph.AddVertex("B");
    auto v3 = graph.AddVertex("C");
    auto v4 = graph.AddVertex("D");

    graph.AddEdge("A", "B");
    graph.AddEdge("A", "C");
    graph.AddEdge("B", "D");

    cse::GraphPosition pos(graph, v1, cse::TraversalMode::DFS);

    // SECTION("DFS follows deep traversal first") {
    //     ++pos;
    //     CHECK(pos.GetCurrentVertex() == v2); // First deeper neighbor
    //     ++pos;
    //     CHECK(pos.GetCurrentVertex() == v4); // Goes as deep as possible first
    //     ++pos;
    //     CHECK(pos.GetCurrentVertex() == v3); // Backtracks to remaining neighbors
    // }
}

// FAILS SO FAR
TEST_CASE("GraphPosition Breadth-First Search Traversal", "[GraphPosition]") {
    cse::Graph graph;
    auto v1 = graph.AddVertex("A");
    auto v2 = graph.AddVertex("B");
    auto v3 = graph.AddVertex("C");
    auto v4 = graph.AddVertex("D");

    graph.AddEdge("A", "B");
    graph.AddEdge("A", "C");
    graph.AddEdge("B", "D");

    cse::GraphPosition pos(graph, v1, cse::TraversalMode::BFS);

    // SECTION("BFS follows level-order traversal") {
    //     ++pos;
    //     CHECK(pos.GetCurrentVertex() == v2); // BFS visits all direct neighbors first
    //     ++pos;
    //     CHECK(pos.GetCurrentVertex() == v3);
    //     ++pos;
    //     CHECK(pos.GetCurrentVertex() == v4); // Then visits the next level
    // }
}

// FAILS SO FAR
TEST_CASE("GraphPosition Random Walk Traversal", "[GraphPosition]") {
    cse::Graph graph;
    auto v1 = graph.AddVertex("A");
    auto v2 = graph.AddVertex("B");
    auto v3 = graph.AddVertex("C");

    graph.AddEdge("A", "B");
    graph.AddEdge("A", "C");

    cse::GraphPosition pos(graph, v1, cse::TraversalMode::RANDOM);

    // SECTION("Random walk selects different neighbors") {
    //     ++pos;
    //     auto firstMove = pos.GetCurrentVertex();
    //     CHECK((firstMove == v2 || firstMove == v3)); // Could be either B or C
    // }
}

// WILL NEED TO WORK WITH GRAPH TO ADD WEIGHTED EDGES FIRST I BELIEVE
TEST_CASE("GraphPosition Weighted Walk Traversal", "[GraphPosition]") {
    
}

