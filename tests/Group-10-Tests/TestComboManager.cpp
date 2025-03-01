#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-10/Classes/ComboManager.h"

#include <vector>
#include <list>
#include <array>
#include <string>
#include <stdexcept>
#include <type_traits>

// Test 1: Using ComboManager with std::vector<int>
TEST_CASE("ComboManager: std::vector<int> with combination size 2", "[ComboManager]")
{
    std::vector<int> numbers = {0, 1, 2, 3, 4};
    // There are C(5,2) = 10 combinations.
    cse::ComboManager<std::vector<int>> cm(numbers, 2);
    const unsigned long long expectedTotal = 10;
    REQUIRE(cm.TotalCombinations() == expectedTotal);

    int count = 0;
    // Iterate forward through all combinations.
    do
    {
        std::vector<int> combo = cm.GetCurrentCombo();
        INFO("Forward Combo " << count << ": "
                              << (combo.empty() ? "(empty)" : ""));
        count++;
    } while (cm.NextCombo());
    REQUIRE(count == expectedTotal);

    // Now, iterate backward using PrevCombo.
    int reverseCount = 0;
    while (cm.PrevCombo())
    {
        std::vector<int> combo = cm.GetCurrentCombo();
        INFO("Reverse Combo " << reverseCount << ": "
                              << (combo.empty() ? "(empty)" : ""));
        reverseCount++;
    }
    // Verify that after going back, the first combination is reached: {0, 1}
    std::vector<int> firstCombo = cm.GetCurrentCombo();
    REQUIRE(firstCombo.size() == 2);
    REQUIRE(firstCombo[0] == 0);
    REQUIRE(firstCombo[1] == 1);
}

// Test 2: Using ComboManager with std::list<std::string>
TEST_CASE("ComboManager: std::list<std::string> with combination size 2", "[ComboManager]")
{
    std::list<std::string> fruits = {"apple", "banana", "cherry", "date"};
    // There are C(4,2) = 6 combinations.
    cse::ComboManager<std::list<std::string>> cm(fruits, 2);
    const unsigned long long expectedTotal = 6;
    REQUIRE(cm.TotalCombinations() == expectedTotal);

    int count = 0;
    do
    {
        std::vector<std::string> combo = cm.GetCurrentCombo();
        INFO("Forward Combo " << count << ": "
                              << (combo.empty() ? "(empty)" : ""));
        count++;
    } while (cm.NextCombo());
    REQUIRE(count == expectedTotal);

    // Iterate backwards.
    int reverseCount = 0;
    while (cm.PrevCombo())
    {
        std::vector<std::string> combo = cm.GetCurrentCombo();
        INFO("Reverse Combo " << reverseCount << ": "
                              << (combo.empty() ? "(empty)" : ""));
        reverseCount++;
    }
    std::vector<std::string> firstCombo = cm.GetCurrentCombo();
    REQUIRE(firstCombo.size() == 2);
    REQUIRE(firstCombo[0] == "apple");
    REQUIRE(firstCombo[1] == "banana");
}

// Test 3: Using ComboManager with std::array<double, 5>
TEST_CASE("ComboManager: std::array<double, 5> with combination size 3", "[ComboManager]")
{
    std::array<double, 5> arr = {1.1, 2.2, 3.3, 4.4, 5.5};
    // There are C(5,3) = 10 combinations.
    cse::ComboManager<std::array<double, 5>> cm(arr, 3);
    const unsigned long long expectedTotal = 10;
    REQUIRE(cm.TotalCombinations() == expectedTotal);

    int count = 0;
    do
    {
        std::vector<double> combo = cm.GetCurrentCombo();
        INFO("Forward Combo " << count << ": "
                              << (combo.empty() ? "(empty)" : ""));
        count++;
    } while (cm.NextCombo());
    REQUIRE(count == expectedTotal);
}

// Test 4: Combination size 0 (should yield one empty combination).
TEST_CASE("ComboManager: Combination size 0", "[ComboManager]")
{
    std::vector<int> numbers = {1, 2, 3, 4};
    // There is exactly 1 combination when k == 0.
    cse::ComboManager<std::vector<int>> cm(numbers, 0);
    const unsigned long long expectedTotal = 1;
    REQUIRE(cm.TotalCombinations() == expectedTotal);

    std::vector<int> combo = cm.GetCurrentCombo();
    INFO("Combo is empty: " << (combo.empty() ? "true" : "false"));
    REQUIRE(combo.empty());
    // No next combination should exist.
    REQUIRE_FALSE(cm.NextCombo());
}

