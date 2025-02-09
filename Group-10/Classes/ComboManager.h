/* --- ComboManager.h --- */

/* ------------------------------------------
Author: Team Bellman - Amery Johnson
Date: 02/07/2025
------------------------------------------ */

#ifndef COMBOMANAGER_H
#define COMBOMANAGER_H

#include <vector>
#include <cstddef>
#include <stdexcept>
#include <iterator>

/**
 * @brief ComboManager class template.
 *
 * This class manages combinations of items from a container. It allows stepping
 * through combinations in lexicographical order via NextCombo() and PrevCombo().
 * The initial combination is available immediately after construction or Reset().
 *
 * Template parameter:
 *   Container - the type of the container holding the items.
 */
template <typename Container>
class ComboManager {
 public:
  /// The type of elements stored in the container.
  using ValueType = typename Container::value_type;

  /**
   * @brief Constructs a ComboManager.
   *
   * @param container The container of items.
   * @param combination_size The number of items per combination.
   * @throws std::invalid_argument if combination_size is greater than the number of items.
   */
  ComboManager(const Container &container, std::size_t combination_size)
      : items_(std::begin(container), std::end(container)),
        n_(items_.size()),
        k_(combination_size),
        total_combinations_(0) {
    if (k_ > n_) {
      throw std::invalid_argument("Combination size cannot be greater than the number of items in the container.");
    }
    // Precompute the total number of combinations.
    total_combinations_ = BinomialCoefficient(n_, k_);
    // Initialize indices to the first combination: [0, 1, 2, ..., k_-1].
    indices_.resize(k_);
    for (std::size_t i = 0; i < k_; ++i) {
      indices_[i] = i;
    }
  }

  /**
   * @brief Resets the combination to the first combination.
   */
  void Reset() {
    for (std::size_t i = 0; i < k_; ++i) {
      indices_[i] = i;
    }
  }

  /**
   * @brief Returns the current combination as a vector of items.
   *
   * @return A vector containing the current combination.
   */
  std::vector<ValueType> GetCurrentCombo() const {
    std::vector<ValueType> combo;
    combo.reserve(k_);
    for (std::size_t index : indices_) {
      combo.push_back(items_[index]);
    }
    return combo;
  }

  /**
   * @brief Advances to the next combination.
   *
   * @return true if the next combination was generated, false if no further combination exists.
   */
  bool NextCombo() {
    // Find the rightmost index that can be incremented.
    int i = static_cast<int>(k_) - 1;
    while (i >= 0 && indices_[i] == i + n_ - k_) {
      --i;
    }
    // If no valid index is found, we have reached the final combination.
    if (i < 0) {
      return false;
    }
    // Increment the found index.
    ++indices_[i];
    // Update all subsequent indices.
    for (std::size_t j = i + 1; j < k_; ++j) {
      indices_[j] = indices_[j - 1] + 1;
    }
    return true;
  }

  /**
   * @brief Moves to the previous combination.
   *
   * @return true if the previous combination was generated, false if already at the first combination.
   */
  bool PrevCombo() {
    // Check if the current combination is the first one.
    bool isFirst = true;
    for (std::size_t i = 0; i < k_; ++i) {
      if (indices_[i] != i) {
        isFirst = false;
        break;
      }
    }
    if (isFirst) {
      return false;
    }
    // Find the rightmost index that can be decremented.
    int i = static_cast<int>(k_) - 1;
    while (i >= 0) {
      std::size_t min_value = (i == 0) ? 0 : (indices_[i - 1] + 1);
      if (indices_[i] > min_value) {
        break;
      }
      --i;
    }
    if (i < 0) {
      return false;
    }
    // Decrement the found index.
    --indices_[i];
    // Update all subsequent indices.
    for (std::size_t j = i + 1; j < k_; ++j) {
      indices_[j] = indices_[j - 1] + 1;
    }
    return true;
  }

  /**
   * @brief Returns the total number of possible combinations.
   *
   * @return The total number of combinations (n choose k).
   */
  unsigned long long TotalCombinations() const { return total_combinations_; }

  /**
   * @brief (Optional) Returns the current combination indices.
   *
   * @return A vector of indices representing the current combination.
   */
  std::vector<std::size_t> GetCurrentIndices() const { return indices_; }

 private:
  /**
   * @brief Computes the binomial coefficient "n choose k".
   *
   * @param n Total number of items.
   * @param k Number of items per combination.
   * @return The binomial coefficient.
   */
  static unsigned long long BinomialCoefficient(std::size_t n, std::size_t k) {
    if (k > n) {
      return 0;
    }
    if (k == 0 || k == n) {
      return 1;
    }
    // Use symmetry: C(n, k) == C(n, n - k)
    if (k > n - k) {
      k = n - k;
    }
    unsigned long long result = 1;
    for (std::size_t i = 1; i <= k; ++i) {
      result *= n - k + i;
      result /= i;
    }
    return result;
  }

  // Container items stored in a vector for random access.
  std::vector<ValueType> items_;

  // Total number of items.
  std::size_t n_;

  // Number of items per combination.
  std::size_t k_;

  // The current combination, stored as indices into items_.
  std::vector<std::size_t> indices_;

  // Precomputed total number of combinations.
  unsigned long long total_combinations_;
};

#endif  // COMBOMANAGER_H