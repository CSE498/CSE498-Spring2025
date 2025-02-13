/* --- BruteForceOptimizer.h --- */

/* ------------------------------------------
Author: Blake Crimmins
Date: 1/31/2025
------------------------------------------ */

#ifndef BRUTEFORCEOPTIMIZER_H
#define BRUTEFORCEOPTIMIZER_H

#include <vector>
#include <utility>


namespace cse {
/**
 * @brief A templated class for exploring possible combinations of items 
 * and identifying an optimal subset based on a scoring (value) function.
 *
 * @tparam T The type of items that will be stored and processed.
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
     * This could represent max weight, max cost, etc.
     *
     * @param cap The max allowed value (like max weight).
     */
    void SetCapacity(double cap)
    {
        capacity_ = cap;
    }

    /**
     * @brief Initiates the brute force or backtracking search to find the best subset.
     *
     * @return A pair: (best score, best subset).
     */
    std::pair<double, std::vector<T>> FindOptimalSolution()
    {
    bestScore_ = -999999;
    currentSelection_.clear();
    Backtrack(0, 0.0);
    return {bestScore_, bestSelection_};
    }

    /**
     * @brief Recursive helper that decides to include or exclude each item.
     * @param index Index of the current item in the items vector.
     * @param currentSum The sum of chosen items so far.
     */
    void Backtrack(size_t index, T currentSum)
    {
        if (index >= items_.size())
        {
            if (currentSum > bestScore_)
            {
                bestScore_ = currentSum;
                bestSelection_ = currentSelection_;
            }
            return;
        }

        // Exclude the current item
        Backtrack(index + 1, currentSum);

        // Include the current item if it fits
        T w = items_[index];
        if (currentSum + w <= capacity_)
        {
            currentSelection_.push_back(w);
            Backtrack(index + 1, currentSum + w);
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
