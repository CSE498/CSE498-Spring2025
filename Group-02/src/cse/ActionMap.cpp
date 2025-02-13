/**
 * @file ActionMap.cpp
 * @author Nitish Maindoliya
 */

#include <cse/ActionMap.h>

#include <stdexcept>

namespace cse {

/**
 * Insert a new action into the map.
 * @param name The name of the action.
 * @param action The action to be inserted.
 */
void ActionMap::insert(const std::string& name, const std::function<void()>& action) {
  m_actions[name] = action;
}

/**
 * Erase an action from the map.
 * @param name The name of the action to be erased.
 */
void ActionMap::erase(const std::string& name) {
  m_actions.erase(name);
}

/**
 * Check if the map contains an action with the given name.
 * @param name The name of the action to check.
 * @return True if the action is found, false otherwise.
 */
[[nodiscard]] bool ActionMap::contains(const std::string& name) const {
  return m_actions.contains(name);
}

/**
 * Clear all actions from the map.
 */
void ActionMap::clear() {
  m_actions.clear();
}

/**
 * Invoke an action with the given name.
 * @param name The name of the action to invoke.
 */
void ActionMap::invoke(const std::string& name) {
  if (!m_actions.contains(name)) {
    throw std::runtime_error("Action not found");
  }

  m_actions[name]();
}

/**
 * Get the action with the given name.
 * @param name The name of the action to get.
 * @return The action with the given name.
 */
std::function<void()>& ActionMap::operator[](const std::string& name) {
  return m_actions[name];
}

/**
 * Get the action with the given name.
 * @param name The name of the action to get.
 * @return The action with the given name.
 */
const std::function<void()>& ActionMap::at(const std::string& name) {
  return m_actions.at(name);
}
}  // namespace cse
