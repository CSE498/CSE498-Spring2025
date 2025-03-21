/**
 * @file StringSet.hpp
 * @author Orhan Aydin
 * @author Emil Rahn-Siegel
 * @author Ivan Bega
 * @brief Header file for StringSet class
 */

#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
#include <vector>
#include <cassert>
#include <ranges>
#include <algorithm>
#include <regex>
#include <random>
namespace cse {

/**
 * @brief A container(unordered_set) with a set of strings and various methods
 * like adding, removing, checking existence, set operations and filtering
 * to simplify using the container.
 *
 */
template<class T = std::string>
class StringSet {
private:
  /// @brief Unordred set of string that as underlying data structure
  std::unordered_set<T> mElements;

public:
  /// @brief Define an iterator type for string set (unordered set)
  using iterator = std::unordered_set<T>::iterator;
  
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
  void insert(const T &str) { mElements.insert(str); }

  /**
  * @brief Add vector of strings into the string set
  * @param stringVector  Vector of strings
  */
  void insert(const std::vector<T> &stringVector){
    for(const T& str : stringVector){
      mElements.insert(str);
    }
  }

  
  /**
  * @brief Erase specific string from string set
  * @param str Deleted from string set
  */
  void erase(const T &str) {
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
   * @brief Check if two string sets are equal
   * @param other The second set
   */
  bool operator==(const StringSet &other) const {
    return mElements == other.mElements;
  }
  
  /**
  * @brief Check if a specific string in the set or not
  * @param str that needs to be checked
  * @return 0 or 1. If str in the set returns 1 otherwise 0
  */
  size_t count(const T &str) const { return mElements.count(str); }

  /**
  * @brief Convert set to vector
  * @return Vector of strings
  */
  std::vector<T> ToVector() const
  {return std::vector<T>(mElements.begin(), mElements.end()); }


  StringSet Union(const StringSet &other) const;
  
  StringSet Intersection(const StringSet &other) const;
  
  StringSet Difference(const StringSet &other) const;

  void Filter(const std::function<bool(const T &str)> filter, bool erase);
  
  void RetainFilter(const std::function<bool(const T &str)> filter);
  
  void RemoveFilter(const std::function<bool(const T &str)> filter);

  bool IsSubset(const StringSet &other) const;

  void SubstringFilter(const T &substring);

  void SizeFilter(int size);

  StringSet Search(const T &wildcard);

  int countOccurence(const T &substring);

  StringSet RandomSample(int sampleSize, const std::function<bool(const T&)> filter = [](const T&) { return true; });

  std::tuple<int, double, T, T>Statistics();

  StringSet SymmetricDifference(const StringSet &other) const;

  StringSet UnionWith(const StringSet &other, const std::function<bool(const T &str)> filter);

  std::set<T> sort(const std::function<bool(const T &str, const T &str2)> comparator) const;

};

/**
 * @brief Union of two sets
 * @param other The second set
 * @return A new set that contains unique elements from both sets
 */

template<typename T>
cse::StringSet<T> cse::StringSet<T>::Union(const StringSet<T>& other) const {

  StringSet<T> result;

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
template<typename T>
cse::StringSet<T> cse::StringSet<T>::Intersection(const StringSet<T>& other) const {

  StringSet<T> result;

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
template<typename T>
cse::StringSet<T> cse::StringSet<T>::Difference(const cse::StringSet<T>& other) const {

  StringSet<T> result;

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
template<typename T>
void cse::StringSet<T>::Filter(const std::function<bool(const T &)> filter, bool erase) {
    std::vector<T> filteredElements;

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
template<typename T>
void cse::StringSet<T>::RetainFilter(const std::function<bool(const T&)> filter) {
  Filter(filter, false);
}

/**
 * @brief Delete elements based on custom filter
 * @param filter custom function
 */
template<typename T>
void cse::StringSet<T>::RemoveFilter(const std::function<bool(const T&)> filter) {
  Filter(filter, true);
}

/**
 * @brief Checks if a current set is a subset of another set
 * 
 * @param other Other set that is a superset 
 * @return true Current set is a subset of other set
 * @return false Current set is not a subset of other set
 */
template<typename T>
bool cse::StringSet<T>::IsSubset(const StringSet<T> &other) const{
  // Prepare a lambda that checks if captured element is in the other set
  // Used DeepSeek to assist with this lambda
  auto otherPredicate = [&other] (const T& element) {
    return other.count(element) == 1;
  };

  // use all_of in ranges to loop through each element in mElements
  return std::ranges::all_of(mElements, otherPredicate);
}

/**
 * @brief Removes words from a current StringSet that contain a substring
 * 
 * @param substring Substring to check against
 */
template<typename T>
void cse::StringSet<T>::SubstringFilter(const T &substring) {
  // Lambda that will be used in RemoveFilter to filter words that we need
  auto substringPredicate = [&substring] (const T& element) {
    return element.find(substring) != T::npos;
  };

  RemoveFilter(substringPredicate);
}
/**
 * @brief Search for a string with wildcard
 * 
 * @param wildcard Wildcard string
 * @return StringSet<T> Set of strings that match the wildcard
 */
template<typename T>
cse::StringSet<T> cse::StringSet<T>::Search(const T &wildcard) {
    StringSet<T> result;
    // Using std::regex_replace was recommended to me by github co
    // Convert wildcard to regex
    T regexPattern = "^" + std::regex_replace(wildcard, std::regex(R"(\*)"), ".*") + "$";
    regexPattern = std::regex_replace(regexPattern, std::regex(R"(\?)"), ".");

    // Create regex object
    std::regex pattern(regexPattern);

    // Iterate through elements and add matching ones to result
    for (const auto& element : mElements) {
        if (std::regex_match(element, pattern)) {
            result.insert(element);
        }
    }

    return result;
}

template<typename T>
int cse::StringSet<T>::countOccurence(const T &substring) {
  int totalCount = 0;

  for (const auto& element : mElements) {
      size_t pos = element.find(substring);
      while (pos != T::npos) {
          ++totalCount;
          pos = element.find(substring, pos + substring.length());
      }
  }

  return totalCount;
}

template<typename T>
cse::StringSet<T> cse::StringSet<T>::RandomSample(int sampleSize, const std::function<bool(const T&)> filter) {
    StringSet<T> result;
    if (sampleSize <= 0) {
        return result;
    }

    std::vector<T> elements;
    for (const auto& element : mElements) {
        if (filter(element)) {
            elements.push_back(element);
        }
    }

    if (static_cast<std::unordered_set<T>::size_type>(sampleSize) > elements.size()) {
        sampleSize = elements.size();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(elements.begin(), elements.end(), gen);

    for (int i = 0; i < sampleSize; ++i) {
        result.insert(elements[i]);
    }

    return result;
}

template<typename T>
std::tuple<int, double, T, T> cse::StringSet<T>::Statistics() {
    int numStrings = size();
    if (numStrings == 0) {
        return std::make_tuple(0, 0.0, "", "");
    }

    int totalLength = 0;
    T longestString = "";
    T shortestString = *mElements.begin();
    
    for (const auto& str : mElements) {
        int length = static_cast<int>(str.length());
        totalLength += length;
        if (length > static_cast<int>(longestString.length())) {
            longestString = str;
        }
        if (length < static_cast<int>(shortestString.length())) {
            shortestString = str;
        }
    }

    double avgLength = static_cast<double>(totalLength) / numStrings;

    return std::make_tuple(numStrings, avgLength, longestString, shortestString);
}

/**
 * @brief Removes strings of length not equal to size
 * 
 * @param size length of strings that will be retained
 */
template<typename T>
void cse::StringSet<T>::SizeFilter(int length) {
  assert(length > 0);
  
  auto sizePredicate = [length] (const T& element) {
    return element.length() == static_cast<std::size_t>(length);
  };

  RetainFilter(sizePredicate);
}


/**
 * @brief Check both sets and return not common elements from both sets
 * @param other the second set
 * @return Symmetric Difference set
 */
template<typename T>
cse::StringSet<T> cse::StringSet<T>::SymmetricDifference(const cse::StringSet<T>& other) const
{
    StringSet<T> result1;
    StringSet<T> result2;
    StringSet<T> finalResult;

    result1 = Difference(other);
    result2 = other.Difference(*this);

    finalResult = result1.Union(result2);

    return finalResult;
}

/**
 * @brief Union two sets if their elements meet the custom filter condition
 * @param other the second set
 * @param filter custom function(condition)
 * @return Union of two sets based on the custom filter
 */
template<typename T>
cse::StringSet<T> cse::StringSet<T>::UnionWith(const cse::StringSet<T> &other, const std::function<bool(const T &)> filter)
{
    StringSet<T> result = Union(other);
    result.RetainFilter(filter);
    return result;
}

/**
 * @brief Sort the StringSet<T>
 * @param comparator sorting condition
 * @return sorted set
 */
template<typename T>
std::set<T> cse::StringSet<T>::sort(const std::function<bool(const T &str, const T &str2)> comparator) const
{
    std::vector<T> sortedElements = ToVector();
    std::sort(sortedElements.begin(), sortedElements.end(), comparator);
    return std::set<T>(sortedElements.begin(), sortedElements.end());
}
}  // namespace cse