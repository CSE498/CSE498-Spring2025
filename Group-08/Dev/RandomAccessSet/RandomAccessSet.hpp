#ifndef CSE_RANDOM_ACCESS_SET_H
#define CSE_RANDOM_ACCESS_SET_H

#include <vector>
#include <unordered_map>
// for std::out_of_range
#include <stdexcept>

namespace cse {

/**
 * @class RandomAccessSet
 * @brief A hybrid data structure combining unique element storage (like a set)
 *        with index-based access (like a vector).
 *
 * @tparam T Type of elements stored in the set.
 *
 * This class maintains a collection of unique elements, supporting O(1) average-time
 * lookups and efficient removals. It also allows indexed access to elements.
 *
 * Internally:
 * - A `std::vector<T>` to store elements in order.
 * - A `std::unordered_map<T, size_t>` mapping each element to its index in the vector.
 */

template <typename T> // Template class allows RAS to work with any data type
class RandomAccessSet {
    private:
        /**
        * @brief Stores the elements in sequential order.
        */
        std::vector<T> mElements;

        /**
        * @brief Maps each element to its index in mElements.
        */
        std::unordered_map<T, size_t> mIndexMap;

    public:
        /**
        * @brief Default constructor, Initializes an empty RandomAccessSet.
        */
        RandomAccessSet() = default;

        /**
         * @brief Adds a new unique element to the set.
         * @param item The element to add.
         * @return True if the element was added (not already present),
         *         false if the element already exists.
         */
        bool add(const T& item);

        /**
         * @brief Checks if an element exists in the set.
         * @param item The element to look for.
         * @return True if the element is found, false otherwise.
         */
        bool contains(const T& item) const;

        /**
         * @brief Retrieves an element by index.
         * @param index The index of the element to retrieve.
         * @return A copy of the element at the specified index.
         * @throw std::out_of_range If the index is greater than or equal to the number of elements.
         */
        T get(size_t index) const;

        /**
         * @brief Removes an element from the set if it exists.
         * @param item The element to remove.
         * @return True if the element was removed, false if the element was not found.
         *
         * Swaps the removed element with the last element in the internal vector (if it
         * isn't already the last) to maintain O(1) complexity, then pops it off.
         */
        bool remove(const T& item);

        /**
         * @brief Returns the number of elements stored in the set.
         * @return The number of elements in the set.
         */
        size_t size() const;

        /**
         * @brief Retrieves the index of a specified element.
         * @param item The element whose index is requested.
         * @return The index of the element in the underlying vector.
         * @throw std::out_of_range If the element is not found in the set.
         */
        size_t getIndexOf(const T& item) const;
};

/************************************
 * Template Method Implementations
 ************************************/

template <typename T>
bool RandomAccessSet<T>::add(const T& item) {
    if (mIndexMap.find(item) != mIndexMap.end()) {
        return false; // Element already exists
    }

    mIndexMap[item] = mElements.size(); // Store index
    mElements.push_back(item);
    return true;
}

template <typename T>
bool RandomAccessSet<T>::contains(const T& item) const {
    return mIndexMap.find(item) != mIndexMap.end();
}

template <typename T>
T RandomAccessSet<T>::get(size_t index) const {
    if (index >= mElements.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return mElements[index];
}

template <typename T>
bool RandomAccessSet<T>::remove(const T& item) {
    auto it = mIndexMap.find(item);

    if (it == mIndexMap.end()) {
        return false;  // Item not found
    }

    size_t index = it->second;  // Get the index of the item
    size_t lastIndex = mElements.size() - 1;  // Last element's index

    if (index != lastIndex) {  // If it's not the last item, swap with the last
        std::swap(mElements[index], mElements[lastIndex]);  // Swap element with the last
        mIndexMap[mElements[index]] = index;  // Update index in the map
    }

    mElements.pop_back();  // Remove last element (which is now the unwanted one)
    mIndexMap.erase(it);   // Remove from the map

    return true;  // Removal successful
}

template <typename T>
size_t RandomAccessSet<T>::size() const {
    return mElements.size();
}

template <typename T>
size_t RandomAccessSet<T>::getIndexOf(const T& item) const {
    auto it = mIndexMap.find(item); // Uses the find method for an O(1) search time and retrieves index IA (hash-map lookup)

    if (it == mIndexMap.end()) {
        throw std::out_of_range("Item not found.");
    }

    return it->second; // Returns the index, which is the value from the map from mIndexMap
}
}

#endif