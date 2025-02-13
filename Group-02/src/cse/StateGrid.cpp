/**
 * @file StateGrid.cpp
 * @author Dominik Leisinger
 */

#include "cse/StateGrid.h"
#include <iostream>
#include <utility>
#include <cassert>
namespace cse {

/**
 * @brief Contructor for StateGrid object
 * @param rows rows in grid map
 * @param cols cols in grid map
 * @param diff string representing requested difficulty
 */
StateGrid::StateGrid(const std::string& diff){
  choose_map(diff);
}

/**
 * @brief Displays the grid to user
 */
void StateGrid::display_grid() {
  assert(!m_grid.empty() && "m_grid is empty and cannot display");

  for (auto line : m_grid) {
    std::cout << line << "\n";
  }
}

/**
 * @brief Sets the specific position to occupied by agent
 * @param move pair containing new agent spot
 * @param agent pair containing current agent position
 */
bool StateGrid::set_state(std::pair<int, int> move, std::pair<int, int> agent) {
  assert(!m_grid.empty() && m_grid[agent.first][agent.second] =='P');
  if (validate_position(std::pair(move.first, move.second))) {
    m_grid[move.first][move.second] = 'P';
    m_grid[agent.first][agent.second] = ' ';
    return true;
  }
  return false;
}

/**
 * @brief Returns the state of a grid position
 * @param row row of position
 * @param col col of position
 * @return state of (row,col) position
 */
char StateGrid::get_state(int row, int col) {
  assert(row <= m_rows && col <= m_cols && "This is not inside the grid");
  return m_grid[row][col];
}
/**
 * @brief Validates if a position can be occupied by agent
 * @param row row of position
 * @param col col of position
 * @return T/F of position validity
 */
bool StateGrid::validate_position(std::pair<int, int> move) {
  assert(move.first <= m_rows && move.second <= m_cols && "This move is out of bounds");
  char validate = m_grid[move.first][move.second];
  if (validate == ' ' || validate == 'X') { /// << Will add '0' when adding win function
    return true;
  }
  return false;
}

/**
 * @brief finds all possible moves for agent from (row,col) position
 * @param row row of agent position
 * @param col col of agent position
 * @return vector of pairs of possible move directions
 */
std::vector<std::pair<int, int>> StateGrid::find_moves(int row, int col) {
  assert(row <= m_rows && col <= m_cols && "This is not inside the grid");
  std::vector<std::pair<int, int>> moves = {};
  std::vector<std::pair<int, int>> poss_moves = {std::pair((row+1), col), std::pair((row-1), col), std::pair(row, (col+1)),
                                                 std::pair(row, (col-1))};
  for (auto move : poss_moves) {
    if (validate_position(move)) {
      moves.push_back(move);
    }
  }
  return moves;
}
/**
 * @brief sets m_grid to specified map
 * @param diff string to choose map of specified difficulty
 */
void StateGrid::choose_map(const std::string& diff) {
  std::map<std::string, std::vector<std::string>> maps = {{"test", {"#####", "# P #", "##X##", "## ##", "#0  #","#####"}}};
  if (maps.find(diff) != maps.end()) {
    m_grid = maps[diff];
    m_cols = 5;
    m_rows = 4;   /// << This is only until more maps are made, for testing purposes
  } else {
    m_grid = maps["test"];
    m_cols = 5;
    m_rows = 4;
  }
}
}  // namespace cse