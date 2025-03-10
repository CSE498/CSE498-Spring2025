/**
 * @file StringSet.cpp
 * @author Orhan Aydin
 * @brief Implementation of StringSet class
 */

#include "StringSet.hpp"

/**
 * @brief Union of two sets
 * @param other The second set
 * @return A new set that contains unique elements from both sets
 */
cse::StringSet cse::StringSet::Union(const StringSet& other) const {

  StringSet result;

  for (const auto& str : mElements) {
    result.insert(str);
  }

  for (const auto& str : other.mElements) {
    result.insert(str);
  }

  return result;
}

/**
 * @brief Intersection of two sets
 * @param other The second set
 * @return A set of common values in 2 sets
 */
cse::StringSet cse::StringSet::Intersection(const StringSet& other) const {

  StringSet result;

  for (const auto& str : mElements) {

    if (other.mElements.find(str) != other.mElements.end()) {
      result.insert(str);
    }
  }

  return result;
}

/**
 * @brief Operates differentiation between two string sets
 * @param other the second set
 * @return the difference set
 */
cse::StringSet cse::StringSet::Difference(const cse::StringSet& other) const {

  StringSet result;

  // Iterate through every element in mElements
  for (const auto& str : mElements) {

    if (other.mElements.find(str) == other.mElements.end()) {
      result.insert(str);
    }
  }

  return result;
}

/**
 * @brief Delete or keep elements based on filter and boolean parameter
 * @param filter Custom filter function
 * @param erase Boolean, RetainFilter function calls with false, RemoveFilter function calls with true
 */
void cse::StringSet::Filter(const std::function<bool(const std::string &)> filter, bool erase) {
    std::vector<std::string> filteredElements;

  for(const auto& str : mElements) {
    if(erase == filter(str)){
      filteredElements.push_back(str);
    }
  }

  for(const auto& str : filteredElements){
    mElements.erase(str);
  }
}

/**
 * @brief Keep elements in string set based on custom filter
 * @param filter custom function
 */
void cse::StringSet::RetainFilter(const std::function<bool(const std::string&)> filter) {
  Filter(filter, false);
}

/**
 * @brief Delete elements based on custom filter
 * @param filter custom function
 */
void cse::StringSet::RemoveFilter(const std::function<bool(const std::string&)> filter) {
  Filter(filter, true);
}
