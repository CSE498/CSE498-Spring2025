/* --- MemoFunction.h --- */

/* ------------------------------------------
Author: Team Bellman - Ephraim
Date: 1/31/2025
------------------------------------------ */

#ifndef MEMOFUNCTION_H
#define MEMOFUNCTION_H

#include <functional>
#include <unordered_map>
#include <memory>

/**
 * @brief MemoFunction class, is a wrapper class that does memoization.
 * 
 * This class caches the results of a given function to an unordered_map, based on the input parameters. If the same
 * parameters are called more than once, the cached result is returned instead of recalculating the function, 
 * improving performance.
 * 
 * All function definitions will be in the header since this is a templated class.
 */

template<typename Input, typename Output>
class MemoFunction {
 public:

  /**
   * @param func - the function we are going to wrap around.
   */
  explicit MemoFunction(std::function<Output(Input)> func) : func_(func) {}

  /* Default Destructor */
  ~MemoFunction() = default;
  
  /**
   * Calls the wrapped function with memoization
   * 
   * @param input the input parameter
   * @return the output of the function either cached or computed.
   */
  Output operator()(const Input & input) const {
    auto it = cache_.find(input);
    if (it != cache_.end()) {
      return it->second;
    }

    Output res = func_(input);
    cache_[input] = res;
    return res;
  }

  /* Clears the cache. */
  void clearCache() {
    cache_.clear();
  }

  /**
   * @return the size of our cache
   */
  size_t cacheSize() const {return cache_.size();}



 private:
  std::function<Output(Input)> func_;
  mutable std::unordered_map<Input, Output> cache_;
};

#endif  // MEMOFUNCTION_H
