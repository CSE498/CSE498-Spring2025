/*
 * @file AuditedArray.hpp
 * @author Siddhartha Bhattacharya
 */
#ifndef AUDITEDARRAY_H
#define AUDITEDARRAY_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>
#include <stdexcept>

#if defined(NDEBUG) || !defined(AUDIT)
template <typename T, size_t N>
using AuditedArray = std::array<T, N>;
#else // NDEBUG

namespace cse {
template <typename T, size_t Size>
class AuditedArray {
 public:
  AuditedArray();
  AuditedArray(const AuditedArray<T, Size>& other);

  ~AuditedArray() = default;
  AuditedArray<T, Size>& operator=(const AuditedArray<T, Size>& other);
  T& operator[](int index);
  const T& operator[](int index) const;
  int size() const;
  void fill(const T& value);
  bool contains(const T& value) const;
  bool isValidIndex(int index) const;
  int indexOf(const T& value) const;
  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

 private:
  T arrayData[Size];
};

template <typename T, size_t Size>
AuditedArray<T, Size>::AuditedArray() {
  /**
   * Default constructor
   * Initializes all elements to default values of type T
   */
  std::fill(begin(), end(), T());
}

template <typename T, size_t Size>
AuditedArray<T, Size>::AuditedArray(const AuditedArray<T, Size>& other) {
  /**
   * Copy constructor
   * @param other: Another AuditedArray to copy from
   */
  assert(this->size() == other.size());
  std::copy(other.begin(), other.end(), begin());
}

template <typename T, size_t Size>
AuditedArray<T, Size>& AuditedArray<T, Size>::operator=(
    const AuditedArray<T, Size>& other) {
  /**
   * Copy assignment operator
   * @param other: Another AuditedArray to assign from
   * @return: Reference to the assigned AuditedArray
   */
  if (this == &other) {
    return *this;
  }
  assert(this->size() == other.size());
  std::copy(other.begin(), other.end(), begin());
  return *this;
}

template <typename T, size_t Size>
T& AuditedArray<T, Size>::operator[](int index) {
  /**
   * Overloaded [] operator to access elements
   * @param index: The index of the element to access
   * @return: Reference to the element at the index
   */
  if (!isValidIndex(index)) {
    throw std::out_of_range("Index out of range");
  }
  return arrayData[index];
}

template <typename T, size_t Size>
const T& AuditedArray<T, Size>::operator[](int index) const {
  /**
   * Overloaded [] operator for const objects
   * @param index: The index of the element to access
   * @return: Const reference to the element at the index
   */
  if (!isValidIndex(index)) {
    throw std::out_of_range("Index out of range");
  }
  return arrayData[index];
}

template <typename T, size_t Size>
int AuditedArray<T, Size>::size() const {
  /**
   * Returns the size of the array
   * @return: Integer representing the size of the array
   */
  return Size;
}

template <typename T, size_t Size>
void AuditedArray<T, Size>::fill(const T& value) {
  /**
   * Fills the array with a specified value
   * @param value: The value to fill the array with
   */
  std::fill(begin(), end(), value);
}

template <typename T, size_t Size>
bool AuditedArray<T, Size>::contains(const T& value) const {
  /**
   * Checks if the array contains a specific value
   * @param value: The value to check for
   * @return: True if the value is found, false otherwise
   */
  return std::find(begin(), end(), value) != end();
}

template <typename T, size_t Size>
bool AuditedArray<T, Size>::isValidIndex(int index) const {
  /**
   * Checks if an index is valid
   * @param index: The index to check
   * @return: True if the index is within range, false otherwise
   */
  return index >= 0 && index < static_cast<int>(Size);
}

template <typename T, size_t Size>
int AuditedArray<T, Size>::indexOf(const T& value) const {
  /**
   * Finds the index of a specific value
   * @param value: The value to find
   * @return: The index of the value if found, -1 otherwise
   */
  auto it = std::find(begin(), end(), value);
  return (it != end()) ? std::distance(begin(), it) : -1;
}

template <typename T, size_t Size>
T* AuditedArray<T, Size>::begin() {
  /**
   * Returns an iterator to the beginning of the array
   * @return: Pointer to the first element
   */
  return &arrayData[0];
}

template <typename T, size_t Size>
T* AuditedArray<T, Size>::end() {
  /**
   * Returns an iterator to the end of the array
   * @return: Pointer to one past the last element
   */
  return &arrayData[Size];
}

template <typename T, size_t Size>
const T* AuditedArray<T, Size>::begin() const {
  /**
   * Returns a const iterator to the beginning of the array
   * @return: Const pointer to the first element
   */
  return &arrayData[0];
}

template <typename T, size_t Size>
const T* AuditedArray<T, Size>::end() const {
  /**
   * Returns a const iterator to the end of the array
   * @return: Const pointer to one past the last element
   */
  return &arrayData[Size];
}

}  // namespace cse
#endif  // NDEBUG
#endif  // AUDITEDARRAY_H
