#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../Group-03/src/DataTracker.h"
#include <vector>


TEST_CASE("DataTrackerTest Empty", "[DataTracker]") {
    cse::DataTracker tracker;
    CHECK(tracker.total() == 0);
    CHECK(tracker.mean() == 0.0);
    CHECK(tracker.median() == 0.0);
    CHECK(tracker.min() == 0.0);
    CHECK(tracker.max() == 0.0);
}

TEST_CASE("DataTrackerTest Add", "[DataTracker]") {
    cse::DataTracker tracker;
    tracker.add_value(10.0);
    CHECK(tracker.total() == 1);
    CHECK(tracker.mean() == 10.0);
    CHECK(tracker.median() == 10.0);
    CHECK(tracker.min() == 10.0);
    CHECK(tracker.max() == 10.0);
}

TEST_CASE("DataTracker Multiple", "[DataTracker]") {
    cse::DataTracker tracker;
    tracker.add_value(5.0);
    tracker.add_value(10.0);
    tracker.add_value(15.0);
    CHECK(tracker.total() == 3);
    CHECK(tracker.mean() == 10.0);
    CHECK(tracker.median() == 10.0);
    CHECK(tracker.min() == 5.0);
    CHECK(tracker.max() == 15.0);
}

TEST_CASE("DataTracker Delete", "[DataTracker]") {
    cse::DataTracker tracker;
    tracker.add_value(5.0);
    tracker.add_value(10.0);
    tracker.add_value(15.0);
    tracker.delete_value(10.0);
    CHECK(tracker.total() == 2);
    CHECK(tracker.mean() == 10.0);
    CHECK(tracker.median() == 10.0);
    CHECK(tracker.min() == 5.0);
    CHECK(tracker.max() == 15.0);
}


TEST_CASE("DataTracker Even Number", "[DataTracker]") {
    cse::DataTracker tracker;
    tracker.add_value(1.0);
    tracker.add_value(3.0);
    tracker.add_value(2.0);
    tracker.add_value(4.0);
    CHECK(tracker.median() == 2.5);
}

TEST_CASE("Delete Nonexistent Value", "[DataTracker]") {
    cse::DataTracker tracker;
    tracker.add_value(5.0);
    tracker.add_value(10.0);
    CHECK(tracker.delete_value(15.0) == false);  // Should return false
    CHECK(tracker.total() == 2);  // Total should remain unchanged
}

TEST_CASE("Duplicate Values Handling", "[DataTracker]") {
    cse::DataTracker tracker;
    tracker.add_value(10.0);
    tracker.add_value(10.0);
    tracker.add_value(20.0);
    tracker.delete_value(10.0);  // Only one instance should be removed
    CHECK(tracker.total() == 2);
    CHECK(tracker.min() == 10.0);
    CHECK(tracker.max() == 20.0);
}

TEST_CASE("Negative and Large Values", "[DataTracker]") {
    cse::DataTracker tracker;
    tracker.add_value(-100.0);
    tracker.add_value(5000.0);
    tracker.add_value(200.0);
    CHECK(tracker.mean() > 1600.0);
    CHECK(tracker.min() == -100.0);
    CHECK(tracker.max() == 5000.0);
}
