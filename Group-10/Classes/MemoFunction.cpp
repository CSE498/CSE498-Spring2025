/* --- MemoFunction.cpp --- */

/* ------------------------------------------
Author: Bellman - Ephraim
date: 1/31/2025
------------------------------------------ */

#include "MemoFunction.h"

#include <chrono>
#include <iomanip>
#include <iostream>

int recursiveFib(int n) {
  if (n <= 1) return n;
  return recursiveFib(n - 1) + recursiveFib(n - 2);
}

// Utility function to measure execution time
template <typename Func>
double measureTime(Func&& func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration<double, std::milli>(end - start).count();
}

void testPerformance() {
  // Create a memoized version of Fibonacci
  MemoFunction<int, int> memoFib([](int n) {
    if (n <= 1) return n;
    return recursiveFib(n - 1) + recursiveFib(n - 2);
  });

  std::cout << "Fibonacci Calculation Demo:\n";
  std::cout << "=========================\n\n";

  // Test with Fibonacci numbers
  const int testValue = 41;

  // First run - no memoization
  std::cout << "Computing Fibonacci(" << testValue << ") first time...\n";
  double time1 = measureTime(
      [&]() { std::cout << "Result: " << memoFib(testValue) << "\n"; });
  std::cout << "Time taken: " << std::fixed << std::setprecision(2) << time1
            << "ms\n\n";

  // Second run - with memoization
  std::cout << "Computing Fibonacci(" << testValue << ") second time...\n";
  double time2 = measureTime(
      [&]() { std::cout << "Result: " << memoFib(testValue) << "\n"; });
  std::cout << "Time taken: " << time2 << "ms\n";
  std::cout << "Speed improvement: " << std::fixed << std::setprecision(1)
            << (time1 / time2) << "x faster\n\n";
}