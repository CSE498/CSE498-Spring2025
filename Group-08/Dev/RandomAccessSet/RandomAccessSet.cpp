#include "RandomAccessSet.h"

/**
 * Adds a new unique element to the set.
 * - If the element already exists, it returns false.
 * - Otherwise, it adds the element to both the `elements` vector and `indexMap` for quick lookup.
 */
template <typename T>
bool RandomAccessSet<T>::add(const T& item) {
    if (indexMap.find(item) != indexMap.end()) {
        return false; // Element already exists
    }

    indexMap[item] = elements.size(); // Store index
    elements.push_back(item); // Store element in order
    return true;
}

/**
 * Checks if an element exists in the set.
 * - Uses `indexMap` for O(1) lookup time.
 */
template <typename T>
bool RandomAccessSet<T>::contains(const T& item) const {
    return indexMap.find(item) != indexMap.end();
}

/**
 * Retrieves an element by index.
 * - Throws an error if the index is out of bounds.
 */
template <typename T>
T RandomAccessSet<T>::get(size_t index) const {
    if (index >= elements.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return elements[index];
}

/**
 * Returns the size of the set.
 */
template <typename T>
size_t RandomAccessSet<T>::size() const {
    return elements.size();
}

template <typename T>
size_t RandomAccessSet<T>::getIndexOf(const T& item) const {
    auto it = std::find(elements.begin(), elements.end(), item);

    if (it == elements.end()) {
        throw std::out_of_range("Item not found.");
    }

    return  it - elements.begin();
}


/**
 * Removes an element from the set.
 * - Includes a multiple step process of finding the index in the map, remove it from map, and then elements vector.
 * - Prioritizes runtime by doing a swap instead of a direct delete and reshuffling.
 */
template <typename T>
bool RandomAccessSet<T>::remove(const T& item) {
    auto it = indexMap.find(item);
    
    if (it == indexMap.end()) {
        return false;  // Item not found
    }

    size_t index = it->second;  // Get the index of the item
    size_t lastIndex = elements.size() - 1;  // Last element's index

    if (index != lastIndex) {  // If it's not the last item, swap with the last
        std::swap(elements[index], elements[lastIndex]);  // Swap element with the last
        indexMap[elements[index]] = index;  // Update index in the map
    }

    elements.pop_back();  // Remove last element (which is now the unwanted one)
    indexMap.erase(it);   // Remove from the map

    return true;  // Removal successful
}

