#include "Vertex.hpp"

#include "Edge.hpp"
#include <cassert>
#include <iostream>

namespace cse {
  void cse::Vertex::AddEdge(std::shared_ptr<Edge> const &e, cse::Vertex const &destination) {
    // assert(e->IsConnected(*this, destination));
    // TODO @lspecht: Should we include a check if the edge already exist?
    this->edges[destination.GetId()] = e;
  }

  void cse::Vertex::AddEdge(std::shared_ptr<Edge> const &e) {
    auto &origin = e->GetFrom();
    auto &destination = e->GetTo();
    AddEdge(e, destination);
    if (e->IsBidirectional() && !(destination.IsConnected(origin))) {
      destination.AddEdge(e, origin);
    }
  }

  // TODO @lspecht: Move expiration logic to a single function
  bool cse::Vertex::IsConnected(cse::Vertex const &destination) {
    auto it = edges.find(destination.GetId());
    if (it == edges.end()) {
      return false;
    }

    if (it->second.expired()) {
      // Edge is not valid anymore
      edges.erase(it);
      return false;
    }
    return true;
  }

  cse::Edge const &cse::Vertex::GetEdge(Vertex const &to) {
    auto e = edges.at(to.GetId());
    if (e.expired()) {
      throw std::runtime_error("Vertex from" + id + " to " + to.GetId() + " does not exists");
    }
    return *(e.lock());
  }

  std::ostream &operator<<(std::ostream &os, const cse::Vertex &v) {
    os << "Vertex(" << v.id << ")";
    return os;
  }

  bool operator==(const Vertex &lhs, const Vertex &rhs) {
    return lhs.id == rhs.id && lhs.x == rhs.x && lhs.y == rhs.y;
  }
} // namespace cse
