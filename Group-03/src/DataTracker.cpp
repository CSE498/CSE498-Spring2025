/** 
* @file DataTracker.cpp
* @author nigamsa1
* adds or removes data from a vector and provides statistcal data from it
* 
*/

#include "DataTracker.h" 
#include <algorithm>
#include <numeric>
#include <cassert>

namespace cse {

// Adds a specified value to the vector
void DataTracker::add_value(double value) {
    size_t old_size = values.size();
    values.push_back(value);

    // Assertion to ensure the size of the vector increased by one after insertion
    assert(values.size() == old_size + 1 && "Size did not increase by one");
}

// Finds a specified value and deletes the first instance of it, returning true if successful
bool DataTracker::delete_value(double value) {
    size_t old_size = values.size();
    
    // Find the first occurrence of the value in the vector
    auto it = std::find(values.begin(), values.end(), value);
    
    // If found, erase the element and return true
    if (it != values.end()) {
        values.erase(it);
        assert(values.size() < old_size && "Size should decrease after deletion");
        return true;
    }

    // Return false if the value was not found
    return false;
}


// Calculates and returns the average (mean) of the data in the object
double DataTracker::mean() const {
    if (values.empty()) return 0.0; // Return 0.0 if no elements exist

    // Compute the mean using std::accumulate
    double mean = std::accumulate(values.begin(), values.end(), 0.0) / values.size();

    // Assertion to ensure the mean lies between min and max values
    assert(mean >= min() && mean <= max() && "Mean should be within the range.");

    return mean;
}

// Sorts the vector and returns the median value
double DataTracker::median() const {
    if (values.empty()) return 0.0; // Return 0.0 if no elements exist

    // Create a copy of the vector and sort it
    std::vector<double> sorted_values = values;
    std::sort(sorted_values.begin(), sorted_values.end());

    size_t size = sorted_values.size();
    
    if (size % 2 == 0) {
        // If the size of the vector is even, return the average of the two middle numbers
        return (sorted_values[size / 2 - 1] + sorted_values[size / 2]) / 2.0;
    } else {
        // If the size of the vector is odd, return the middle value
        return sorted_values[size / 2];
    }
}

// Returns the minimum value in the dataset
double DataTracker::min() const {
    if (values.empty()) return 0.0; // Return 0.0 if no elements exist
    
    // Get the minimum element in the vector
    double min = *std::min_element(values.begin(), values.end());

    // Assertion to ensure that the minimum value is truly the smallest
    assert(std::all_of(values.begin(), values.end(), [&](double v) { return v >= min; }) && 
           "Min value is not actually the minimum.");

    return min;
}

// Returns the maximum value in the dataset
double DataTracker::max() const {
    if (values.empty()) return 0.0; // Return 0.0 if no elements exist

    // Get the maximum element in the vector
    double max = *std::max_element(values.begin(), values.end());

    // Assertion to ensure that the maximum value is truly the largest
    assert(std::all_of(values.begin(), values.end(), [&](double v) { return v <= max; }) && 
           "Max value is not actually the maximum.");

    return max;
}

// Returns the total number of elements in the dataset
size_t DataTracker::total() const {
    return values.size();
}

} // namespace cse
