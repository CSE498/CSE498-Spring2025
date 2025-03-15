/**
 * @file StringSet.hpp
 * @author Orhan Aydin
 * @brief Header file for StringSet class
 */

#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cassert>

namespace cse {

/**
 * @brief A container(unordered_set) with a set of strings and various methods
 * like adding, removing, checking existence, set operations and filtering
 * to simplify using the container.
 *
 */
class StringSet {
private:
  /// @brief Unordred set of string that as underlying data structure
  std::unordered_set<std::string> mElements;

public:
  /// @brief Define an iterator type for string set (unordered set)
  using iterator = std::unordered_set<std::string>::iterator;
  
  /**
  * @brief Iterator to the first element of string set (begin iterator)
  * @return Iterator pointing to begining of string set
  */
  iterator begin() { return mElements.begin(); }
  
  /**
  * @brief Iterator to the end of string set (end iterator)
  * @return Iterator pointing past the last element of string set
  */
  iterator end() { return mElements.end(); }
  
  /**
  * @brief Add string into the string set
  * @param str Added to string set
  */
  void insert(const std::string &str) { mElements.insert(str); }

  /**
  * @brief Add vector of strings into the string set
  * @param stringVector  Vector of strings
  */
  void insert(const std::vector<std::string> &stringVector){
    for(const std::string& str : stringVector){
      mElements.insert(str);
    }
  }

  
  /**
  * @brief Erase specific string from string set
  * @param str Deleted from string set
  */
  void erase(const std::string &str) {
    assert(!str.empty() && "Erasing empty string");
    mElements.erase(str);
  }
  
  /**
  * @brief Make string set empty
  */
  void clear() { mElements.clear(); }
  
  /**
  * @brief Get the size of set
  * @return Size of string set
  */
  size_t size() const { return mElements.size(); }
  
  /**
  * @brief Check if string set is empty
  * @return True if the set is empty, false otherwise
  */
  bool empty() const { return mElements.empty(); }
  
  /**
  * @brief Check if a specific string in the set or not
  * @param str that needs to be checked
  * @return 0 or 1. If str in the set returns 1 otherwise 0
  */
  size_t count(const std::string &str) const { return mElements.count(str); }
  
  StringSet Union(const StringSet &other) const;
  
  StringSet Intersection(const StringSet &other) const;
  
  StringSet Difference(const StringSet &other) const;

  void Filter(const std::function<bool(const std::string &str)> filter, bool erase);
  
  void RetainFilter(const std::function<bool(const std::string &str)> filter);
  
  void RemoveFilter(const std::function<bool(const std::string &str)> filter);

};
}  // namespace cse