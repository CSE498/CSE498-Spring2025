#include "IndexSet.hpp"

#include <vector>

#include "catch.hpp"

// Test constructor and size calculation
TEST_CASE("Constructor", "[IndexSetTest]") {
  cse::IndexSet set1(0, 5);  // [0,5)
  REQUIRE(set1.size() == 5);

  cse::IndexSet set2(10, 15);  // [10,15)
  REQUIRE(set2.size() == 5);

  // Empty range
  cse::IndexSet set3(3, 3);  // [3,3)
  REQUIRE(set3.size() == 0);
}

// Test insert_range efficiency
TEST_CASE("InsertRange", "[IndexSetTest]") {
  cse::IndexSet set;

  // Basic range insertion
  set.insert_range(0, 5);  // [0,5)
  REQUIRE(set.size() == 5);

  // Overlapping range
  set.insert_range(3, 8);  // Should merge with [0,5) to become [0,8)
  REQUIRE(set.size() == 8);

  // Adjacent range
  set.insert_range(8, 10);  // Should merge with [0,8) to become [0,10)
  REQUIRE(set.size() == 10);

  // Disjoint range
  set.insert_range(12, 15);  // Should add [12,15)
  REQUIRE(set.size() == 13);

  // Invalid range (start >= end)
  set.insert_range(5, 3);
  REQUIRE(set.size() == 13);  // Size should not change
}

// Test iterator functionality
TEST_CASE("Iterator", "[IndexSetTest]") {
  cse::IndexSet set;
  set.insert_range(0, 3);    // [0,3)
  set.insert_range(5, 8);    // [5,8)
  set.insert_range(10, 12);  // [10,12)

  // Test forward iteration
  std::vector<std::size_t> expected = {0, 1, 2, 5, 6, 7, 10, 11};
  std::vector<std::size_t> actual;

  for (auto it = set.begin(); it != set.end(); ++it) {
    actual.push_back(*it);
  }

  REQUIRE(actual == expected);

  // Test range-based for loop
  actual.clear();
  for (const auto &index : set) {
    actual.push_back(index);
  }

  REQUIRE(actual == expected);

  // Test const iterator
  const cse::IndexSet const_set = set;
  actual.clear();
  for (auto it = const_set.cbegin(); it != const_set.cend(); ++it) {
    actual.push_back(*it);
  }

  REQUIRE(actual == expected);
}

// Original AppendAt test
TEST_CASE("AppendAt", "[IndexSetTest]") {
  cse::IndexSet set1;
  set1.insert_range(0, 3);  // [0,3)

  cse::IndexSet set2;
  set2.insert_range(0, 4);  // [0,4)

  // Append set2 starting at index 5
  set1.append_at(set2, 5);

  // Expected result: set1 should now contain [0,3) and [5,9)
  REQUIRE(set1.contains(0));
  REQUIRE(set1.contains(1));
  REQUIRE(set1.contains(2));
  REQUIRE_FALSE(set1.contains(3));
  REQUIRE_FALSE(set1.contains(4));
  REQUIRE(set1.contains(5));
  REQUIRE(set1.contains(6));
  REQUIRE(set1.contains(7));
  REQUIRE(set1.contains(8));
  REQUIRE_FALSE(set1.contains(9));

  // Test merging case
  cse::IndexSet set3;
  set3.insert_range(0, 2);  // [0,2)
  set1.append_at(set3, 3);  // Should merge with [0,3)

  // Expected: [0,5), [5,9)
  REQUIRE(set1.contains(3));
  REQUIRE(set1.contains(4));
  REQUIRE(set1.contains(5));
}

// Test copy operations
TEST_CASE("CopyOperations", "[IndexSetTest]") {
  cse::IndexSet original;
  original.insert_range(0, 3);    // [0,3)
  original.insert_range(5, 8);    // [5,8)
  original.insert_range(10, 12);  // [10,12)

  // Test copy constructor
  cse::IndexSet copied(original);
  REQUIRE(copied.size() == original.size());

  // Verify all ranges are copied correctly
  std::vector<std::size_t> original_indices = original.get_all_indices();
  std::vector<std::size_t> copied_indices = copied.get_all_indices();
  REQUIRE(copied_indices == original_indices);

  // Modify copy and verify original is unchanged
  copied.insert(3);  // Should merge with [0,3) to become [0,4)
  REQUIRE(copied.contains(3));
  REQUIRE_FALSE(original.contains(3));

  // Test copy assignment
  cse::IndexSet assigned;
  assigned = original;
  REQUIRE(assigned.size() == original.size());

  // Verify assigned copy has correct ranges
  std::vector<std::size_t> assigned_indices = assigned.get_all_indices();
  REQUIRE(assigned_indices == original_indices);
}

