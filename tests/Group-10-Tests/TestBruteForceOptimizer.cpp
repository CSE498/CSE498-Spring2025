#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-10/Classes/BruteForceOptimizer.h" 

/// Tests for StaticVector functionality

TEST_CASE("BruteForceOptimizer basic tests", "[BruteForceOptimizer]")
{
    SECTION("No items") {
        cse::BruteForceOptimizer<double> optimizer;
        optimizer.SetCapacity(10.0);
        auto result = optimizer.FindOptimalSolution();


        REQUIRE(result.second.empty());  // no items
        // check that it's not a positive number
        REQUIRE(result.first <= 0.0);
    }

    SECTION("Single item, fits capacity") {
        cse::BruteForceOptimizer<double> optimizer;
        optimizer.SetItems({5.0});
        optimizer.SetCapacity(10.0);

        auto result = optimizer.FindOptimalSolution();
        // We expect best sum = 5, subset = {5}
        REQUIRE(result.first == 5.0);
        REQUIRE(result.second.size() == 1);
        REQUIRE(result.second[0] == 5.0);
    }

    SECTION("Single item, does not fit capacity") {
        cse::BruteForceOptimizer<double> optimizer;
        optimizer.SetItems({12.0});
        optimizer.SetCapacity(10.0);

        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.second.empty());
        REQUIRE((result.first == 0.0 || result.first < 0));
    }

    SECTION("Multiple items, easy example") {
        cse::BruteForceOptimizer<double> optimizer;
        optimizer.SetItems({1,2,3,4,5});
        optimizer.SetCapacity(5.0);

        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.first == 5.0); 
        double sumCheck = 0;
        for (auto val : result.second) sumCheck += val;
        REQUIRE(sumCheck == 5.0);
    }

    SECTION("Multiple items, capacity < smallest item") {
        cse::BruteForceOptimizer<double> optimizer;
        // Items: [3,4,5], capacity=2 => can't pick anything
        optimizer.SetItems({3,4,5});
        optimizer.SetCapacity(2.0);

        auto result = optimizer.FindOptimalSolution();
        // Expect no items, best sum is 0 or negative sentinel
        REQUIRE(result.second.empty());
        REQUIRE((result.first == 0.0 || result.first < 0.0));
    }

    SECTION("Mixed example, capacity=6") {
        cse::BruteForceOptimizer<double> optimizer;
        optimizer.SetItems({2,2,6,3});
        optimizer.SetCapacity(6.0);

        auto result = optimizer.FindOptimalSolution();
        REQUIRE(result.first == 6.0);
        // The code might pick the single item [6].
        double sumCheck = 0;
        for (auto val : result.second) sumCheck += val;
        REQUIRE(sumCheck == 6.0);
    }
}