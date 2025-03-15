/* --- StaticVector.h --- */

/* ------------------------------------------
Author: Alex Mueller 
Date: 2/7/2025
------------------------------------------ */

#ifndef STATICVECTOR_H
#define STATICVECTOR_H

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

namespace cse {
/**
 * @brief A Class designed to create a vector like structure with a static size
 * @tparam T a templated object pointing to the type of objects in the vector
 * @tparam MAX_SIZE a size_t object that is the size of the vector
 */
template <typename T, size_t MAX_SIZE>
class StaticVector {
 private:
  /// @brief Array of size MAX_SIZE
  T data[MAX_SIZE];
  
  /// @brief Size of the StaticVector
  size_t currentSize;

 public:
  /// @brief Iterator for StaticVector
  using iterator = T*;

  /// @brief Default contructor for StaticVector
  StaticVector() : currentSize(0) {}
  /// @brief Default destructor
  ~StaticVector() = default;

  /// @brief Adds param value to next open slot of StaticVector
  /// @param value value to be added to StaticVector
  void push_back(const T& value) {
    if (currentSize >= MAX_SIZE) {
      throw std::out_of_range("Attempt to exceed static vector capacity.");
    }
    data[currentSize++] = value;
  }

  /// @brief Removes ending value of StaticVector
  void pop_back() {
    if (currentSize == 0) {
      throw std::out_of_range("Attempt to pop_back from empty vector.");
    }
    --currentSize;
  }

  /// @brief Clears contents of StaticVector
  void clear() { currentSize = 0; }

  /// @brief Gets value from vector at param index
  /// @param index Index to get value from in StaticVector
  T& at(size_t index) {
    if (index >= currentSize) {
      throw std::out_of_range("Index out of bounds.");
    }
    return data[index];
  }

  /// @brief Overload operator of [] and returns value
  /// @param index Index to get value from in StaticVector
  T& operator[](size_t index) { return data[index]; } 

  /// @brief Const version Overload operator of [] and returns value
  /// @param index Index to get value from in StaticVector
  const T& operator[](size_t index) const { 
    if (index >= currentSize) {
      throw std::out_of_range("Index out of bounds.");
    }
    return data[index];
  }

  /// @brief Returns front value of StaticVector
  T& front() {
    if (currentSize == 0) {
      throw std::out_of_range("Accessing front from an empty vector.");
    }
    return data[0];
  }

  /// @brief Returns back value of StaticVector
  T& back() {
    if (currentSize == 0) {
      throw std::out_of_range("Accessing back from an empty vector.");
    }
    return data[currentSize - 1];
  }

  /// @brief Checks if StaticVector is empty
  bool empty() const { return currentSize == 0; }

  /// @brief Returns current size of StaticVector
  size_t size() const { return currentSize; }

  /// @brief Returns max size of StaticVector
  size_t max_size() const { return MAX_SIZE; }

  /// @brief Begin iterator for StaticVector
  iterator begin() { return data; }

  /// @brief End iterator for StaticVector
  iterator end() { return data + currentSize; }
};

/// @brief Creates standard vector from StaticVector
/// @param sv StaticVector to be casted to std vector
template <typename T, size_t MAX_SIZE>
std::vector<T> ToVector(const StaticVector<T, MAX_SIZE>& sv) {
  std::vector<T> result;
  result.reserve(sv.size());
  for (size_t i = 0; i < sv.size(); ++i) {
    result.push_back(sv[i]);
  }
  return result;
}

}  // namespace cse

#endif  // STATICVECTOR_H