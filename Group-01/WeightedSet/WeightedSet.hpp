#pragma once 

#include <vector>

namespace cse498 {
    class WeightedSet {
    private:
        std::vector<size_t> ids;
        std::vector<double> weights;
    public:
        void Add(size_t id, double weight);
        void Remove(size_t id);
        double TotalWeight();
        double Weight(size_t id);
        size_t At(double position);
    };
}
