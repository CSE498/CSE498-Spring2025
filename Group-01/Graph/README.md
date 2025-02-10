# Graph Class
## Description

A class to manage a collection of vertices and edges; should be useful for conducting graph algorithms. 
The class should be able to load from files, save to file, access connection information, and add or remove vertices and edges. It should also allow fast access to vertices and easy iteration through vertices and edges.
[_From cse_](https://cse.github.io/project-details.html).

## Similar Classes
A list of similar classes in cpp include:
- std::unordered_map
- std::ordered_map
- std::tuple (for vertices)
- std::pair (for edges)

## Error Conditions
- Out of range/vertex does not exist errors.
- Repeated Vertices are not allowed error.

## Expected Challenges
- Integration with GraphPosition class.
- Algorithmic correctness and evaluation of algorithms that are provided as built in algorithms

## Expected Dependencies
- GraphPosition

## Base Class Specs
* For some of the methods, it might be considerable to change Vertex to GraphPosition
```cpp
template <class T>
class Graph {
public:
  cse::Vertex AddVertex(std::string id, T data, std::optional<double> X, std::optional<double> Y);
  cse::Vertex RemoveVertex(std::string id);
  cse::Vertex& GetVertex(std::string id);

  cse::Edge AddEdge(std::string v1_id, std::string v2_id, bool bidirectional = false );
  cse::Edge AddEdge(cse::Vertex &v1, cse::Vertex &v2, bool bidirectional = false );
  void RemoveEdge(cse::Edge &edge);
  void RemoveEdge(std::string const& edge_id);
  cse::Edge GetEdge(std::string const& edge_id);
  std::optional<cse::Edge> GetEdge(cse::Vertex &from, cse::Vertex &to);
  std::optional<cse::Edge> GetEdge(std::string from_id, std::string to_id );

  void ToFile(std::fstream s);
  static Graph FromFile(std::fstream s);
}

/**
 * Algorithms should be functions. Some possible algorithms include
 * A-Star
 * Search
 * DFS/BFS
 * Topological Sort
 * ...
*/
```
