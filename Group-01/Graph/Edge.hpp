#pragma once
#include "../Util/Util.hpp"
#include "Vertex.hpp"
#include <iostream>
#include <string>

namespace cse {
  class Graph; // Forward declaration

  class Edge : public FileSerializable {
  private:
    std::string id;
    std::shared_ptr<cse::Vertex> from;
    std::shared_ptr<cse::Vertex> to;
    double weight = 0.0;

    // Helper for parsing edge properties
    struct EdgeProperties {
      std::string from_id;
      std::string to_id;
      double weight;
    };

    static EdgeProperties ParseProperties(std::istream &f, size_t indent_level) {
      auto properties = FileUtil::GetProperties(f, indent_level + cse::BASE_INDENTATION);
      assert(properties.size() == 3);
      assert(properties.at(0).first == "from");
      assert(properties.at(1).first == "to");
      assert(properties.at(2).first == "weight");

      return EdgeProperties{properties.at(0).second, properties.at(1).second, std::stod(properties.at(2).second)};
    }

  protected:
    std::string GetTypeName() const override { return "EDGE"; }
    std::vector<std::pair<std::string, SerializableProperty>> GetPropertyMap() override {
      std::vector<std::pair<std::string, SerializableProperty>> properties;
      properties.emplace_back(
          "from", SerializableProperty([this](std::ostream &s) { s << from->GetId(); }, [](const std::string &) {}));
      properties.emplace_back(
          "to", SerializableProperty([this](std::ostream &s) { s << to->GetId(); }, [](const std::string &) {}));
      properties.emplace_back(
          "weight", SerializableProperty([this](std::ostream &s) { s << weight; }, [](const std::string &) {}));
      return properties;
    }
    void SetId(std::string newId) override { id = newId; };

  public:
    virtual ~Edge() = default;
    Edge(const std::string id, std::shared_ptr<cse::Vertex> &from, std::shared_ptr<cse::Vertex> &to,
         double const weight = 0.0)
        : id(id), from(from), to(to), weight(weight) {};
    Edge() = delete;

    virtual bool IsConnected(cse::Vertex const &v1, cse::Vertex const &v2) { return v1 == *from && v2 == *to; };

    cse::Vertex &GetFrom() { return *from; };
    cse::Vertex &GetTo() { return *to; };
    std::string GetId() const override { return id; };
    double GetWeight() const { return weight; };

    static void CreateFromFile(std::istream &f, size_t indent_level, Graph &graph);
  };
} // namespace cse
