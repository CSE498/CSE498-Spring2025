#include "Vertex.hpp"

#include "Edge.hpp"
#include <cassert>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

namespace cse {
  void cse::Vertex::AddEdge(std::weak_ptr<Edge> const &e, std::shared_ptr<cse::Vertex> const &destination) {
    this->edges[destination->GetId()] = e;
  }

  Vertex::Vertex(std::istream &f, size_t prefix_size) {
    FromFile(f, prefix_size);
  }

  void cse::Vertex::AddEdge(std::weak_ptr<Edge> const &e) {
    if (auto edge = e.lock()) {
      auto &origin = edge->GetFrom();
      auto &destination = edge->GetTo();
      AddEdge(e, destination);
      if (edge->IsBidirectional() && !(destination->IsConnected(origin))) {
        destination->AddEdge(e, origin);
      }
    }
  }

  void cse::Vertex::CleanupExpiredEdges() {
    for (auto it = edges.begin(); it != edges.end();) {
      if (it->second.expired()) {
        it = edges.erase(it);
      } else {
        ++it;
      }
    }
  }

  std::map<std::string, SerializableProperty> Vertex::GetPropertyMap() {
    std::map<std::string, SerializableProperty> properties;
    properties.emplace("X", SerializableProperty([this](const std::string &value) { this->x = std::stod(value); },
                                                 [this](std::ostream &s) { s << x; }));
    properties.emplace("Y", SerializableProperty([this](const std::string &value) { this->y = std::stod(value); },
                                                 [this](std::ostream &s) { s << y; }));
    return properties;
  }

  bool cse::Vertex::IsConnected(std::shared_ptr<cse::Vertex> const &destination) {
    auto it = edges.find(destination->GetId());
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

  std::shared_ptr<cse::Edge> const cse::Vertex::GetEdge(std::shared_ptr<cse::Vertex> const &to) {
    CleanupExpiredEdges();
    auto it = edges.find(to->GetId());
    if (it == edges.end() || it->second.expired()) {
      throw std::runtime_error("Edge from " + id + " to " + to->GetId() + " does not exist");
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
