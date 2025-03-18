/** 
* @file DataTracker.cpp
* @author nigamsa1
* adds or removes data from a vector and provides statistcal data from it
* 
*/

#include "DataTracker.h"
#include <string>
namespace cse {

// Adds a specified value to the vector
template <typename T>
void DataTracker<T>::add_value(const T& value) {
    values.push_back(value);
}

// Removes a value if found, returns true if successful
template <typename T>
bool DataTracker<T>::delete_value(const T& value) {
    auto it = std::find(values.begin(), values.end(), value);
    if (it != values.end()) {
        values.erase(it);
        return true;
    }
    return false;
}

// Calculates and returns the mean 
template <typename T>
double DataTracker<T>::mean() const {
    if (values.empty()) return 0.0;
    if constexpr (std::is_arithmetic_v<T>){
        return static_cast<double>(std::accumulate(values.begin(), values.end(), 0.0)) / values.size();
    }
    else {
        return T();
    }
}

// Calculates and returns the median
template <typename T>
double DataTracker<T>::median() const {
    if (values.empty()) return 0.0;

    std::vector<T> sorted_values = values;
    std::sort(sorted_values.begin(), sorted_values.end());

    size_t size = sorted_values.size();
    if (size % 2 == 0) {
        return (sorted_values[size / 2 - 1] + sorted_values[size / 2]) / 2.0;
    } else {
        return sorted_values[size / 2];
    }
}

// Calculates and returns the mode
template <typename T>
T DataTracker<T>::mode() const {
    if (values.empty()) return T();

    std::unordered_map<T, int> frequency;
    for (const auto& val : values) {
        frequency[val]++;
    }

    auto max_freq = [](const auto& a, const auto& b) { return a.second < b.second; };

    return std::max_element(frequency.begin(), frequency.end(), max_freq)->first;
}
// Calculates and returns the variance
template <typename T>
double DataTracker<T>::variance() const {
    if (values.empty()) return 0.0;
    if constexpr (std::is_arithmetic_v<T>){
        double mean_value = mean();
        double variance_sum = 0.0;

        for (const auto& val : values) {
            variance_sum += std::pow(val - mean_value, 2);
        }

        return variance_sum / values.size();
    }
    else {
        return T();
    }
}

// Returns the minimum value
template <typename T>
T DataTracker<T>::min() const {
    if (values.empty()) return T();
    if constexpr (std::is_arithmetic_v<T>){
        return *std::min_element(values.begin(), values.end());
    }
    else return T();
}

// Returns the maximum value
template <typename T>
T DataTracker<T>::max() const {
    if (values.empty()) return T();
    if constexpr (std::is_arithmetic_v<T>){
        return *std::max_element(values.begin(), values.end());
    }
    else{
        return T();
    }
}

// Returns the total number of elements
template <typename T>
size_t DataTracker<T>::total() const {
    return values.size();
}

// Determines if there is a winner (if any value surpasses 80% of total)
template <typename T>
std::optional<T> DataTracker<T>::winner() const {
    if (values.empty()) return false;

    std::unordered_map<T, int> frequency;
    size_t threshold = static_cast<size_t>(values.size() * 0.8);

    for (const auto& val : values) {
        if (++frequency[val] > threshold) return val;
    }

    return false;
}

template class DataTracker<int>;
template class DataTracker<double>;
} // namespace cse