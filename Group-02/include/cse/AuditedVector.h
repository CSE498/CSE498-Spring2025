/**
 * @file AuditedVector.h
 * @author Matthew Hawkins
 */

#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

namespace cse {

#ifdef NDEBUG
// In release mode, just use std::vector.
template <typename T, typename Allocator = std::allocator<T>>
using AuditedVector = std::vector<T, Allocator>;

#else
template <typename T, typename Allocator = std::allocator<T>>
class AuditedVector : public std::vector<T, Allocator> {
 public:
  // Create a type alias
  using base_t = std::vector<T, Allocator>;
  // Inherit all functions without having to manually re-define
  using base_t::base_t;

  T& operator[](size_t index) {
    assert(index < this->size() && "cse::vector: index out of range");
    return base_t::operator[](index);
  }

  const T& operator[](size_t index) const {
    assert(index < this->size() && "cse::vector: index out of range (const)");
    return base_t::operator[](index);
  }

  T& front() {
    assert(!this->empty() && "cse::vector: front() called on empty vector");
    return base_t::front();
  }

  const T& front() const {
    assert(!this->empty() && "cse::vector: front() called on empty vector (const)");
    return base_t::front();
  }

  T& back() {
    assert(!this->empty() && "cse::vector: back() called on empty vector");
    return base_t::back();
  }

  const T& back() const {
    assert(!this->empty() && "cse::vector: back() called on empty vector (const)");
    return base_t::back();
  }

  void pop_back() {
    assert(!this->empty() && "cse::vector: pop_back() called on empty vector");
    base_t::pop_back();
  }
};

#endif  // NDEBUG

}  // namespace cse

