/**
 * @file StateGrid.h
 * @author Dominik Leisinger
 *
 *
 */

#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "AuditedVector.h"
#include "DataMap.hpp"

namespace cse {

/**
 * StateDictionary
 * Struct to hold each StateGrid state, along with any (and future) properties it has
 */
struct StateDictionary {
  std::map<char, cse::AuditedVector<std::string>> m_state_dictionary;

  StateDictionary() {
    m_state_dictionary = {{' ', {"EmptySpace", "Open"}},
                          {'#', {"Wall", "Closed"}},
                          {'X', {"Enemy", "Open"}},
                          {'0', {"Exit", "Open"}},
                          {'P', {"Player", "Closed"}}};
  }
  bool find(char searchchar)
  {
    return m_state_dictionary.find(searchchar) != m_state_dictionary.end();
  }
  bool traversable(char searchchar)
  {
    return m_state_dictionary.at(searchchar)[1] == "Open";
  }
  cse::AuditedVector<std::string> get_info(char searchchar)
  {
    return m_state_dictionary.at(searchchar);
  }
  void change_property(char changestate, std::string& property, std::string changeprop)
  {
    cse::AuditedVector<std::string> properties = m_state_dictionary.at(changestate);
    auto found = std::find(properties.begin(), properties.end(), property);
    if(found != properties.end()){*found = std::move(changeprop);};
  }
};

class StateGrid {
 private:
  ///Rows in grid
  int m_rows = 0;
  ///Rows in grid
  int m_cols = 0;
  ///Grid to represent game map
  cse::AuditedVector<std::string> m_grid;

  StateDictionary m_dictionary;

 public:

  /**
   * Default StateGrid Constructor (No arguments)
   */
  StateGrid()
  {
    load_map("test");
  }

  /**
 * @brief Contructor for StateGrid object
 * @param diff string representing requested difficulty
 */
  explicit StateGrid(const std::string& diff) {
    load_map(diff);
  }

  void load_map(const std::string& diff);

  void display_grid();
  ///REVIEW COMMENT: I had a comment about my use of std::pairs instead of a dedicated Point struct,
  /// like in SGPos, but this currently would not work with indexing into m_grid with doubles,
  /// so in advanced version I will include a better looking struct that will coincide with SGPos
  bool set_state(std::pair<int, int> new_position, std::pair<int, int> agent);

  char get_state(int row, int col);

  std::vector<std::string> define_state(char state);

  void set_condition(char changestate, std::string property, std::string changeprop);

  void remove_conditions(char changestate, std::string property);

  void find_properties();

  bool validate_position(std::pair<int, int> move);

  std::vector<std::pair<int,int>> find_moves(int row, int col);

  void modify_all_cells(const std::function<void(int, int, char&)>& func);
};
}  // namespace cse