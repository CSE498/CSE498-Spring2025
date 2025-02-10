#include "Graph.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>

namespace cse {
  /**
   * TODO @lspecht: Add integration with GraphPosition
   * TODO @lspecht: Add GetAllEdges from vertex
   * TODO @lspecht: Add data parameter
   */
  std::shared_ptr<cse::Vertex> cse::Graph::AddVertex(std::string id, double X, double Y) {
    if (vertices.find(id) != vertices.end()) {
      throw std::runtime_error("Vertex already exists: " + id);
    }
    auto v = std::make_shared<cse::Vertex>(id, X, Y);
    vertices[id] = v;
    return v;
  }

  std::shared_ptr<cse::Vertex> cse::Graph::GetVertex(std::string id) {
    if (vertices.find(id) == vertices.end()) {
      throw std::out_of_range("Vertex does not exist: " + id);
    }
    return vertices.at(id);
  }

  std::shared_ptr<cse::Vertex> cse::Graph::RemoveVertex(std::string id) {
    auto it = vertices.find(id);
    if (it == vertices.end()) {
      throw std::out_of_range("Vertex does not exist: " + id);
    }
    auto removedVertex = it->second;
    vertices.erase(it);
    return removedVertex;
  }

  std::weak_ptr<cse::Edge> cse::Graph::AddEdge(std::string v1_id, std::string v2_id, bool bidirectional) {
    if (vertices.find(v1_id) == vertices.end() || vertices.find(v2_id) == vertices.end()) {
      throw std::out_of_range("One or both vertices do not exist.");
    }

    // TODO @lspecht: Maybe this should be a unique ID.
    // TODO @lspecht: Check if edge already exists.
    std::string edge_id = v1_id + "-" + v2_id;
    std::shared_ptr<cse::Edge> e;
    if (bidirectional) {
      e = std::make_shared<cse::BidirectionalEdge>(edge_id, vertices[v1_id], vertices[v2_id]);
    } else {
      e = std::make_shared<cse::Edge>(edge_id, vertices[v1_id], vertices[v2_id]);
    }

    GetVertex(v1_id)->AddEdge(e);
    edges[edge_id] = e;
    return e;
  }

  std::weak_ptr<cse::Edge> cse::Graph::AddEdge(std::shared_ptr<cse::Vertex> &v1, std::shared_ptr<cse::Vertex> &v2,
                                               bool bidirectional) {
    return AddEdge(v1->GetId(), v2->GetId(), bidirectional);
  }

  std::shared_ptr<cse::Edge> cse::Graph::RemoveEdge(std::string const &edge_id) {
    auto it = edges.find(edge_id);
    if (it == edges.end()) {
      throw std::out_of_range("Edge does not exist: " + edge_id);
    }
    auto edge = std::move(it->second);
    edges.erase(it);
    return edge;
  }

  std::shared_ptr<cse::Edge> Graph::RemoveEdge(std::weak_ptr<cse::Edge> edge) {
    if (edge.expired()) {
      throw std::out_of_range("Edge does not exist");
    }
    auto sh = edge.lock();
    return RemoveEdge(sh->GetId());
  }

  std::weak_ptr<cse::Edge> cse::Graph::GetEdge(std::string const &edge_id) {
    if (edges.find(edge_id) == edges.end()) {
      throw std::out_of_range("Edge does not exist.");
    }
    auto edge_ptr = edges.at(edge_id);
    return edge_ptr;
  }

  std::weak_ptr<cse::Edge> cse::Graph::GetEdge(std::shared_ptr<cse::Vertex> from, std::shared_ptr<cse::Vertex> to) {
    return GetEdge(from->GetEdge(to)->GetId());
  }

  std::weak_ptr<cse::Edge> cse::Graph::GetEdge(std::string from_id, std::string to_id) {
    return GetEdge(GetVertex(from_id), GetVertex(to_id));
  }

  // void cse::Graph::ToFile(std::fstream &s) {
  //   // TODO @lspecht: Implement this
  // }

  // cse::Graph cse::Graph::FromFile(std::fstream &s) {
  //   cse::Graph graph;
  //   // TODO @lspecht: Implement this
  //   return graph;
  // }
} // namespace cse
