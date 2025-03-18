/** 
* @file DataTracker.h
* @author nigamsa1
* adds or removes data from a vector and provides statistcal data from it
* 
*/

#ifndef DATATRACKER_H
#define DATATRACKER_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cassert>
#include <optional>

namespace cse {

template <typename T>
class DataTracker {
public:
    void add_value(const T& value);
    bool delete_value(const T& value);

    double mean() const;
    double median() const;
    T mode() const;
    double variance() const;
    T min() const;
    T max() const;
    size_t total() const;

    std::optional<T> winner() const;

private:
    std::vector<T> values;
};

} // namespace cse
#endif