// Test move operations
TEST_CASE("MoveOperations", "[IndexSetTest]") {
  cse::IndexSet original;
  original.insert_range(0, 3);    // [0,3)
  original.insert_range(5, 8);    // [5,8)
  original.insert_range(10, 12);  // [10,12)

  std::vector<std::size_t> original_indices = original.get_all_indices();

  // Test move constructor
  cse::IndexSet moved(std::move(original));
  std::vector<std::size_t> moved_indices = moved.get_all_indices();
  REQUIRE(moved_indices == original_indices);

  // Original should be in valid but empty state after move
  REQUIRE(original.size() == 0);
  REQUIRE(original.get_all_indices().empty());

  // Create new set for move assignment test
  cse::IndexSet another;
  another.insert_range(0, 3);    // [0,3)
  another.insert_range(5, 8);    // [5,8)
  another.insert_range(10, 12);  // [10,12)

  std::vector<std::size_t> another_indices = another.get_all_indices();

  // Test move assignment
  cse::IndexSet move_assigned;
  move_assigned = std::move(another);

  // Verify moved-to object has correct ranges
  std::vector<std::size_t> assigned_indices = move_assigned.get_all_indices();
  REQUIRE(assigned_indices == another_indices);

  // Original should be in valid but empty state after move
  REQUIRE(another.size() == 0);
  REQUIRE(another.get_all_indices().empty());
}

// Test set operations
TEST_CASE("SetOperations", "[IndexSetTest]") {
  cse::IndexSet set1, set2;

  // Set1: [0,3) ∪ [5,7)
  set1.insert_range(0, 3);
  set1.insert_range(5, 7);

  // Set2: [2,6)
  set2.insert_range(2, 6);

  // Test union (|)
  auto union_set = set1 | set2;
  // Expected: [0,7) - continuous range due to overlap
  REQUIRE(union_set.contains(0));
  REQUIRE(union_set.contains(1));
  REQUIRE(union_set.contains(2));
  REQUIRE(union_set.contains(3));
  REQUIRE(union_set.contains(4));
  REQUIRE(union_set.contains(5));
  REQUIRE(union_set.contains(6));
  REQUIRE_FALSE(union_set.contains(7));

  // Test intersection (&)
  auto intersect_set = set1 & set2;
  // Expected: [2,3) ∪ [5,6)
  REQUIRE_FALSE(intersect_set.contains(0));
  REQUIRE_FALSE(intersect_set.contains(1));
  REQUIRE(intersect_set.contains(2));
  REQUIRE_FALSE(intersect_set.contains(3));
  REQUIRE_FALSE(intersect_set.contains(4));
  REQUIRE(intersect_set.contains(5));
  REQUIRE_FALSE(intersect_set.contains(6));

  // Test difference (-)
  auto diff_set = set1 - set2;
  // Expected: [0,2) ∪ [6,7)
  REQUIRE(diff_set.contains(0));
  REQUIRE(diff_set.contains(1));
  REQUIRE_FALSE(diff_set.contains(2));
  REQUIRE_FALSE(diff_set.contains(3));
  REQUIRE_FALSE(diff_set.contains(4));
  REQUIRE_FALSE(diff_set.contains(5));
  REQUIRE(diff_set.contains(6));
  REQUIRE_FALSE(diff_set.contains(7));

  // Test symmetric difference (^)
  auto sym_diff_set = set1 ^ set2;
  // Expected: [0,2) ∪ [3,5) ∪ [6,7)
  REQUIRE(sym_diff_set.contains(0));
  REQUIRE(sym_diff_set.contains(1));
  REQUIRE_FALSE(sym_diff_set.contains(2));  // In both sets
  REQUIRE(sym_diff_set.contains(3));
  REQUIRE(sym_diff_set.contains(4));
  REQUIRE_FALSE(sym_diff_set.contains(5));  // In both sets
  REQUIRE(sym_diff_set.contains(6));
  REQUIRE_FALSE(sym_diff_set.contains(7));

  // Test subset/superset
  cse::IndexSet subset;
  subset.insert_range(1, 2);  // [1,2)

  // Test subset (<=)
  REQUIRE(subset <= set1);
  REQUIRE_FALSE(set1 <= subset);
  REQUIRE_FALSE(set1 <= set2);

  // Test superset (>=)
  REQUIRE_FALSE(subset >= set1);
  REQUIRE(set1 >= subset);
  REQUIRE_FALSE(set1 >= set2);

  // Edge cases
  cse::IndexSet empty_set;
  REQUIRE(empty_set <= set1);  // Empty set is subset of all sets
  REQUIRE(set1 >= empty_set);  // All sets are superset of empty set
  REQUIRE((empty_set | set1).size() == set1.size());  // Union with empty set
  REQUIRE((empty_set & set1).size() == 0);  // Intersection with empty set
  REQUIRE((set1 - empty_set).size() ==
          set1.size());                     // Difference with empty set
  REQUIRE((empty_set - set1).size() == 0);  // Empty difference
}

