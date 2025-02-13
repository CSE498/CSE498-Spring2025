#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-10/Classes/ComboManager.h"

#include <vector>
#include <list>
#include <array>
#include <string>
#include <stdexcept>

//-----------------------------------------------------------
// Original Tests
//-----------------------------------------------------------

// Test 1: Using ComboManager with std::vector<int>
TEST_CASE("ComboManager: std::vector<int> with combination size 2", "[ComboManager]") {
    std::vector<int> numbers = {0, 1, 2, 3, 4};
    // There are C(5,2) = 10 combinations.
    cse::ComboManager<std::vector<int>> cm(numbers, 2);
    const unsigned long long expectedTotal = 10;
    REQUIRE(cm.TotalCombinations() == expectedTotal);

    int count = 0;
    // Iterate forward through all combinations.
    do {
        std::vector<int> combo = cm.GetCurrentCombo();
        INFO("Forward Combo " << count << ": " 
             << (combo.empty() ? "(empty)" : ""));
        count++;
    } while (cm.NextCombo());
    REQUIRE(count == expectedTotal);

    // Now, iterate backward using PrevCombo.
    int reverseCount = 0;
    while (cm.PrevCombo()) {
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
TEST_CASE("ComboManager: std::list<std::string> with combination size 2", "[ComboManager]") {
    std::list<std::string> fruits = {"apple", "banana", "cherry", "date"};
    // There are C(4,2) = 6 combinations.
    cse::ComboManager<std::list<std::string>> cm(fruits, 2);
    const unsigned long long expectedTotal = 6;
    REQUIRE(cm.TotalCombinations() == expectedTotal);

    int count = 0;
    do {
        std::vector<std::string> combo = cm.GetCurrentCombo();
        INFO("Forward Combo " << count << ": " 
             << (combo.empty() ? "(empty)" : ""));
        count++;
    } while (cm.NextCombo());
    REQUIRE(count == expectedTotal);

    // Iterate backwards.
    int reverseCount = 0;
    while (cm.PrevCombo()) {
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
TEST_CASE("ComboManager: std::array<double, 5> with combination size 3", "[ComboManager]") {
    std::array<double, 5> arr = {1.1, 2.2, 3.3, 4.4, 5.5};
    // There are C(5,3) = 10 combinations.
    cse::ComboManager<std::array<double, 5>> cm(arr, 3);
    const unsigned long long expectedTotal = 10;
    REQUIRE(cm.TotalCombinations() == expectedTotal);

    int count = 0;
    do {
        std::vector<double> combo = cm.GetCurrentCombo();
        INFO("Forward Combo " << count << ": " 
             << (combo.empty() ? "(empty)" : ""));
        count++;
    } while (cm.NextCombo());
    REQUIRE(count == expectedTotal);
}

// Test 4: Combination size 0 (should yield one empty combination).
TEST_CASE("ComboManager: Combination size 0", "[ComboManager]") {
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
TEST_CASE("ComboManager: Combination size equal to container size", "[ComboManager]") {
    std::vector<char> letters = {'a', 'b', 'c'};
    // There is exactly 1 combination when k equals the container size.
    cse::ComboManager<std::vector<char>> cm(letters, letters.size());
    const unsigned long long expectedTotal = 1;
    REQUIRE(cm.TotalCombinations() == expectedTotal);
    
    std::vector<char> combo = cm.GetCurrentCombo();
    INFO("Combo contents: ");
    REQUIRE(combo.size() == letters.size());
    for (size_t i = 0; i < letters.size(); ++i) {
        REQUIRE(combo[i] == letters[i]);
    }
    // No next combination should exist.
    REQUIRE_FALSE(cm.NextCombo());
}

// Test 6: Invalid combination size (k > n) should throw an exception.
TEST_CASE("ComboManager: Invalid combination size (k > n) throws exception", "[ComboManager]") {
    std::vector<int> numbers = {1, 2, 3};
    // Requesting more elements than available should throw.
    REQUIRE_THROWS_AS(cse::ComboManager<std::vector<int>>(numbers, 5), std::invalid_argument);
}

