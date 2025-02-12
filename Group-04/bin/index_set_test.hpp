#include <cassert>
#include <iostream>

#include "IndexSet.hpp"

// Helper function to print test results
void print_test_result(const char* test_name, bool passed) {
  std::cout << test_name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

// Test basic operations
void test_basic_operations() {
  cse::IndexSet set;

  // Test initial state
  assert(set.size() == 0);
  assert(!set.contains(0));
  print_test_result("Initial state", true);

  // Test single insert
  set.insert(5);
  assert(set.size() == 1);
  assert(set.contains(5));
  assert(!set.contains(4));
  assert(!set.contains(6));
  print_test_result("Single insert", true);

  // Test single remove
  set.remove(5);
  assert(set.size() == 0);
  assert(!set.contains(5));
  print_test_result("Single remove", true);
}

// Test range operations
void test_range_operations() {
  cse::IndexSet set;

  // Insert consecutive numbers
  for (size_t i = 5; i < 10; ++i) {
    set.insert(i);
  }

  // Test range creation
  assert(set.size() == 5);
  auto range = set.getContainingRange(7);
  assert(range.has_value());
  assert(range->first == 5);
  assert(range->second == 10);
  print_test_result("Range creation", true);

  // Test range queries
  auto next_range = set.getNextRange(4);
  assert(next_range.has_value());
  assert(next_range->first == 5);
  assert(next_range->second == 10);

  auto prev_range = set.getPrevRange(12);
  assert(prev_range.has_value());
  assert(prev_range->first == 5);
  assert(prev_range->second == 10);
  print_test_result("Range queries", true);

  // Test getAllIndices
  auto indices = set.getAllIndices();
  assert(indices.size() == 5);
  for (size_t i = 0; i < indices.size(); ++i) {
    assert(indices[i] == i + 5);
  }
  print_test_result("Get all indices", true);
}

// Test range merging
void test_range_merging() {
  cse::IndexSet set;

  // Insert non-consecutive ranges
  set.insert(1);
  set.insert(2);
  set.insert(4);
  set.insert(5);
  set.insert(3);  // This should merge all into one range

  assert(set.size() == 5);
  auto range = set.getContainingRange(3);
  assert(range.has_value());
  assert(range->first == 1);
  assert(range->second == 6);
  print_test_result("Range merging", true);
}

// Test range splitting
void test_range_splitting() {
  cse::IndexSet set;

  // Create a range and split it
  for (size_t i = 1; i <= 5; ++i) {
    set.insert(i);
  }

  set.remove(3);
  assert(set.size() == 4);
  assert(!set.contains(3));

  auto first_range = set.getContainingRange(2);
  auto second_range = set.getContainingRange(4);
  assert(first_range.has_value());
  assert(second_range.has_value());
  assert(first_range->first == 1);
  assert(first_range->second == 3);
  assert(second_range->first == 4);
  assert(second_range->second == 6);
  print_test_result("Range splitting", true);
}

int index_set_test() {
  std::cout << "Running IndexSet tests...\n\n";

  test_basic_operations();
  test_range_operations();
  test_range_merging();
  test_range_splitting();

  std::cout << "\nAll tests completed!\n";
  return 0;
}