// Test 5: Combination size equal to container size.
TEST_CASE("ComboManager: Combination size equal to container size", "[ComboManager]")
{
    std::vector<char> letters = {'a', 'b', 'c'};
    // There is exactly 1 combination when k equals the container size.
    cse::ComboManager<std::vector<char>> cm(letters, letters.size());
    const unsigned long long expectedTotal = 1;
    REQUIRE(cm.TotalCombinations() == expectedTotal);

    std::vector<char> combo = cm.GetCurrentCombo();
    INFO("Combo contents: ");
    REQUIRE(combo.size() == letters.size());
    for (size_t i = 0; i < letters.size(); ++i)
    {
        REQUIRE(combo[i] == letters[i]);
    }
    // No next combination should exist.
    REQUIRE_FALSE(cm.NextCombo());
}

// Test 6: Invalid combination size (k > n) should throw an exception.
TEST_CASE("ComboManager: Invalid combination size (k > n) throws exception", "[ComboManager]")
{
    std::vector<int> numbers = {1, 2, 3};
    // Requesting more elements than available should throw.
    REQUIRE_THROWS_AS(cse::ComboManager<std::vector<int>>(numbers, 5), std::invalid_argument);
}

// Test 7: Reset functionality
TEST_CASE("ComboManager: Reset functionality returns to first combination", "[ComboManager]")
{
    std::vector<int> numbers = {10, 20, 30, 40};
    cse::ComboManager<std::vector<int>> cm(numbers, 2);

    // Advance through all combinations (we don't need to track the count).
    while (cm.NextCombo())
    {
    }

    // After exhausting combinations, reset back.
    cm.Reset();
    std::vector<int> firstCombo = cm.GetCurrentCombo();
    REQUIRE(firstCombo.size() == 2);
    // The first combination should match the first two elements.
    REQUIRE(firstCombo[0] == numbers[0]);
    REQUIRE(firstCombo[1] == numbers[1]);
}

// Test 8: Current indices correctness
TEST_CASE("ComboManager: GetCurrentIndices returns increasing indices", "[ComboManager]")
{
    std::vector<char> letters = {'x', 'y', 'z', 'w'};
    cse::ComboManager<std::vector<char>> cm(letters, 3);
    std::vector<std::size_t> indices = cm.GetCurrentIndices();

    // For the first combination, the indices should be {0, 1, 2}.
    REQUIRE(indices.size() == 3);
    REQUIRE(indices[0] == 0);
    REQUIRE(indices[1] == 1);
    REQUIRE(indices[2] == 2);

    // Move to next combination and ensure the indices remain strictly increasing.
    bool moved = cm.NextCombo();
    REQUIRE(moved);
    indices = cm.GetCurrentIndices();
    for (std::size_t i = 1; i < indices.size(); ++i)
    {
        INFO("Index " << i << " is " << indices[i] << ", previous index was " << indices[i - 1]);
        REQUIRE(indices[i] > indices[i - 1]);
    }
}

// Test 9: Single element container
TEST_CASE("ComboManager: Single element container produces one combination", "[ComboManager]")
{
    std::vector<int> single = {42};
    cse::ComboManager<std::vector<int>> cm(single, 1);
    const unsigned long long expectedTotal = 1;
    REQUIRE(cm.TotalCombinations() == expectedTotal);

    std::vector<int> combo = cm.GetCurrentCombo();
    REQUIRE(combo.size() == 1);
    REQUIRE(combo[0] == 42);
    // No further combination should be available.
    REQUIRE_FALSE(cm.NextCombo());
}

// Test 10: Empty container with combination size 0
TEST_CASE("ComboManager: Empty container with combination size 0", "[ComboManager]")
{
    std::vector<int> empty;
    // By convention, C(0, 0) is 1.
    cse::ComboManager<std::vector<int>> cm(empty, 0);
    REQUIRE(cm.TotalCombinations() == 1);

    std::vector<int> combo = cm.GetCurrentCombo();
    REQUIRE(combo.empty());
    REQUIRE_FALSE(cm.NextCombo());
}

