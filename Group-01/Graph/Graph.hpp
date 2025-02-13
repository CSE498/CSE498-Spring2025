#pragma once
#include <fstream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Util/Util.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

namespace cse {

  class Graph : public FileSerializable {
  private:
    std::unordered_map<std::string, std::shared_ptr<cse::Vertex>> vertices{};
    std::unordered_map<std::string, std::shared_ptr<cse::Edge>> edges{};
    void ParseVertices(std::istream &f, size_t indent_level);

  protected:
    std::string GetTypeName() const override { return "GRAPH"; }
    std::string GetId() const override { return ""; }
    void SetId(std::string) override {}
    std::map<std::string, SerializableProperty> GetPropertyMap() override;
    void FromFile(std::istream &f, size_t prefix_size) override;

  public:
    Graph() {};
    Graph(std::istream &f);
    std::shared_ptr<cse::Vertex> AddVertex(std::string id, double X = 0.0, double Y = 0.0);
    std::shared_ptr<cse::Vertex> GetVertex(std::string const &id) const;
    std::shared_ptr<cse::Vertex> RemoveVertex(std::string id);

    std::weak_ptr<cse::Edge> AddEdge(std::string v1_id, std::string v2_id, bool bidirectional = false);
    std::weak_ptr<cse::Edge> AddEdge(std::shared_ptr<cse::Vertex> &v1, std::shared_ptr<cse::Vertex> &v2,
                                     bool bidirectional = false);
    void RemoveEdge(std::string const &edge_id);
    void RemoveEdge(std::weak_ptr<cse::Edge> edge);
    std::weak_ptr<cse::Edge> GetEdge(std::string const &edge_id) const;
    std::weak_ptr<cse::Edge> GetEdge(std::shared_ptr<cse::Vertex> const from,
                                     std::shared_ptr<cse::Vertex> const to) const;
    std::weak_ptr<cse::Edge> GetEdge(std::string from_id, std::string to_id);

    bool IsConnected(std::shared_ptr<cse::Vertex> const &v1, std::shared_ptr<cse::Vertex> const &v2) const;
    bool IsConnected(std::string const &v1_id, std::string const &v2_id) const;

    // TODO @lspecht: Add iterator for class
  };
} // namespace cse
