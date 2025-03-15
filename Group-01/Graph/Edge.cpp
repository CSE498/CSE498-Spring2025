#include "Edge.hpp"
#include "Graph.hpp"

/**
 * Creates an edge from file input and adds it to the graph
 * @param f Input stream to read from
 * @param indent_level The indentation level
 * @param graph The graph to add the edge to
 * @throws runtime_error if input format is invalid
 */
void cse::Edge::CreateFromFile(std::istream &f, size_t indent_level, Graph &graph) {
  std::string line;
  std::getline(f, line);
  auto [key, id] = FileUtil::SeparateKeyValue(line);
  if (key != "EDGE") {
    throw std::runtime_error("Invalid type: " + key);
  }

  auto props = ParseProperties(f, indent_level);
  auto from = graph.GetVertex(props.from_id);
  auto to = graph.GetVertex(props.to_id);
  graph.AddEdge(from, to, props.weight);
}