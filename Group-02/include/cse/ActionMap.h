/**
 * @file ActionMap.h
 * @author Nitish Maindoliya
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

namespace cse {
class ActionMap {
 public:
  void insert(const std::string& name, const std::function<void()>& action);

  void erase(const std::string& name);

  [[nodiscard]] bool contains(const std::string& name) const;

  void clear();

  void invoke(const std::string& name);

  std::function<void()>& operator[](const std::string& name);

  [[nodiscard]] const std::function<void()>& at(const std::string& name);

 private:
  std::unordered_map<std::string, std::function<void()>> m_actions;
};

};  // namespace cse