// Test 11: Empty container with nonzero combination size should throw.
TEST_CASE("ComboManager: Empty container with nonzero combination size throws exception", "[ComboManager]")
{
    std::vector<int> empty;
    REQUIRE_THROWS_AS(cse::ComboManager<std::vector<int>>(empty, 1), std::invalid_argument);
}

// Test 12: Repeated calls to NextCombo after exhaustion
TEST_CASE("ComboManager: Repeated calls to NextCombo after last combination always return false", "[ComboManager]")
{
    std::vector<int> numbers = {0, 1, 2};
    cse::ComboManager<std::vector<int>> cm(numbers, 2);
    // Advance to the last combination.
    while (cm.NextCombo())
    {
    }
    REQUIRE(cm.TotalCombinations() == 3);
    // After reaching the final combination, repeated calls return false.
    for (int i = 0; i < 5; i++)
    {
        REQUIRE_FALSE(cm.NextCombo());
    }
}

// Test 13: Repeated calls to PrevCombo on first combination always return false.
TEST_CASE("ComboManager: Repeated calls to PrevCombo on first combination always return false", "[ComboManager]")
{
    std::vector<int> numbers = {5, 6, 7, 8};
    cse::ComboManager<std::vector<int>> cm(numbers, 2);
    // Already at the first combination.
    for (int i = 0; i < 3; i++)
    {
        REQUIRE_FALSE(cm.PrevCombo());
    }
}

// Test 14: Alternate NextCombo and PrevCombo consistency
TEST_CASE("ComboManager: Alternating NextCombo and PrevCombo yields consistent results", "[ComboManager]")
{
    std::vector<int> numbers = {0, 1, 2, 3};
    cse::ComboManager<std::vector<int>> cm(numbers, 2);

    // Save the first combination.
    std::vector<int> first = cm.GetCurrentCombo();

    // Move to the next combination.
    bool moved = cm.NextCombo();
    REQUIRE(moved);
    std::vector<int> second = cm.GetCurrentCombo();
    // Ensure the two combinations are different.
    REQUIRE(first != second);

    // Move back to the first combination.
    moved = cm.PrevCombo();
    REQUIRE(moved);
    std::vector<int> firstAgain = cm.GetCurrentCombo();
    REQUIRE(first == firstAgain);
}

// Test 15: Lexicographical order of generated combinations
TEST_CASE("ComboManager: Generated combinations are in lexicographical order", "[ComboManager]")
{
    std::vector<int> numbers = {0, 1, 2, 3};
    cse::ComboManager<std::vector<int>> cm(numbers, 2);
    std::vector<std::vector<int>> combinations;
    do
    {
        combinations.push_back(cm.GetCurrentCombo());
    } while (cm.NextCombo());

    // Compare each combination with the next to ensure lexicographical order.
    for (size_t i = 1; i < combinations.size(); i++)
    {
        INFO("Comparing combination " << i - 1 << " with combination " << i);
        REQUIRE(combinations[i - 1] < combinations[i]);
    }
}

// Test 16: Container with duplicate elements
TEST_CASE("ComboManager: Container with duplicate elements", "[ComboManager]")
{
    std::vector<int> numbers = {1, 2, 2, 3};
    // With 4 items, choosing 2 gives C(4,2) = 6 index combinations,
    // even though some value combinations may be identical.
    cse::ComboManager<std::vector<int>> cm(numbers, 2);
    REQUIRE(cm.TotalCombinations() == 6);

    int count = 0;
    do
    {
        std::vector<int> combo = cm.GetCurrentCombo();
        INFO("Combination " << count << " values: "
                            << (combo.empty() ? "(empty)" : ""));
        REQUIRE(combo.size() == 2);
        count++;
    } while (cm.NextCombo());
    REQUIRE(count == 6);
}

// Test 17: Larger container test for TotalCombinations correctness
TEST_CASE("ComboManager: Larger container total combinations test", "[ComboManager]")
{
    std::vector<int> numbers(10);
    for (int i = 0; i < 10; i++)
    {
        numbers[i] = i;
    }
    cse::ComboManager<std::vector<int>> cm(numbers, 3);
    // C(10,3) should equal 120.
    REQUIRE(cm.TotalCombinations() == 120);
}

