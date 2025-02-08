#include "DataTracker.h"
#include <algorithm>
#include <numeric>

namespace cse {
void DataTracker::add_value(double value) {
    values.push_back(value);
}

void DataTracker::delete_value(double value) {
    auto it = std::find(values.begin(), values.end(), value);
    if (it != values.end()) {
        values.erase(it);
    }
}

double DataTracker::mean() const {
    if (values.empty()) return 0.0;
    return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
}

double DataTracker::median() const {
    if (values.empty()) return 0.0;
    std::vector<double> sorted_values = values;
    std::sort(sorted_values.begin(), sorted_values.end());
    size_t size = sorted_values.size();
    if (size % 2 == 0) {
        return (sorted_values[size / 2 - 1] + sorted_values[size / 2]) / 2.0;
    } else {
        return sorted_values[size / 2];
    }
}

double DataTracker::min() const {
    if (values.empty()) return 0.0;
    return *std::min_element(values.begin(), values.end());
}

double DataTracker::max() const {
    if (values.empty()) return 0.0;
    return *std::max_element(values.begin(), values.end());
}

size_t DataTracker::total() const {
    return values.size();
}
}