/**
 * @file ActionMap.h
 * @author Nitish Maindoliya
 */

#pragma once

#include <cassert>

#include <any>
#include <functional>
#include <string>
#include <unordered_map>

namespace cse {
class ActionMap {
 private:
  /// Map of actions and their corresponding functions
  std::unordered_map<std::string, std::any> m_actions;

 public:
  /// Default constructor
  ActionMap() = default;

  /// Default destructor
  ~ActionMap() = default;

  /// Default copy/move constructor
  ActionMap(const ActionMap&) = default;

  /// Default copy assignment operator
  ActionMap& operator=(const ActionMap&) = default;

  /**
   * @brief Bind an action to a function
   * @tparam Func Function type
   * @param action Action name
   * @param func Function to bind
   */
  template <typename Func>
  void insert(const std::string& action, Func&& func) {
    m_actions[action] = std::function(std::forward<Func>(func));
  }

  /**
   * @brief Invoke an action with arguments
   * @tparam Ret Return type
   * @tparam Args Argument types
   * @param action Action name
   * @param args Arguments
   * @return Return value of the function
   */
  template <typename Ret = void, typename... Args>
  Ret invoke(const std::string& action, Args&&... args) {
    if (const auto it = m_actions.find(action); it != m_actions.end()) {
      try {
        using Func = std::function<Ret(Args...)>;
        return std::any_cast<Func>(it->second)(std::forward<Args>(args)...);
      } catch (const std::bad_any_cast& e) {
        assert(false &&
               "Wrong function signature for action. Check the return type and arguments. You may need to use "
               "invoke<Ret, Args...>().");
      }
    } else {
      assert(false && "Action not found.");
    }

    if constexpr (std::is_same_v<Ret, void>) {
      return;
    } else {
      return Ret{};
    }
  }

  [[nodiscard]] bool contains(const std::string& action) const;

  void clear();

  void erase(const std::string& action);

  [[nodiscard]] size_t size() const;

  [[nodiscard]] bool empty() const;
};

};  // namespace cse
