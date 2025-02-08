#ifndef RANDOM_ACCESS_SET_H
#define RANDOM_ACCESS_SET_H

#include <vector>
#include <unordered_map>

/**
 * @author Joanna Rodriguez Zamarron
 * @file RandomAccessSet.h
 * 
 * RandomAccessSet: A hybrid data structure combining unique element storage (like a set)
 * with index-based access (like a vector).
 * 
 * Features:
 * - Stores **unique elements** (No duplicates, like a set)
 * - Supports **fast lookup** (Checking if an item exists in O(1) time)
 * - Allows **indexed access** (Like a vector, you can retrieve elements by position)
 * - Provides **efficient removals** (Maintaining order while keeping lookup fast)
 * 
 * Internal Data Structures:
 * - `std::vector<T> elements`: Stores the actual elements in order.
 * - `std::unordered_map<T, size_t> indexMap`: Maps each element to its index in the vector.
 */

template <typename T> // Template class allows RAS to work with any data type
class RandomAccessSet {
private:
    std::vector<T> elements; // Stores the elements in order
    std::unordered_map<T, size_t> indexMap; // Maps element → index in the vector

public:
    // Constructor
    RandomAccessSet() = default;

    // Adds a new unique element to the set
    bool add(const T& item);

    // Checks if an element exists in the set
    bool contains(const T& item) const;

    // Retrieves an element by index
    T get(size_t index) const;

    // Removes an element
    bool remove(const T& item);

    // Returns the size of the set
    size_t size() const;

    // Returns the index if element is known
    size_t getIndexOf(const T& item) const;
};

#include "RandomAccessSet.cpp"
#endif
