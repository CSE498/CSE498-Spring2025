/**
 * @file ReferenceVector.cpp
 *
 * @author Calen Green
 */

#include "ReferenceVector.h"

namespace cse {

/**
 * Removes the last element from the vector.
 */
void ReferenceVector::pop_back() {
  if (!mData.empty())
    mData.pop_back();
}

/**
 * Removes an element at a specified index.
 *
 * @param index The position of the element to remove.
 */
void ReferenceVector::erase(size_t index) {
  if (index >= mData.size()) {
    throw std::out_of_range("Index out of range");
  }
  mData.erase(mData.begin() + index);
}

/**
 * Accesses a Datum at the given index.
 *
 * @param index The position of the element.
 * @return Datum& Reference to the Datum.
 */
Datum &ReferenceVector::operator[](size_t index) {
  if (index >= mData.size())
    throw std::out_of_range("Index out of range");
  return *mData[index];
}

/**
 * Returns a reference to the Datum at a position.
 *
 * @param index The index of the desired element.
 * @return Datum& Reference to the Datum.
 */
Datum &ReferenceVector::at(size_t index) {
  if (index >= mData.size())
    throw std::out_of_range("Index out of range");
  return *mData[index];
}

/**
 * Returns a reference to the first Datum in the vector.
 *
 * @return Datum& Reference to the first Datum.
 */
Datum &ReferenceVector::front() {
  if (mData.empty())
    throw std::out_of_range("ReferenceVector is empty");
  return *mData.front();
}

/**
 * Returns a reference to the last Datum in the vector.
 *
 * @return Datum& Reference to the last Datum.
 */
Datum &ReferenceVector::back() {
  if (mData.empty())
    throw std::out_of_range("ReferenceVector is empty");
  return *mData.back();
}

} // namespace cse
