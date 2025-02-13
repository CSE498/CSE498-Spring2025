/*
 * @file AuditedArray.hpp
 * @author Siddhartha Bhattacharya
 */
#ifndef AUDITEDARRAY_H
#define AUDITEDARRAY_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

#ifdef NDEBUG
  template <typename T, size_t N>
  using AuditedArray = std::array<T,N>;
#else


namespace cse{
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
    int indexOf(const T& value) const;
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

  private:
    T data[Size];
  };

  template <typename T, size_t Size>
  AuditedArray<T, Size>::AuditedArray() {
    // Default constructor
    std::fill(begin(), end(), T());
  }

  template <typename T, size_t Size>
  AuditedArray<T, Size>::AuditedArray(const AuditedArray<T, Size>& other) {
    // Copy constructor
    assert (this->size() == other.size()); // Asserting that the sizes are the same
    std::copy(other.begin(), other.end(), begin());
  }

  template <typename T, size_t Size>
  AuditedArray<T, Size>& AuditedArray<T, Size>::operator=(
      const AuditedArray<T, Size>& other) {
    // Assignment operator
    if (this == &other) {
      return *this;
    }
    assert (this->size() == other.size()); // Asserting that the sizes are the same
    std::copy(other.begin(), other.end(), begin());
    return *this;
  }

  template <typename T, size_t Size>
  T& AuditedArray<T, Size>::operator[](int index) {
    int size_int = static_cast<int>(Size);
    if (index < 0 || index >= size_int) { // Throwing an exception if the index is out of range
      throw std::out_of_range("Index out of range");
    }
    return data[index];
  }

  template <typename T, size_t Size>
  const T& AuditedArray<T, Size>::operator[](int index) const {
    if (index < 0 || index >= Size) { // Throwing an exception if the index is out of range
      throw std::out_of_range("Index out of range");
    }
    return data[index];
  }

  template <typename T, size_t Size>
  int AuditedArray<T, Size>::size() const {
    return Size;
  }

  template <typename T, size_t Size>
  void AuditedArray<T, Size>::fill(const T& value) {
    for (size_t i = 0; i < Size; i++) {
      data[i] = value;
    }
  }

  template <typename T, size_t Size>
  bool AuditedArray<T, Size>::contains(const T& value) const {
    for (size_t i = 0; i < Size; i++) {
      if (data[i] == value) {
        return true;
      }
    }
    return false;
  }

  template <typename T, size_t Size>
  int AuditedArray<T, Size>::indexOf(const T& value) const {
    for (size_t i = 0; i < Size; i++) {
      if (data[i] == value) {
        return static_cast<int>(i);
      }
    }
    return -1;
  }

  template <typename T, size_t Size>
  T* AuditedArray<T, Size>::begin() {
    return &data[0];
  }

  template <typename T, size_t Size>
  T* AuditedArray<T, Size>::end() {
    return &data[Size];
  }

  template <typename T, size_t Size>
  const T* AuditedArray<T, Size>::begin() const {
    return &data[0];
  }

  template <typename T, size_t Size>
  const T* AuditedArray<T, Size>::end() const {
    return &data[Size];
  }
}
#endif // NDEBUG
#endif // AUDITEDARRAY_H
