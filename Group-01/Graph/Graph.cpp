#include "Graph.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>

namespace cse {
  /**
   * Constructs a graph from a file stream
   * @param f Input stream to read from
   */
  Graph::Graph(std::istream &f) {
    FromFile(f, 0);
  }

  /**
   * Adds a new vertex to the graph
   * @param id Unique identifier for the vertex
   * @param X X-coordinate position
   * @param Y Y-coordinate position
   * @return Reference to the created vertex
   * @throws runtime_error if vertex ID already exists
   */
  cse::Vertex &cse::Graph::AddVertex(std::string const id, double X, double Y) {
    if (HasVertex(id)) {
      throw std::runtime_error("Vertex already exists: " + id);
    }

    auto v = std::make_shared<cse::Vertex>(id, X, Y);
    vertices[id] = v;
    return *vertices[id];
  }

  /**
   * Retrieves a vertex from the graph
   * @param id ID of the vertex to retrieve
   * @return Reference to the vertex
   * @throws out_of_range if vertex doesn't exist
   */
  cse::Vertex &cse::Graph::GetVertex(std::string const &id) const {
    if (vertices.find(id) == vertices.end()) {
      throw std::out_of_range("Vertex does not exist: " + id);
    }
    return *(vertices.at(id));
  }

  /**
   * Removes a vertex from the graph
   * @param id ID of the vertex to remove
   * @throws out_of_range if vertex doesn't exist
   */
  void cse::Graph::RemoveVertex(std::string const id) {
    auto it = vertices.find(id);
    if (it == vertices.end()) {
      std::cout << "Did not find vertex to remove" << std::endl;
      throw std::out_of_range("Vertex does not exist: " + id);
    }
    vertices.erase(it);
  }

  /**
   * Creates a new edge between two vertices
   * @param edge_id Unique identifier for the edge
   * @param v1_id Source vertex ID
   * @param v2_id Destination vertex ID
   * @param weight Edge weight
   * @return Shared pointer to the created edge
   */
  std::shared_ptr<Edge> Graph::CreateEdge(const std::string &edge_id, const std::string &v1_id,
                                          const std::string &v2_id, double const &weight) {
    auto v1 = vertices[v1_id];
    auto v2 = vertices[v2_id];
    return std::make_shared<Edge>(edge_id, v1, v2, weight);
  }

  /**
   * Adds a new edge to the graph using vertex IDs
   * @param v1_id Source vertex ID
   * @param v2_id Destination vertex ID
   * @param weight Edge weight
   * @return Weak pointer to the created edge
   */
  cse::Edge &cse::Graph::AddEdge(std::string const v1_id, std::string const v2_id, double const &weight) {
    if (!HasVertex(v1_id) || !HasVertex(v2_id)) {
      throw std::out_of_range("Both vertices must exist to create an edge");
    }

    std::string edge_id = v1_id + "-" + v2_id;
    auto edge = CreateEdge(edge_id, v1_id, v2_id, weight);

    cse::Vertex &v1 = GetVertex(v1_id);
    v1.AddEdge(edge);
    edges[edge_id] = edge;
    return *edge;
  }

  /**
   * Adds a new edge to the graph using vertex pointers
   * @param v1 Source vertex
   * @param v2 Destination vertex
   * @param weight Edge weight
   * @return Weak pointer to the created edge
   */
  cse::Edge &cse::Graph::AddEdge(cse::Vertex const &v1, cse::Vertex const &v2, double const &weight) {
    return AddEdge(v1.GetId(), v2.GetId(), weight);
  }

  /**
   * Gets an edge from the graph by ID
   * @param edge_id ID of the edge to retrieve
   * @return Weak pointer to the edge
   * @throws out_of_range if edge doesn't exist
   */
  cse::Edge &cse::Graph::GetEdge(std::string const &edge_id) const {
    if (edges.find(edge_id) == edges.end()) {
      throw std::out_of_range("Edge does not exist.");
    }
    auto edge_ptr = edges.at(edge_id);
    return *edge_ptr;
  }

  /**
   * Gets an edge between two vertices
   * @param from Source vertex
   * @param to Destination vertex
   * @return Weak pointer to the edge
   */
  cse::Edge &cse::Graph::GetEdge(cse::Vertex const &from, cse::Vertex const &to) const {
    return GetEdge(from.GetEdge(to)->GetId());
  }

  /**
   * Gets an edge between two vertices using their IDs
   * @param from_id Source vertex ID
   * @param to_id Destination vertex ID
   * @return Weak pointer to the edge
   */
  cse::Edge &cse::Graph::GetEdge(std::string const &from_id, std::string const &to_id) {
    return GetEdge(GetVertex(from_id), GetVertex(to_id));
  }

