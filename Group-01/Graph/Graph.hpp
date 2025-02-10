#pragma once
#include <fstream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Edge.hpp"
#include "Vertex.hpp"

namespace cse {

  class Graph {
  private:
    std::unordered_map<std::string, std::shared_ptr<cse::Vertex>> vertices{};
    std::unordered_map<std::string, std::shared_ptr<cse::Edge>> edges{};

  public:
    std::shared_ptr<cse::Vertex> AddVertex(std::string id, double X = 0.0, double Y = 0.0);
    std::shared_ptr<cse::Vertex> GetVertex(std::string id);
    std::shared_ptr<cse::Vertex> RemoveVertex(std::string id);

    std::weak_ptr<cse::Edge> AddEdge(std::string v1_id, std::string v2_id, bool bidirectional = false);
    std::weak_ptr<cse::Edge> AddEdge(std::shared_ptr<cse::Vertex> &v1, std::shared_ptr<cse::Vertex> &v2,
                                     bool bidirectional = false);
    std::shared_ptr<cse::Edge> RemoveEdge(std::string const &edge_id);
    std::shared_ptr<cse::Edge> RemoveEdge(std::weak_ptr<cse::Edge> edge);
    std::weak_ptr<cse::Edge> GetEdge(std::string const &edge_id);
    std::weak_ptr<cse::Edge> GetEdge(std::shared_ptr<cse::Vertex> from, std::shared_ptr<cse::Vertex> to);
    std::weak_ptr<cse::Edge> GetEdge(std::string from_id, std::string to_id);

    // void ToFile(std::fstream &s);
    // static Graph FromFile(std::fstream &s);

    // TODO @lspecht: Add iterator for class
  };
} // namespace cse
