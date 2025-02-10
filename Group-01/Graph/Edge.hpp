#pragma once
#include "Vertex.hpp"
#include <iostream>
#include <string>

namespace cse {
  /**
   * A single direction edge
   */
  class Edge {
  private:
    std::string id;
    std::shared_ptr<cse::Vertex> &from;
    std::shared_ptr<cse::Vertex> &to;
    //
  public:
    Edge() = delete;
    virtual ~Edge() = default;
    Edge(std::string id, std::shared_ptr<cse::Vertex> &from, std::shared_ptr<cse::Vertex> &to)
        : id(id), from(from), to(to) {};
    virtual bool IsBidirectional() { return false; };
    virtual bool IsConnected(std::shared_ptr<cse::Vertex> const &v1, std::shared_ptr<cse::Vertex> const &v2) {
      return v1 == from && v2 == to;
    };

    std::shared_ptr<cse::Vertex> &GetFrom() { return from; };
    std::shared_ptr<cse::Vertex> &GetTo() { return to; };
    std::string GetId() const { return id; };
  };

  class BidirectionalEdge : public cse::Edge {
  public:
    BidirectionalEdge() = delete;
    virtual ~BidirectionalEdge() = default;
    BidirectionalEdge(std::string id, std::shared_ptr<cse::Vertex> &from, std::shared_ptr<cse::Vertex> &to)
        : cse::Edge(id, from, to) {};
    // TODO @lspecht: Handle GetFrom and GetTo on bidirectional case
    bool IsBidirectional() override { return true; };
    bool IsConnected(std::shared_ptr<cse::Vertex> const &v1, std::shared_ptr<cse::Vertex> const &v2) override {
      return Edge::IsConnected(v1, v2) || Edge::IsConnected(v2, v1);
    };
  };
} // namespace cse