/**
 * Advanced Test Cases

   - Iterators
   - Permutations
   - Repeating Elements
   - Required Elements
 */

 /**
  * Iterators should be available for the user to iterate over every combination generated by the constructor
  */
TEST_CASE("ComboManager: Iterators", "[ComboManager]")
{
    std::vector<int> comboNums{1, 2, 3, 4, 5, 6};
    cse::ComboManager<std::vector<int>> comboManager(comboNums, 2);

    // I think this might be a compile time error, so we need a different way to test the iterator exists
    // Both iterators should exist
    REQUIRE_NOTHROW(auto iterator = comboManager.begin());
    REQUIRE_NOTHROW(auto iterator = comboManager.end());

    for (auto i = comboManager.begin(); i != comboManager.end(); i++)
    {
        // The underlying type of each iterator should point to that combination
        CHECK(type(*i) == std::vector<int>);

    }
    
    // could have a test case where we verify values ~
    /*
    std::vector<int> smallNums{1, 2, 3};
    cse::ComboManager<std::vector<int>> comboManager(smallNums, 2);
    std::vector<std::vector<int>> res = {{1, 2}, {1, 3}, {2, 3}};
    size_t idx = 0;
    for (auto i = comboManger.begin(); i != comboManager.end(); i++) {
        CHECK(*i == res.at(idx));
    }
        */
}

/**
 * Permutations mean combinations of different order qualify as different combinations (Order DOES matter)
 */
TEST_CASE("Combo Manager: Test permutations", "[Combo Manager]")
{
    std::vector<int> nums(5);
    for (size_t i = 0; i < 5; ++i)
    {
        nums.push_back(i);
    }

    // constructor??
    //static_assert(std::is_constructible_v<cse::ComboManager<std::vector<int>, std::vector<int>, size_t, bool>,
    //              "Must account for permutations in constructor");
    cse::ComboManager<std::vector<int>> comboManager(nums, 3, false);

    // P(5, 3) == 60
    REQUIRE(comboManager.TotalCombinations() == 60);
}

/**
 * Repeating determines whether individual elements can repeat within a combination (determined by index) (AllowRepetition)
 * Repeating count determines how many times that individual element may repeat (max of the length of combo) (MaxRepetitions)
 */
TEST_CASE("Combo Manager: Test Repeating Elements", "[ComboManager]")
{
    bc = BinomialCoefficient(n = 5, k = 3, AllowRepetition = true, MaxRepetitions = 2);
    expected = 7;
    REQUIRE(bc == expected);

    bc = BinomialCoefficient(n = 5, k = 2, AllowRepetition = false, MaxRepetitions = None);
    expected = 10;
    REQUIRE(bc == expected);

    bc = BinomialCoefficient(n = 4, k = 3, AllowRepetition = true, MaxRepetitions = None);
    expected = 20;
    REQUIRE(bc == expected);

    bc = BinomialCoefficient(n = 3, k = 3, AllowRepetition = true, MaxRepetitions = 1);
    expected = 1;
    REQUIRE(bc == expected);
}

/**
 * Required means the specified element MUST appear at lease once in every combination returned
 */
 TEST_CASE("Combo Manager: Test Required Elements", "[ComboManager]")
{
    std::vector<int> vec = {1, 2, 3, 4};

    ComboManager<std::vector<int>> acm(items, 2);

    acm.SetRequiredElement(2);
    //might call a nw function here to get all combos with the required element
    // Such as
    // acm.Requi

// second parameter could also be the index of the required element

    std::vector<std::vector<int>> valid_combos;

    do {
        auto combo = acm.GetCurrentCombo();
        // Verify that the current combination contains the required element '2'.
        bool containsRequired = std::find(combo.begin(), combo.end(), 2) != combo.end();
        REQUIRE(containsRequired);
        
        valid_combos.push_back(combo);
    } while (acm.NextCombo());
    REQUIRE(valid_combos.size() == 3);
    std::vector<std::vector<int>> expected = { {1,2}, {2,3}, {2,4} };
    std::sort(valid_combos.begin(), valid_combos.end());
    std::sort(expected.begin(), expected.end());
    REQUIRE(valid_combos == expected);
}//