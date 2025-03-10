/* --- BruteForceOptimizer.h --- */

/* ------------------------------------------
Author: Blake Crimmins
Date: 1/31/2025
------------------------------------------ */

#ifndef BRUTEFORCEOPTIMIZER_H
#define BRUTEFORCEOPTIMIZER_H

#include <vector>
#include <utility>
#include <string>

namespace cse {


/**
 * @brief Structure representing an item with a name, weight, and value.
 */
struct Item {
    std::string name;
    double weight;   
    double value;      
};

/**
 * @brief A templated class for exploring possible combinations of items 
 * and identifying an optimal subset based on a scoring (value) function.
 *
 * Each item is defined by its name, weight, and value.
 */
template <typename T>
class BruteForceOptimizer
{
public:

    /**
     * @brief Default constructor for BruteForceOptimizer.
     */
    BruteForceOptimizer() = default;

    /**
     * @brief Stores the list of items in the optimizer.
     *
     * @param newItems The vector of items to manage.
     */
    void SetItems(const std::vector<T>& newItems)
    {
        items_ = newItems;
    }

    /**
     * @brief Sets a capacity/threshold.
     * This represents the maximum allowed weight.
     *
     * @param cap The maximum allowed weight.
     */
    void SetCapacity(double cap)
    {
        capacity_ = cap;
    }

    /**
     * @brief Initiates the brute force/backtracking search to find the best subset.
     *
     * @return A pair containing the best total value and the corresponding subset of items.
     */
    std::pair<double, std::vector<Item>> FindOptimalSolution()
    {
        bestScore_ = -999999;
        currentSelection_.clear();
        Backtrack(0, 0.0, 0.0);
        return {bestScore_, bestSelection_};
    }

    /**
     * @brief Recursive helper that decides to include or exclude each item.
     *
     * @param index Index of the current item in the items vector.
     * @param currentWeight The total weight of the selected items so far.
     * @param currentValue The total value of the selected items so far.
     */
    void Backtrack(size_t index, double currentWeight, double currentValue)
    {
        if (index >= items_.size())
        {
            if (currentWeight <= capacity_ && currentValue > bestScore_)
            {
                bestScore_ = currentValue;
                bestSelection_ = currentSelection_;
            }
            return;
        }

        // Exclude the current item.
        Backtrack(index + 1, currentWeight, currentValue);
        // Include the current item if it does not exceed capacity.
        const Item& item = items_[index];
        if (currentWeight + item.weight <= capacity_)
        {
            currentSelection_.push_back(item);
            Backtrack(index + 1, currentWeight + item.weight, currentValue + item.value);
            currentSelection_.pop_back();
        }
    }

private:
    
    std::vector<T> items_;
    double capacity_;
    double bestScore_;
    std::vector<T> bestSelection_;
    std::vector<T> currentSelection_;
};

} // namespace cse

#endif // BRUTEFORCEOPTIMIZER_H
