#pragma once

#include "../Graph/Graph.hpp"
#include "../Graph/Vertex.hpp"

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <set>
#include <stdexcept>
#include <unordered_set>
#include <vector>

namespace cse {

  class GraphPosition; // Forward declaration

  namespace TraversalModes {
    auto DFS() -> std::function<bool(GraphPosition &)>; // Forward declare the function
    auto BFS() -> std::function<bool(GraphPosition &)>; // Forward declare the function
  } // namespace TraversalModes

  class GraphPosition {
  private:
    [[maybe_unused]] const Graph &graph;
    Vertex const *currentVertex;
    // Set of strings of visited vertices by ID
    std::set<std::string> visitedVertices;
    std::vector<Vertex const *> traversalPath;
    std::function<bool(GraphPosition &)> traversalFunction = TraversalModes::DFS();
    std::deque<Vertex const *> traversalQueue;
    std::vector<Vertex const *> traversalStack;

  public:
    std::vector<Vertex const *> &GetTraversalStack() { return traversalStack; }
    std::deque<Vertex const *> &GetTraversalQueue() { return traversalQueue; }
    void MarkVisited(Vertex const &vertex);
    bool IsVisited(Vertex const &vertex) { return visitedVertices.find(vertex.GetId()) != visitedVertices.end(); };
    GraphPosition(const Graph &g, Vertex const *startVertex);

    Vertex const &GetCurrentVertex() const;
    void SetCurrentVertex(Vertex const &vertex);
    bool AdvanceToNextNeighbor();
    const std::vector<Vertex const *> &GetTraversalPath() const;
    void ResetTraversal(Vertex const &newStartVertex);
    GraphPosition &operator++();    // Advances to next vertex
    explicit operator bool() const; // Checks if more traversal is possible
    void SetTraversalMode(std::function<bool(GraphPosition &)> newTraversalFunction) {
      traversalFunction = newTraversalFunction;
    }
  };

} // namespace cse