  /**
   * Removes an edge from the graph by ID
   * @param edge_id ID of the edge to remove
   * @throws out_of_range if edge doesn't exist
   */
  void cse::Graph::RemoveEdge(std::string const &edge_id) {
    auto it = edges.find(edge_id);
    if (it == edges.end()) {
      throw std::out_of_range("Edge does not exist: " + edge_id);
    }
    auto edge = std::move(it->second);
    edges.erase(it);
  }

  /**
   * Removes an edge from the graph using a weak pointer
   * @param edge Weak pointer to the edge to remove
   * @throws out_of_range if edge doesn't exist or is expired
   */
  void Graph::RemoveEdge(cse::Edge const &edge) {
    RemoveEdge(edge.GetId());
  }

  /**
   * Checks if two vertices are connected by an edge
   * @param v1 First vertex
   * @param v2 Second vertex
   * @return true if vertices are connected, false otherwise
   */
  bool Graph::IsConnected(cse::Vertex const &v1, cse::Vertex const &v2) const {
    try {
      auto e = GetEdge(v1, v2);
      return e.IsConnected(v1, v2);
    } catch (std::runtime_error) {
      // If there is a runtime error, the edge does not exist
    }

    return false;
  }

  /**
   * Checks if two vertices are connected by an edge using their IDs
   * @param v1_id First vertex ID
   * @param v2_id Second vertex ID
   * @return true if vertices are connected, false otherwise
   */
  bool Graph::IsConnected(std::string const &v1_id, std::string const &v2_id) const {
    return IsConnected(GetVertex(v1_id), GetVertex(v2_id));
  }

  /**
   * Parses the vertices section from a file stream
   * @param f Input stream to read from
   * @param indent_level The indentation level
   */
  void Graph::ParseVertices(std::istream &f, size_t indent_level) {
    std::string line;
    while (FileUtil::CheckPrefixSize(f, indent_level + cse::BASE_INDENTATION)) {
      auto vertex = std::make_shared<Vertex>(f, indent_level + cse::BASE_INDENTATION);
      vertices[vertex->GetId()] = vertex;
    }
  }

  /**
   * Parses the edges section from a file stream
   * @param f Input stream to read from
   * @param indent_level The indentation level
   */
  void Graph::ParseEdges(std::istream &f, size_t indent_level) {
    while (FileUtil::CheckPrefixSize(f, indent_level + cse::BASE_INDENTATION)) {
      Edge::CreateFromFile(f, indent_level + cse::BASE_INDENTATION, *this);
    }
  }

  /**
   * Parses a section header from a file stream and validates it
   * @param f Input stream to read from
   * @param expected_section The expected section header
   * @throws runtime_error if the section header is invalid
   */
  void Graph::ParseSection(std::istream &f, const std::string &expected_section) {
    std::string line;
    std::getline(f, line);
    auto [section_key, _] = FileUtil::SeparateKeyValue(line);
    if (section_key != expected_section) {
      throw std::runtime_error("Expected " + expected_section + " section, got: " + section_key);
    }
  }

  /**
   * Deserializes the graph from a file stream
   * @param f Input stream to read from
   * @param prefix_size The indentation level (unused)
   * @throws runtime_error if the file format is invalid
   */
  void Graph::FromFile(std::istream &f, size_t) {
    std::string line;
    std::getline(f, line);
    auto [key, value] = FileUtil::SeparateKeyValue(line);
    if (key != GetTypeName()) {
      throw std::runtime_error("Invalid type: " + key);
    }

    ParseSection(f, "Vertices");
    ParseVertices(f, cse::BASE_INDENTATION);

    std::getline(f, line); // Skip empty line
    ParseSection(f, "Edges");
    ParseEdges(f, cse::BASE_INDENTATION);
  }

  /**
   * Gets the serializable properties for this graph
   * @return Vector of property pairs for serialization
   */
  std::vector<std::pair<std::string, SerializableProperty>> Graph::GetPropertyMap() {
    std::vector<std::pair<std::string, SerializableProperty>> properties;

    auto verticesWriter = [this](std::ostream &s) {
      s << "\n";
      for (auto const &[id, vertex] : vertices) {
        vertex->ToFile(s, cse::BASE_INDENTATION);
      }
    };

    auto edgesWriter = [this](std::ostream &s) {
      s << "\n";
      for (auto const &[id, edge] : edges) {
        edge->ToFile(s, cse::BASE_INDENTATION);
      }
    };

    // Handler not needed since we override FromFile
    properties.emplace_back("Vertices", SerializableProperty(verticesWriter, [](const std::string &) {}));
    properties.emplace_back("Edges", SerializableProperty(edgesWriter, [](const std::string &) {}));
    return properties;
  }
} // namespace cse
