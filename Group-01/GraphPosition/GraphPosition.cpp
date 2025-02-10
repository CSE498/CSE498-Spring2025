#include "GraphPosition.hpp"

namespace cse {

void GraphPosition::MarkVisited(std::shared_ptr<Vertex> vertex) {
    visitedVertices.insert(vertex);  // Store the actual vertex object
    traversalPath.push_back(vertex);
}

GraphPosition::GraphPosition(const Graph& g, std::shared_ptr<Vertex> startVertex)
    : graph(g), currentVertex(startVertex) {
    if (!startVertex) {
        throw std::invalid_argument("Starting vertex is null.");
    }
    MarkVisited(startVertex);
}

std::shared_ptr<Vertex> GraphPosition::GetCurrentVertex() const {
    return currentVertex;
}

void GraphPosition::SetCurrentVertex(std::shared_ptr<Vertex> vertex) {
    if (!vertex) {
        throw std::invalid_argument("Invalid vertex: nullptr received.");
    }
    currentVertex = vertex;
    MarkVisited(currentVertex);
}

bool GraphPosition::AdvanceToNextNeighbor() {
    // Get the current vertex's edges
    for (auto& [neighborID, weakEdge] : currentVertex->GetEdges()) {
        if (auto edge = weakEdge.lock()) { // Lock weak_ptr to access Edge
            std::shared_ptr<Vertex> neighbor = (edge->GetFrom() == currentVertex) ? edge->GetTo() : edge->GetFrom();

            // If neighbor has not been visited, move to it
            if (visitedVertices.find(neighbor) == visitedVertices.end()) {
                currentVertex = neighbor;
                MarkVisited(currentVertex);
                return true;
            }
        }
    }

    // No unvisited neighbors found
    return false;
}

const std::vector<std::shared_ptr<Vertex>>& GraphPosition::GetTraversalPath() const {
    return traversalPath;
}

} // namespace cse