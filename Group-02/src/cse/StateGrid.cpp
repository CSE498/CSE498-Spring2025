/**
 * @file StateGrid.cpp
 * @author Dominik Leisinger
 */

#include "cse/StateGrid.h"
#include <cassert>
#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "cse/StateGridPosition.h"
namespace cse {

///NOTE: Used ChatGPT for syntax for this overload
///Chat link: https://chatgpt.com/share/67d227cf-5f50-8001-86f4-494a0f71a7ea
std::ostream& operator<<(std::ostream& os, const cse::AuditedVector<std::string>& grid) {
  for (const auto& row : grid) {
    os << row << "\n";
  }
  return os;
}

/**
 * @brief Displays the grid to user
 */
///REVIEW COMMENT: an overloaded << to display StateGrid would be useful, but not needed
///unless we decide not to implement a better visual element to display our game.
void StateGrid::display_grid() {
  assert(!m_grid.empty() && "m_grid is empty and cannot display");
  std::cout<< &m_grid;
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
  assert(m_dictionary.find(state) && "This state is not in the map!");
  return m_dictionary.get_info(state);
}
/**
 * Changes properties of specified states (e.g. "Open" to "Closed" traversability)
 * @param changestate state to alter
 * @param property property to change
 * @param changeprop new editied property
 */
void StateGrid::set_condition(char changestate, std::string property, std::string changeprop)
{
  assert(m_dictionary.find(changestate) && "This state is not in the map!");
  m_dictionary.change_property(changestate,property,std::move(changeprop));
}

/**
 * This removes the specified states/conditions from an object
 * @param changestate state to alter
 * @param property property to change
 */
void StateGrid::remove_conditions(char changestate, std::string property)
{
    assert(m_dictionary.find(changestate) && "This state is not in the map!");
    std::string tempstring = property;
    ///need to remove the property from the state
}
/**
 * Will be called from set_state, and makes calls depending on most recent agent move
 * and the properties of the new agent state
 */
void StateGrid::find_properties()
{

}

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
  return (m_dictionary.find(validate) && m_dictionary.traversable(validate));
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
///Used ChatGPT for file loading syntax: https://chatgpt.com/share/67da2af9-a22c-8001-8a07-ff125bba08e7
void StateGrid::load_map(const std::string& diff) {

  ///Currently no check for incorrect filename other than thrown exception
  std::string filename = diff + ".csv";
  std::ifstream file(filename);
  cse::AuditedVector<std::string> pregrid;

  if(!file.is_open())
  {
    throw std::runtime_error("File could not be opened: " + filename);
  }

  std::string line;
  while(std::getline(file,line))
  {
    pregrid.push_back(line);
  }
  file.close();

  m_grid = pregrid;
  m_cols = static_cast<int>(m_grid[0].size());
  m_rows = static_cast<int>(m_grid.size());

}

/**
 * @brief iterates through each cell and applies the passed function or lambda
 * @param func function or lambda to be applied to each cell
 */
void StateGrid::modify_all_cells(const std::function<void(int, int, char&)> &func) {
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_cols; ++j) {
      func(i, j, m_grid[i][j]);
    }
  }
}


}  // namespace cse