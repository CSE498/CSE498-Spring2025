#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../Group-03/src/DataTracker.h"
#include <vector>

TEST_CASE("Advanced DataTracker Mode", "[DataTracker]") {
    cse::DataTracker<int> tracker;
    tracker.add_value(1);
    tracker.add_value(2);
    tracker.add_value(2);
    tracker.add_value(3);
    CHECK(tracker.mode() == 2);

    tracker.add_value(3);
    CHECK((tracker.mode() == 2 || tracker.mode() == 3)); // Handle multiple modes
}

TEST_CASE("Advanced DataTracker Variance", "[DataTracker]") {
    cse::DataTracker<double> tracker;
    tracker.add_value(2.0);
    tracker.add_value(4.0);
    tracker.add_value(4.0);
    tracker.add_value(4.0);
    tracker.add_value(5.0);
    tracker.add_value(5.0);
    tracker.add_value(7.0);
    tracker.add_value(9.0);
    CHECK(tracker.variance() == Approx(4.0));
}

TEST_CASE("Advanced DataTracker Template Support", "[DataTracker]") {
    cse::DataTracker<std::string> tracker;
    tracker.add_value("apple");
    tracker.add_value("banana");
    tracker.add_value("apple");
    CHECK(tracker.mode() == "apple");
}

TEST_CASE("Advanced DataTracker Prey-Predator Win Condition", "[DataTracker]") {
    cse::DataTracker<int> tracker;
    for (int i = 0; i < 81; ++i) tracker.add_value(1); // 81% prey
    for (int i = 0; i < 19; ++i) tracker.add_value(2); // 19% predator
    CHECK(tracker.has_winner());
    CHECK(tracker.get_winner() == 1);
}
