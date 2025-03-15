#pragma once
#include <stdexcept>
#include <string>

/** 
 * Used ChatGPT in assitance to help create custom graph exceptions 
 * This allows error nameing/handling to be more related
*/
namespace cse {
  /**
   * Base class for custom graph exceptions as 
   */
  class graph_error : public std::runtime_error {
  public:
    explicit graph_error(const std::string& message) : std::runtime_error(message) {}
  };

  class vertex_already_exists_error : public graph_error {
  public:
    explicit vertex_already_exists_error(const std::string& id) 
      : graph_error("Vertex already exists: " + id), vertex_id(id) {}
    
    std::string vertex_id;
  };

  class vertex_not_found_error : public graph_error {
  public:
    explicit vertex_not_found_error(const std::string& id) 
      : graph_error("Vertex does not exist: " + id), vertex_id(id) {}
    
    std::string vertex_id;
  };

  class edge_not_found_error : public graph_error {
  public:
    explicit edge_not_found_error(const std::string& id) 
      : graph_error("Edge does not exist: " + id), edge_id(id) {}
    
    std::string edge_id;
  };

  class edge_connection_error : public graph_error {
  public:
    explicit edge_connection_error(const std::string& message) 
      : graph_error(message) {}
  };

  class file_format_error : public graph_error {
  public:
    explicit file_format_error(const std::string& message) 
      : graph_error(message) {}
  };
}