// Test basic operations
TEST_CASE("Test basic operations", "[IndexSetTest]") {
  cse::IndexSet set;

  // Test initial state
  REQUIRE(set.size() == 0);
  REQUIRE(!set.contains(0));

  // Test single insert
  set.insert(5);
  REQUIRE(set.size() == 1);
  REQUIRE(set.contains(5));
  REQUIRE(!set.contains(4));
  REQUIRE(!set.contains(6));

  // Test single remove
  set.remove(5);
  REQUIRE(set.size() == 0);
  REQUIRE(!set.contains(5));
}

// Test range operations
TEST_CASE("Test range operations", "[IndexSetTest]") {
  cse::IndexSet set;

  // Insert consecutive numbers
  for (size_t i = 5; i < 10; ++i) {
    set.insert(i);
  }

  // Test range creation
  REQUIRE(set.size() == 5);
  auto range = set.get_containing_range(7);
  REQUIRE(range.has_value());
  REQUIRE(range->first == 5);
  REQUIRE(range->second == 10);

  // Test range queries
  auto next_range = set.get_next_range(4);
  REQUIRE(next_range.has_value());
  REQUIRE(next_range->first == 5);
  REQUIRE(next_range->second == 10);

  auto prev_range = set.get_prev_range(12);
  REQUIRE(prev_range.has_value());
  REQUIRE(prev_range->first == 5);
  REQUIRE(prev_range->second == 10);

  // Test get_all_indices
  auto indices = set.get_all_indices();
  REQUIRE(indices.size() == 5);
  for (size_t i = 0; i < indices.size(); ++i) {
    REQUIRE(indices[i] == i + 5);
  }
}

// Test range merging
TEST_CASE("Test range merging", "[IndexSetTest]") {
  cse::IndexSet set;

  // Insert non-consecutive ranges
  set.insert(1);
  set.insert(2);
  set.insert(4);
  set.insert(5);
  set.insert(3);  // This should merge all into one range

  REQUIRE(set.size() == 5);
  auto range = set.get_containing_range(3);
  REQUIRE(range.has_value());
  REQUIRE(range->first == 1);
  REQUIRE(range->second == 6);
}

// Test range splitting
TEST_CASE("Test range splitting", "[IndexSetTest]") {
  cse::IndexSet set;

  // Create a range and split it
  for (size_t i = 1; i <= 5; ++i) {
    set.insert(i);
  }

  set.remove(3);
  REQUIRE(set.size() == 4);
  REQUIRE(!set.contains(3));

  auto first_range = set.get_containing_range(2);
  auto second_range = set.get_containing_range(4);
  REQUIRE(first_range.has_value());
  REQUIRE(second_range.has_value());
  REQUIRE(first_range->first == 1);
  REQUIRE(first_range->second == 3);
  REQUIRE(second_range->first == 4);
  REQUIRE(second_range->second == 6);
}
