/**
 * @file ActionMap.cpp
 * @author Nitish Maindoliya
 */

#include <cse/ActionMap.h>

namespace cse {
/**
 * @brief Check if an action exists
 * @param action Action name
 * @return True if the action exists, false otherwise
 */
bool ActionMap::contains(const std::string& action) const {
  return m_actions.contains(action);
}

/**
 * @brief Clear all actions
 */
void ActionMap::clear() {
  m_actions.clear();
}

/**
 * @brief Erase an action
 * @param action Action name
 */
void ActionMap::erase(const std::string& action) {
  m_actions.erase(action);
}

/**
 * @brief Return the size of the action map
 */
size_t ActionMap::size() const {
  return m_actions.size();
}

/**
 * @brief Check if the action map is empty
 */
bool ActionMap::empty() const {
  return m_actions.empty();
}
}  // namespace cse
