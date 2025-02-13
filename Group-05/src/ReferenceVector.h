/**
 * @file ReferenceVector.h
 *
 * @author Calen Green
 *
 * A vector class that keeps pointers to Datum instances under the hood.
 */

#pragma once

#include "Datum.h"
#include <memory>
#include <stdexcept>
#include <vector>

namespace cse {

class ReferenceVector {
private:
  /// Stores pointers to Datum instances.
  std::vector<Datum *> mData;

public:
  /**
   * Default constructor for ReferenceVector.
   */
  ReferenceVector() = default;

  /**
   * Pushes a Datum reference into the vector.
   *
   * @param datum The reference to a Datum.
   */
  void push_back(Datum &datum) { mData.push_back(&datum); }

  /**
   * Removes the last element in the vector.
   */
  void pop_back();

  /**
   * Removes an element at a specified index.
   *
   * @param index The position of the element to remove.
   */
  void erase(size_t index);

  /**
   * Returns the number of elements in the vector.
   *
   * @return size_t The size of the vector.
   */
  size_t size() const { return mData.size(); }

  /**
   * Checks if the vector is empty.
   *
   * @return bool True if empty, otherwise false.
   */
  bool empty() const { return mData.empty(); }

  /**
   * Clears all elements from the vector.
   */
  void clear() { mData.clear(); }

  /**
   * Accesses a Datum reference at the given index.
   *
   * @param index The position of the element.
   * @return Datum& Reference to the Datum at the index.
   */
  Datum &operator[](size_t index);

  /**
   * Returns a reference to the Datum at the given index.
   *
   * @param index The index of the desired element.
   * @return Datum& Reference to the Datum.
   */
  Datum &at(size_t index);

  /**
   * Returns a reference to the first Datum in the vector.
   *
   * @return Datum& Reference to the first Datum.
   */
  Datum &front();

  /**
   * Returns a reference to the last Datum in the vector.
   *
   * @return Datum& Reference to the last Datum.
   */
  Datum &back();

  class iterator {
  private:
    std::vector<Datum *>::iterator it_;

  public:
    explicit iterator(std::vector<Datum *>::iterator it) : it_(it) {}

    Datum &operator*() const { return **it_; }

    Datum *operator->() const { return *it_; }

    iterator &operator++() {
      ++it_;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const iterator &other) const { return it_ == other.it_; }
    bool operator!=(const iterator &other) const { return it_ != other.it_; }
  };

  /**
   * Returns an iterator to the beginning of the reference vector.
   *
   * @return std::vector<Datum*>::iterator An iterator pointing to the first
   * element.
   */
  iterator begin() { return iterator(mData.begin()); }

  /**
   * Returns an iterator to the end of the reference vector.
   *
   * @return std::vector<Datum*>::iterator An iterator pointing past the last
   * element.
   */
  iterator end() { return iterator(mData.end()); }
};

} // namespace cse
