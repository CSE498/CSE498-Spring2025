/**
 * @file StateGrid.cpp
 * @author Dominik Leisinger
 */

#include "cse/StateGrid.h"
#include <cassert>
#include <iostream>
#include <map>
#include <utility>
#include "cse/StateGridPosition.h"
namespace cse {

/**
 * @brief Contructor for StateGrid object
 * @param diff string representing requested difficulty
 */
StateGrid::StateGrid(const std::string& diff) {
  load_map(diff);
}

/**
 * @brief Displays the grid to user
 */
///REVIEW COMMENT: an overloaded << to display StateGrid would be useful, but not needed
///unless we decide not to implement a better visual element to display our game.
void StateGrid::display_grid() {
  assert(!m_grid.empty() && "m_grid is empty and cannot display");

  for (const std::string& line : m_grid) {
    std::cout << line << "\n";
  }
}

/**
 * @brief Sets the specific position to occupied by agent
 * @param new_position pair containing new agent spot
 * @param agent pair containing current agent position
 */
bool StateGrid::set_state(std::pair<int, int> new_position, std::pair<int, int> agent) {
  assert(!m_grid.empty() && m_grid[agent.first][agent.second] == 'P');

  if (validate_position({new_position.first, new_position.second})) {
    m_grid[new_position.first][new_position.second] = 'P';
    m_grid[agent.first][agent.second] = ' ';
    return true;
  }
  return false;
}

/**
 * Returns property information about a specific state
 * @param state queried state
 * @return vector of strings holding info about state
 */
std::vector<std::string> StateGrid::define_state(char state) {
  auto possible_state = m_dictionary.find(state);
  assert(possible_state != m_dictionary.end() && "This state is not in the map!");
  return m_dictionary.at(state);
}
///REVIEW COMMENT: A review comment was made to add std::optional for this function in the case where no
/// StateGrid state was found, but I do not believe this necessary as the assert checks
/// if the row,col is within bounds which will guarantee a StateGrid state.
/**
 * @brief Returns the state of a grid position
 * @param row row of position
 * @param col col of position
 * @return state of (row,col) position
 */
char StateGrid::get_state(int row, int col) {
  assert(row < m_rows && col < m_cols && "This is not inside the grid");
  return m_grid[row][col];
}

/**
 * @brief Validates if a position can be occupied by agent
 * @param move std::pair containing row,col of position to be validated
 * @return T/F of position validity
 */
bool StateGrid::validate_position(std::pair<int, int> move) {
  assert(move.first < m_rows && move.second < m_cols && "This move is out of bounds");
  char validate = m_grid[move.first][move.second];
  return (m_dictionary.find(validate) != m_dictionary.end() && m_dictionary.at(validate)[1]=="Open");
}

/**
 * @brief finds all possible moves for agent from (row,col) position
 * @param row row of agent position
 * @param col col of agent position
 * @return vector of pairs of possible move directions
 */
std::vector<std::pair<int,int>> StateGrid::find_moves(int row, int col) {
  assert(row < m_rows && col < m_cols && "This is not inside the grid");
  std::vector<std::pair<int, int>> moves = {};
  std::vector<std::pair<int, int>> poss_moves = {{(row + 1), col}, {(row - 1), col}, {row, (col + 1)}, {row, (col - 1)}};
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
void StateGrid::load_map(const std::string& diff) {
  std::map<std::string, std::vector<std::string>> maps = {
      {"test", {"#####", "# P #", "##X##", "## ##", "#0  #", "#####"}}}; ///Could add functionality to load in a map from separate file
  if (maps.find(diff) != maps.end()) {
    m_grid = maps[diff];
  } else {                                          ///<< If wrong map input, default to test map
    m_grid = maps["test"];
  }
  m_cols = static_cast<int>(m_grid[0].size());
  m_rows = static_cast<int>(m_grid.size());
}

}  // namespace cse