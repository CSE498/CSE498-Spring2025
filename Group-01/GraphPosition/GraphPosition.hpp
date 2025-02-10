#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <stdexcept>
#include "../Graph/Graph.hpp"

// Forward declaration of Graph. 
// Likely will have functions like GetNeighbors, HasVertex (bool if vertex exists in graph), GetModificationCount (provides
// count of # times graph has been modified so GraphPosition can use to detect changes during 
// traversal), and more. Also assumes Graph class initializes vertices with an ID for easy tracking/position usage.

namespace cse {

class GraphPosition {
    private:
    const Graph& graph;
    std::shared_ptr<Vertex> currentVertex;
    std::set<std::shared_ptr<Vertex>> visitedVertices;
    std::vector<std::shared_ptr<Vertex>> traversalPath;

    void MarkVisited(std::shared_ptr<Vertex> vertex);


public:
    GraphPosition(const Graph& g, std::shared_ptr<Vertex> startVertex);

    std::shared_ptr<Vertex> GetCurrentVertex() const;
    void SetCurrentVertex(std::shared_ptr<Vertex> vertex);
    bool AdvanceToNextNeighbor();
    const std::vector<std::shared_ptr<Vertex>>& GetTraversalPath() const;
};

} // namespace cse