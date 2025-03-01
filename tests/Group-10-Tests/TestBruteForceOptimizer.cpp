#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-10/Classes/BruteForceOptimizer.h"

/// Tests for BruteForceOptimizer functionality
TEST_CASE("BruteForceOptimizer basic tests", "[BruteForceOptimizer]")
{
    SECTION("No items")
    {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetCapacity(10.0);
        optimizer.SetItems({});
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.second.empty());
        REQUIRE(result.first == 0.0);
    }

    SECTION("Single item, fits capacity")
    {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({{"Item1", 5.0, 5.0}});
        optimizer.SetCapacity(10.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.first == 5.0);
        REQUIRE(result.second.size() == 1);
        REQUIRE(result.second[0].weight == 5.0);
        REQUIRE(result.second[0].value == 5.0);
    }

    SECTION("Single item, does not fit capacity")
    {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({{"Item1", 12.0, 12.0}});
        optimizer.SetCapacity(10.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.second.empty());
        REQUIRE(result.first == 0.0);
    }

    SECTION("Multiple items, easy example")
    {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({{"A", 1.0, 1.0}, {"B", 2.0, 2.0}, {"C", 3.0, 3.0}, {"D", 4.0, 4.0}, {"E", 5.0, 5.0}});
        optimizer.SetCapacity(5.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.first == 5.0);
        double sumWeight = 0.0;
        for (auto const &item : result.second)
            sumWeight += item.weight;
        REQUIRE(sumWeight == 5.0);
    }

    SECTION("Multiple items, capacity < smallest item")
    {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({{"A", 3.0, 3.0}, {"B", 4.0, 4.0}, {"C", 5.0, 5.0}});
        optimizer.SetCapacity(2.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.second.empty());
        REQUIRE(result.first == 0.0);
    }

    SECTION("Mixed example, capacity=6")
    {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({{"A", 2.0, 2.0}, {"B", 2.0, 2.0}, {"C", 6.0, 6.0}, {"D", 3.0, 3.0}});
        optimizer.SetCapacity(6.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.first == 6.0);
        double sumWeight = 0.0;
        for (auto const &item : result.second)
            sumWeight += item.weight;
        REQUIRE(sumWeight == 6.0);
    }

    SECTION("Mixed example, selecting specific items (Gold and Silver)")
    {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({{"Silver", 2.0, 10.0}, {"Gold", 5.0, 20.0}, {"Copper", 2.0, 5.0}});
        optimizer.SetCapacity(7.0);
        auto result = optimizer.FindOptimalSolution();
        // Best solution should be Silver + Gold: weight = 7.0, value = 30.0
        REQUIRE(result.first == 30.0);
        REQUIRE(result.second.size() == 2);

        bool foundSilver = false, foundGold = false;
        for (auto const &item : result.second)
        {
            if (item.name == "Silver")
                foundSilver = true;
            if (item.name == "Gold")
                foundGold = true;
        }
        REQUIRE(foundSilver);
        REQUIRE(foundGold);
    }
}

/**
 * Advanced Class Tests
 *
 * - New Constructor to assemble the vector of Items
 * - Optimization Speedup
 * - FindOptimalSolution
 * - New knapsack variation
 */

// BruteForceOptimizer(vector of names, vector of values, vector of weights, vector of volume=optional)

// Optimization sections
// Utility function to measure execution time
template <typename Func>
double measureTime(Func &&func)
{
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

TEST_CASE("BruteForceOptimizer: Optimization Settings", "[BruteForceOptimizer]")
{
    cse::BruteForceOptimizer<cse::Item> optimizer;

    // really big item set, should take a while
    optimizer.SetItems({{"A", 2.0, 2.0}, {"B", 2.0, 2.0}, {"C", 6.0, 6.0}, {"D", 3.0, 3.0}, {"E", 2.2, 4.6}, {"F", 1.0, 1.0}, {"G", 1.0, 2.1}, {"H", 5.5, 6.5}, {"I", 5.9, 6.0}, {"J", 0.1, 0.4}, {"K", 1.0, 1.1}, {"L", 1.3, 4.0}, {"M", 3.3, 3.0}});
    optimizer.SetCapacity(7.0);

    double time1 = measureTime([&]()
                               { optimizer.FindOptimalSolution(); });

    // set optimization flag on
    // this should exist by the time we do it...
    optimizer.setOptimizer(true);

    double time2 = measureTime([&]()
                               { optimizer.FindOptimalSolution(); });

    REQUIRE(time1 > time2);
}

/**
 * Different Knapsack variations can be handled depending on user needs
 */
TEST_CASE("BruteForceOptimizer: Knapsack Repeatable Elements", "[BruteForceOptimizer]")
{
    cse::BruteForceOptimizer<cse::Item> optimizer;
    std::vector<cse::Item> itemVector{
        {"A", 3.0, 2.0}, {"B", 2.0, 2.0}, {"C", 6.0, 6.0}, {"D", 3.0, 3.0}};
    optimizer.SetItems({{"A", 2.0, 2.0}, {"B", 2.0, 2.0}, {"C", 6.0, 6.0}, {"D", 3.0, 3.0}});
    optimizer.SetCapacity(6.0);
    // This records the highest value for a solution where weight matters (Standard)
    auto result = optimizer.FindOptimalSolution(cse::BruteForceOptimizer::Weighted);
    std::vector<cse::Item> solutionVector{{"C", 6.0, 6.0}};
    std::pair<double, std::vector<cse::Item>> solution = (6.0, solutionVector);
    CHECK(result == solution);

    // This records the highest value when elements can repeat
    auto resultRepeatable = optimizer.FindOptimalSolution(cse::BruteForceOptimizer::Repeatable);
    // With A being able to repeat, and its repeated value being 9 rather than the previous best of 6, 3 As is the best solution
    std::vector<cse::Item> solutionRepeatableVector{{"A", 3.0, 2.0}, {"A", 3.0, 2.0}, {"A", 3.0, 2.0}};
    std::pair<double, std::vector<cse::Item>> solutionRepeatable = {9.0, solutionRepeatableVector};
    CHECK(resultRepeatable == solutionRepeatable);
}

TEST_CASE("BruteForceOptimizer: Constructor", "[BruteForceOptimizer]")
{
    // Initialize BruteForceOptimizer with vector of items that can be later retrieved with GetItems function
    cse::BruteForceOptimizer BFO(std::vector<Item>{{"A", 1.0, 1.0}, {"B", 2.0, 2.0}, {"C", 3.0, 3.0}});
    std::vector<Item> expected{{"A", 1.0, 1.0}, {"B", 2.0, 2.0}, {"C", 3.0, 3.0}};
    REQUIRE(BFO.GetItems() == expected);

    // Check default constructor for empty vector upon creation
    cse::BruteForceOptimizer BFO;
    std::vector<Item> expected = {};
    REQUIRE(BFO.GetItems() == expected);

    // Initialize BruteForceOptimizer with separate vectors of name, weights, and values that will be merged and turned into items-
    cse::BruteForceOptimizer BFO(std::vector<std::string>{"A", "B", "C"}, std::vector<double>{1.0, 2.0, 3.0}, std::vector<double>{1.0, 2.0, 3.0});
    std::vector<Item> expected{{"A", 1.0, 1.0}, {"B", 2.0, 2.0}, {"C", 3.0, 3.0}};
    REQUIRE(BFO.GetItems() == expected);
}
