#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../../Group-01/WeightedSet/WeightedSet.hpp"



TEST_CASE("Test WeightedSet::Add", "[base]")
{
    cse498::WeightedSet ws;
    CHECK_NOTHROW(ws.Add(1, 1.0));
    CHECK_NOTHROW(ws.Add(2, 2.0));
    CHECK_NOTHROW(ws.Add(3, 3.0));
}

TEST_CASE("Test WeightedSet::Remove", "[base]")
{
    cse498::WeightedSet ws;
    ws.Add(1, 1.0);
    ws.Add(2, 2.0);
    ws.Add(3, 3.0);

    CHECK_NOTHROW(ws.Remove(2));
    CHECK_THROWS_AS(ws.Remove(2), std::invalid_argument);
}

TEST_CASE("Test WeightedSet::TotalWeight", "[base]")
{
    cse498::WeightedSet ws;
    ws.Add(1, 1.0);
    ws.Add(2, 2.0);
    ws.Add(3, 3.0);

    CHECK(ws.TotalWeight() == 6.0);
}

TEST_CASE("Test WeightedSet::Weight", "[base]")
{
    cse498::WeightedSet ws;
    ws.Add(1, 1.0);
    ws.Add(2, 2.0);
    ws.Add(3, 3.0);

    CHECK(ws.Weight(1) == 1.0);
    CHECK(ws.Weight(2) == 2.0);
    CHECK(ws.Weight(3) == 3.0);
    CHECK_THROWS_AS(ws.Weight(4), std::invalid_argument);
}

TEST_CASE("Test WeightedSet::At", "[base]")
{
    cse498::WeightedSet ws;
    ws.Add(1, 1.0);
    ws.Add(2, 2.0);
    ws.Add(3, 3.0);

    CHECK(ws.At(0) == 1);
    CHECK(ws.At(1) == 1);
    CHECK(ws.At(2) == 2);
    CHECK(ws.At(3) == 2);
    CHECK(ws.At(4) == 3);
    CHECK(ws.At(5) == 3);
    CHECK_THROWS_AS(ws.At(10), std::invalid_argument);
}