/**
 * @file StateGrid.h
 * @author Dominik Leisinger
 *
 *
 */

#pragma once

#include <map>
#include <string>
#include <vector>

namespace cse {
class StateGrid {
 private:
  ///Rows in grid
  size_t m_rows = 0;
  ///Rows in grid
  size_t m_cols = 0;
  ///Grid to represent game map
  std::vector<std::string> m_grid;

 public:
  StateGrid(size_t rows, size_t cols, const std::string& diff);

  void choose_map(const std::string& diff);

  void display_grid();

  bool set_state(std::pair<int, int> move, std::pair<int, int> agent);

  char get_state(int row, int col);

  bool validate_position(std::pair<int, int> move);

  std::vector<std::pair<int, int>> find_moves(int row, int col);
};
}  // namespace cse