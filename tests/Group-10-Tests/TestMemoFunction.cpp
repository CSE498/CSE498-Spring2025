#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../Group-10/Classes/MemoFunction.h"

int addFive(int a) {
  return a + 5;
}

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


TEST_CASE("MemoFunction", "[MemoFunction]") {

  SECTION("Constructor and cache Size") {
    // Test constructor with function name
    cse::MemoFunction<int, int> myFunc(addFive);
    REQUIRE(myFunc.cacheSize() == 0);
  }

  SECTION("Operator () Functionality") {
    cse::MemoFunction<int, int> myFunc(addFive);
    // Test basic functionality
    int result1 = myFunc(0);
    REQUIRE(result1 == 5);
    REQUIRE(myFunc.cacheSize() == 1);
  }

  SECTION("Performance Boost") {
    // Test performance boosts with fibbonacci sequence ~ O(2^N)
    //
    // Create a memoized version of Fibonacci
    cse::MemoFunction<int, int> fibbonacci([](int n) {
      if (n <= 1) return n;
      return recursiveFib(n - 1) + recursiveFib(n - 2);
    });

    //calculate large fibbonacci value twice. The time taken for the second must be smaller than the first
    int testValue = 40;
    double time1 = measureTime([&]() {  
      fibbonacci(testValue); 
    });
    double time2 = measureTime([&](){
      fibbonacci(testValue);
    });
    REQUIRE(time2 < time1);
  }

  SECTION("Clearing Cache") {
    cse::MemoFunction<int, int> fibbonacci([](int n) {
      if (n <= 1) return n;
      return recursiveFib(n - 1) + recursiveFib(n - 2);
    });

    
    //calculate large fibbonacci value twice. The time taken for the second must be smaller than the first
    int testValue = 35;
    double time1 = measureTime([&]() {  
      fibbonacci(testValue); 
    });
    double time2 = measureTime([&](){
      fibbonacci(testValue);
    });
    REQUIRE(time2 < time1);

    fibbonacci(3);
    fibbonacci(4);
    
    //cache size must be three
    REQUIRE(fibbonacci.cacheSize() == 3);

    //clear the cache, size must be zero now
    fibbonacci.clearCache();
    REQUIRE(fibbonacci.cacheSize() == 0);
  }
}