#include "../../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../RandomAccessSet/RandomAccessSet.h"

TEST_CASE("Test RandomAccessSet add operation", "[RandomAccessSet]") {
    RandomAccessSet<int> ras;
    CHECK(ras.add(10));
    CHECK(ras.add(20));
    CHECK_FALSE(ras.add(10)); // Duplicate should not be added
    CHECK(ras.size() == 2);
}

TEST_CASE("Test RandomAccessSet contains operation", "[RandomAccessSet]") {
    RandomAccessSet<int> ras;
    ras.add(15);
    ras.add(25);
    CHECK(ras.contains(15));
    CHECK(ras.contains(25));
    CHECK_FALSE(ras.contains(30));
}

TEST_CASE("Test RandomAccessSet get by index", "[RandomAccessSet]") {
    RandomAccessSet<int> ras;
    ras.add(5);
    ras.add(10);
    ras.add(15);
    CHECK(ras.get(0) == 5);
    CHECK(ras.get(1) == 10);
    CHECK(ras.get(2) == 15);
}

TEST_CASE("Test RandomAccessSet remove operation", "[RandomAccessSet]") {
    RandomAccessSet<int> ras;
    ras.add(7);
    ras.add(14);
    ras.add(21);
    CHECK(ras.remove(14));
    CHECK_FALSE(ras.contains(14));
    CHECK(ras.size() == 2);
    CHECK_FALSE(ras.remove(30)); // Non-existent element
}

TEST_CASE("Test RandomAccessSet size operation", "[RandomAccessSet]") {
    RandomAccessSet<int> ras;
    CHECK(ras.size() == 0);
    ras.add(1);
    ras.add(2);
    CHECK(ras.size() == 2);
    ras.remove(1);
    CHECK(ras.size() == 1);
}

TEST_CASE("Test RandomAccessSet getIndexOf operation", "[RandomAccessSet]") {
    RandomAccessSet<int> ras;
    ras.add(100);
    ras.add(200);
    CHECK(ras.getIndexOf(100) == 0);
    CHECK(ras.getIndexOf(200) == 1);
}