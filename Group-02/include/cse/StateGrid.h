/**
 * @file StateGrid.h
 * @author Dominik Leisinger
 *
 *
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include "cse/DataMap.h"

namespace cse {

class StateGrid {
 private:
  ///Rows in grid
  int m_rows = 0;
  ///Rows in grid
  int m_cols = 0;
  ///Grid to represent game map
  std::vector<std::string> m_grid;
  ///Map to represent the name and (future) properties of each state <<< Soon to be DataMap type
  ///REVIEW COMMENT: Had a review saying to make this a dedicated struct, this will become a DataMap object in Advanced version
  std::map<char, std::vector<std::string>> m_dictionary = {
      {' ', {"EmptySpace", "Open"} },
      {'#', {"Wall", "Closed"}},
      {'X', {"Enemy", "Open"}},
      {'0', {"Exit", "Open"}},
      {'P', {"Player", "Closed"}}
  };
 public:

  /**
   * Default StateGrid Constructor (No arguments)
   */
  StateGrid()
  {
    load_map("test");
  }

  [[maybe_unused]] explicit StateGrid(const std::string& diff);

  void load_map(const std::string& diff);

  void display_grid();
  ///REVIEW COMMENT: I had a comment about my use of std::pairs instead of a dedicated Point struct,
  /// like in SGPos, but this currently would not work with indexing into m_grid with doubles,
  /// so in advanced version I will include a better looking struct that will coincide with SGPos
  bool set_state(std::pair<int, int> new_position, std::pair<int, int> agent);

  char get_state(int row, int col);

  std::vector<std::string> define_state(char state);

  bool validate_position(std::pair<int, int> move);

  std::vector<std::pair<int,int>> find_moves(int row, int col);
};
}  // namespace cse