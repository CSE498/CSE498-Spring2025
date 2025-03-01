#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-10/Classes/BruteForceOptimizer.h" 

/// Tests for BruteForceOptimizer functionality
TEST_CASE("BruteForceOptimizer basic tests", "[BruteForceOptimizer]")
{
    SECTION("No items") {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetCapacity(10.0);
        optimizer.SetItems({});
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.second.empty());
        REQUIRE(result.first == 0.0);
    }

    SECTION("Single item, fits capacity") {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({ {"Item1", 5.0, 5.0} });
        optimizer.SetCapacity(10.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.first == 5.0);
        REQUIRE(result.second.size() == 1);
        REQUIRE(result.second[0].weight == 5.0);
        REQUIRE(result.second[0].value == 5.0);
    }

    SECTION("Single item, does not fit capacity") {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({ {"Item1", 12.0, 12.0} });
        optimizer.SetCapacity(10.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.second.empty());
        REQUIRE(result.first == 0.0);
    }

    SECTION("Multiple items, easy example") {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({ {"A", 1.0, 1.0}, {"B", 2.0, 2.0}, {"C", 3.0, 3.0}, {"D", 4.0, 4.0}, {"E", 5.0, 5.0} });
        optimizer.SetCapacity(5.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.first == 5.0);
        double sumWeight = 0.0;
        for (auto const& item : result.second)
            sumWeight += item.weight;
        REQUIRE(sumWeight == 5.0);
    }

    SECTION("Multiple items, capacity < smallest item") {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({ {"A", 3.0, 3.0}, {"B", 4.0, 4.0}, {"C", 5.0, 5.0} });
        optimizer.SetCapacity(2.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.second.empty());
        REQUIRE(result.first == 0.0);
    }

    SECTION("Mixed example, capacity=6") {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({ {"A", 2.0, 2.0}, {"B", 2.0, 2.0}, {"C", 6.0, 6.0}, {"D", 3.0, 3.0} });
        optimizer.SetCapacity(6.0);
        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.first == 6.0);
        double sumWeight = 0.0;
        for (auto const& item : result.second)
            sumWeight += item.weight;
        REQUIRE(sumWeight == 6.0);
    }

    SECTION("Mixed example, selecting specific items (Gold and Silver)") {
        cse::BruteForceOptimizer<cse::Item> optimizer;
        optimizer.SetItems({ {"Silver", 2.0, 10.0}, {"Gold", 5.0, 20.0}, {"Copper", 2.0, 5.0} });
        optimizer.SetCapacity(7.0);
        auto result = optimizer.FindOptimalSolution();
        // Best solution should be Silver + Gold: weight = 7.0, value = 30.0
        REQUIRE(result.first == 30.0);
        REQUIRE(result.second.size() == 2);

        bool foundSilver = false, foundGold = false;
        for (auto const& item : result.second) {
            if (item.name == "Silver")
                foundSilver = true;
            if (item.name == "Gold")
                foundGold = true;
        }
        REQUIRE(foundSilver);
        REQUIRE(foundGold);
    }
}