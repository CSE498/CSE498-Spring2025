#include "../../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../RandomAccessSet/RandomAccessSet.hpp"

TEST_CASE("Test RandomAccessSet default construction", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    CHECK(ras.size() == 0);
    CHECK_FALSE(ras.contains(42)); // No element should exist
}

TEST_CASE("Test RandomAccessSet size operation", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    CHECK(ras.size() == 0);
    ras.add(1);
    ras.add(2);
    ras.remove(1);
    CHECK(ras.size() == 1);
}

TEST_CASE("Test RandomAccessSet add operation", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    CHECK(ras.add(10));
    CHECK(ras.add(20));
    CHECK_FALSE(ras.add(10)); // Duplicate should not be added
    CHECK(ras.size() == 2);
}

TEST_CASE("Test RandomAccessSet contains operation", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    ras.add(15);
    ras.add(25);
    CHECK(ras.contains(15));
    CHECK(ras.contains(25));
    CHECK_FALSE(ras.contains(30));
}

TEST_CASE("Test RandomAccessSet get by index", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    ras.add(5);
    ras.add(10);
    ras.add(15);
    CHECK(ras.get(0) == 5);
    CHECK(ras.get(1) == 10);
    CHECK(ras.get(2) == 15);
}

TEST_CASE("Test RandomAccessSet get() with invalid index", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    ras.add(10);
    ras.add(20);

    REQUIRE_THROWS_AS(ras.get(2), std::out_of_range);   // index 2 invalid
    REQUIRE_THROWS_AS(ras.get(999), std::out_of_range); // obviously out-of-range
}

TEST_CASE("Test RandomAccessSet getIndexOf() with invalid item", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    ras.add(100);

    REQUIRE_THROWS_AS(ras.getIndexOf(999), std::out_of_range);
}

TEST_CASE("Test RandomAccessSet remove operation", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    ras.add(7);
    ras.add(14);
    ras.add(21);
    CHECK(ras.remove(14));
    CHECK_FALSE(ras.contains(14));
    CHECK(ras.size() == 2);
    CHECK_FALSE(ras.remove(30)); // Non-existent element
}

TEST_CASE("Test RandomAccessSet remove() edge cases", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    ras.add(1);
    ras.add(2);
    ras.add(3);

    // Remove last element (3), no swap needed
    CHECK(ras.remove(3));
    CHECK_FALSE(ras.contains(3));
    CHECK(ras.size() == 2);

    // Remove element at index 0 (element '1')
    // The code should swap '1' with the last (which is '2'), then pop.
    CHECK(ras.remove(1));
    CHECK_FALSE(ras.contains(1));
    CHECK(ras.size() == 1);

    // Now '2' should be the only element left
    CHECK(ras.contains(2));
    CHECK(ras.getIndexOf(2) == 0);
}

TEST_CASE("Test RandomAccessSet getIndexOf operation", "[RandomAccessSet]") {
    cse::RandomAccessSet<int> ras;
    ras.add(100);
    ras.add(200);
    CHECK(ras.getIndexOf(100) == 0);
    CHECK(ras.getIndexOf(200) == 1);
}