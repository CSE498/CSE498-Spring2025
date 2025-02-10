#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace cse {
  class Edge;
  class Vertex {
  private:
    std::string id;
    double x, y = 0;
    std::map<std::string, std::weak_ptr<Edge>> edges{};
    void AddEdge(std::weak_ptr<Edge> const &e, std::shared_ptr<cse::Vertex> const &destination);
    void CleanupExpiredEdges();

  public:
    Vertex() = delete;
    Vertex(std::string id) : id(id) {};
    Vertex(std::string id, double x, double y) : id(id), x(x), y(y) {};

    void AddEdge(std::weak_ptr<Edge> const &e);
    bool IsConnected(std::shared_ptr<cse::Vertex> const &destination);

    std::string GetId() const { return id; };
    const std::map<std::string, std::weak_ptr<Edge>>& GetEdges() const { return edges; };
    double GetX() const { return x; };
    double GetY() const { return y; };

    std::shared_ptr<cse::Edge> const GetEdge(std::shared_ptr<cse::Vertex> const &to);

    friend std::ostream &operator<<(std::ostream &, const Vertex &);
    friend bool operator==(const Vertex &lhs, const Vertex &rhs);
    friend class Graph; // Allow Graph to call RemoveEdge
  };

  std::ostream &operator<<(std::ostream &os, const cse::Vertex &v);
  bool operator==(const Vertex &lhs, const Vertex &rhs);
} // namespace cse
