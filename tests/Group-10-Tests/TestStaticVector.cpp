#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-10/Classes/StaticVector.h" 

/// Tests for StaticVector functionality

TEST_CASE("StaticVector operations", "[StaticVector]") {
    cse::StaticVector<int, 5> sv;

    SECTION("Empty vector") {
        REQUIRE(sv.size() == 0);
    }

    SECTION("Pushing elements") {
        sv.push_back(1);
        sv.push_back(2);
        REQUIRE(sv.size() == 2);
        REQUIRE(sv.at(0) == 1);
        REQUIRE(sv.at(1) == 2);
    }

    SECTION("Popping elements") {
        sv.push_back(1);
        sv.push_back(2);
        sv.pop_back();
        REQUIRE(sv.size() == 1);
        REQUIRE(sv.back() == 1);
    }

    SECTION("Accessing front and back") {
        sv.push_back(10);
        sv.push_back(20);
        REQUIRE(sv.front() == 10);
        REQUIRE(sv.back() == 20);
    }

    SECTION("Clearing vector") {
        sv.push_back(1);
        sv.clear();
        REQUIRE(sv.empty());
    }

    SECTION("ToVector conversion") {
        sv.push_back(1);
        sv.push_back(2);
        std::vector<int> std_vec = cse::ToVector(sv);
        REQUIRE(std_vec.size() == 2);
        REQUIRE(std_vec[0] == 1);
        REQUIRE(std_vec[1] == 2);
    }
}
