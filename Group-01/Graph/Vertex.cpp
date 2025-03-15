#include "Vertex.hpp"

#include "Edge.hpp"
#include <cassert>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

namespace cse {
  /**
   * Adds an edge to this vertex's edge collection with a specific destination
   * @param e The edge to add
   * @param destination The destination vertex of the edge
   */
  void cse::Vertex::AddEdge(std::weak_ptr<Edge> const &e, cse::Vertex const &destination) {
    this->edges[destination.GetId()] = e;
  }

  /**
   * Constructs a vertex from a file stream
   * @param f Input stream to read from
   * @param prefix_size The indentation level
   */
  Vertex::Vertex(std::istream &f, size_t prefix_size) {
    FromFile(f, prefix_size);
  }

  /**
   * Adds an edge to this vertex
   * @param e The edge to add
   */
  void cse::Vertex::AddEdge(std::weak_ptr<Edge> const &e) {
    CleanupExpiredEdges();
    if (auto edge = e.lock()) {
      cse::Vertex const &toVertex = edge->GetTo();
      AddEdge(e, toVertex);
    }
  }

  /**
   * Removes any expired edge references from the edges collection
   */
  void cse::Vertex::CleanupExpiredEdges() {
    for (auto it = edges.begin(); it != edges.end();) {
      if (it->second.expired()) {
        it = edges.erase(it);
      } else {
        ++it;
      }
    }
  }

  /**
   * Gets the serializable properties for this vertex
   * @return Vector of property pairs for serialization
   */
  std::vector<std::pair<std::string, SerializableProperty>> Vertex::GetPropertyMap() {
    std::vector<std::pair<std::string, SerializableProperty>> properties;
    properties.emplace_back("X", SerializableProperty([this](const std::string &value) { this->x = std::stod(value); },
                                                      [this](std::ostream &s) { s << x; }));
    properties.emplace_back("Y", SerializableProperty([this](const std::string &value) { this->y = std::stod(value); },
                                                      [this](std::ostream &s) { s << y; }));
    return properties;
  }

  /**
   * Checks if this vertex is connected to another vertex
   * @param destination The vertex to check connection with
   * @return true if vertices are connected, false otherwise
   */
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

  /**
   * Gets the edge connecting this vertex to another vertex
   * @param to The destination vertex
   * @return Shared pointer to the edge
   * @throws runtime_error if edge doesn't exist
   */
  std::shared_ptr<cse::Edge> const cse::Vertex::GetEdge(cse::Vertex const &to) const {
    auto it = edges.find(to.GetId());
    if (it == edges.end() || it->second.expired()) {
      throw std::runtime_error("Edge from " + id + " to " + to.GetId() + " does not exist");
    }
    return it->second.lock();
  }

  std::ostream &operator<<(std::ostream &os, const cse::Vertex &v) {
    os << "Vertex(" << v.id << ")";
    return os;
  }

  bool operator==(const Vertex &lhs, const Vertex &rhs) {
    return lhs.id == rhs.id && lhs.x == rhs.x && lhs.y == rhs.y;
  }
} // namespace cse
