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

template <typename T, size_t MAX_SIZE>
class StaticVector {
 private:
  T data[MAX_SIZE];
  size_t currentSize;

 public:
  using iterator = T*;

  StaticVector() : currentSize(0) {}
  ~StaticVector() = default;

  void push_back(const T& value) {
    if (currentSize >= MAX_SIZE) {
      throw std::out_of_range("Attempt to exceed static vector capacity.");
    }
    data[currentSize++] = value;
  }

  void pop_back() {
    if (currentSize == 0) {
      throw std::out_of_range("Attempt to pop_back from empty vector.");
    }
    --currentSize;
  }

  void clear() { currentSize = 0; }

  T& at(size_t index) {
    if (index >= currentSize) {
      throw std::out_of_range("Index out of bounds.");
    }
    return data[index];
  }

  T& operator[](size_t index) { return data[index]; }  // non-const version

  const T& operator[](size_t index) const {  // const version
    if (index >= currentSize) {
      throw std::out_of_range("Index out of bounds.");
    }
    return data[index];
  }

  T& front() {
    if (currentSize == 0) {
      throw std::out_of_range("Accessing front from an empty vector.");
    }
    return data[0];
  }

  T& back() {
    if (currentSize == 0) {
      throw std::out_of_range("Accessing back from an empty vector.");
    }
    return data[currentSize - 1];
  }

  bool empty() const { return currentSize == 0; }

  size_t size() const { return currentSize; }

  size_t max_size() const { return MAX_SIZE; }

  iterator begin() { return data; }

  iterator end() { return data + currentSize; }
};

template <typename T, size_t MAX_SIZE>
std::vector<T> ToVector(const StaticVector<T, MAX_SIZE>& sv) {
  std::vector<T> result;
  result.reserve(sv.size());
  for (size_t i = 0; i < sv.size(); ++i) {
    result.push_back(sv[i]);  // now valid for const StaticVector
  }
  return result;
}

}  // namespace cse

#endif  // STATICVECTOR_H