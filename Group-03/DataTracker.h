#ifndef DATATRACKER_H
#define DATATRACKER_H

#include <vector>

namespace cse {
class DataTracker {
private:
    std::vector<double> values;

public:
    void add_value(double value);
    void delete_value(double value);
    double mean() const;
    double median() const;
    double min() const;
    double max() const;
    size_t total() const;
};
}
#endif // DATATRACKER_H