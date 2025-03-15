#include "GraphPosition.hpp"

namespace cse {
  GraphPosition::GraphPosition(const Graph &g, Vertex const *startVertex) : graph(g), currentVertex(startVertex) {
    if (!startVertex) {
      throw std::invalid_argument("GraphPosition must be initialized with a non-null vertex!");
    }
  }

  void GraphPosition::MarkVisited(Vertex const &vertex) {
    visitedVertices.insert(vertex.GetId()); // Store the actual vertex object
    traversalPath.push_back(&vertex);
  }

  Vertex const &GraphPosition::GetCurrentVertex() const {
    assert(currentVertex != nullptr && "GetCurrentVertex() should never return nullptr!");
    return *currentVertex;
  }

  void GraphPosition::SetCurrentVertex(Vertex const &vertex) {
    currentVertex = &vertex;
  }

  bool GraphPosition::AdvanceToNextNeighbor() {
    return traversalFunction(*this);
  }

  const std::vector<Vertex const *> &GraphPosition::GetTraversalPath() const {
    return traversalPath;
  }

  void GraphPosition::ResetTraversal(Vertex const &newStartVertex) {
    // Clear traversal history
    visitedVertices.clear();
    traversalPath.clear();

    // Set new starting position
    SetCurrentVertex(newStartVertex);
  }

  GraphPosition &GraphPosition::operator++() {
    if (!AdvanceToNextNeighbor()) {
      // No more nodes to visit
      currentVertex = nullptr;
    }
    return *this;
  }

  GraphPosition::operator bool() const {
    return currentVertex != nullptr;
  }

  namespace TraversalModes {
    auto DFS() -> std::function<bool(GraphPosition &)> {
      return [](GraphPosition &graphPosition) {
        auto dfs_implementation = [&](GraphPosition &gp, auto &dfs) -> bool {
          auto &stack = gp.GetTraversalStack();

          if (stack.empty()) {
            stack.push_back(&gp.GetCurrentVertex());
          }
          cse::Vertex const &current = *stack.back();
          if (gp.IsVisited(current)) {
            return false;
          }

          // Collect and sort neighbors alphabetically by Vertex ID
          std::vector<std::pair<std::string, std::weak_ptr<cse::Edge>>> neighbors(current.GetEdges().begin(),
                                                                                  current.GetEdges().end());
          std::sort(neighbors.begin(), neighbors.end(),
                    [](std::pair<std::string, std::weak_ptr<cse::Edge>> &edge1,
                       std::pair<std::string, std::weak_ptr<cse::Edge>> &edge2) {
                      return edge1.second.lock()->GetTo().GetId() < edge2.second.lock()->GetTo().GetId();
                    });

          // Find the first non visited neighbor and not in the stack
          auto nonVisited = std::find_if(neighbors.begin(), neighbors.end(),
                                         [&](std::pair<std::string, std::weak_ptr<cse::Edge>> &p) {
                                           auto weakEdge = p.second;
                                           if (auto edge = weakEdge.lock()) {
                                             cse::Vertex const &neighbor = edge->GetTo();
                                             return !gp.IsVisited(neighbor);
                                           }
                                           return false;
                                         });

          if (nonVisited == neighbors.end()) {
            stack.pop_back();
            gp.SetCurrentVertex(current);
            gp.MarkVisited(current);
            return true;
          }

          auto &c = (nonVisited->second.lock())->GetTo();
          stack.push_back(&c);
          return dfs(gp, dfs); // Recursive call
        };

        return dfs_implementation(graphPosition, dfs_implementation); // Start DFS from the current position
      };
    };

    auto BFS() -> std::function<bool(GraphPosition &)> {
      return [](GraphPosition &graphPosition) {
        auto &queue = graphPosition.GetTraversalQueue();

        // Initialize queue with start vertex if empty
        if (queue.empty()) {
          queue.push_back(&graphPosition.GetCurrentVertex());
          graphPosition.MarkVisited(graphPosition.GetCurrentVertex());
        }

        // If queue is empty after initialization, traversal is complete
        if (queue.empty()) {
          return false;
        }

        // Get the front vertex from queue
        Vertex const *current = queue.front();
        queue.pop_front();
        graphPosition.SetCurrentVertex(*current);

        // Collect and sort neighbors alphabetically by Vertex ID
        std::vector<std::pair<std::string, std::weak_ptr<Edge>>> neighbors(current->GetEdges().begin(),
                                                                           current->GetEdges().end());
        std::sort(neighbors.begin(), neighbors.end(), [](const auto &edge1, const auto &edge2) {
          return edge1.second.lock()->GetTo().GetId() < edge2.second.lock()->GetTo().GetId();
        });

        // Add unvisited neighbors to queue
        for (const auto &edge : neighbors) {
          if (auto edgePtr = edge.second.lock()) {
            Vertex const &neighbor = edgePtr->GetTo();
            if (!graphPosition.IsVisited(neighbor)) {
              queue.push_back(&neighbor);
              graphPosition.MarkVisited(neighbor);
            }
          }
        }

        return !queue.empty();
      };
    };
  } // namespace TraversalModes

} // namespace cse