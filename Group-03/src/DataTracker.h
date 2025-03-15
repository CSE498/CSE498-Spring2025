/** 
* @file DataTracker.h
* @author nigamsa1
* adds or removes data from a vector and provides statistcal data from it
* 
*/

#ifndef DATATRACKER_H
#define DATATRACKER_H

#include <vector>

namespace cse {
class DataTracker {
private:
    std::vector<double> values; //main container

public:
    void add_value(double value);
    bool delete_value(double value);
    double mean() const;
    double median() const;
    double min() const;
    double max() const;
    size_t total() const;
};
} // namespace cse

#endif // DATATRACKER_H