/**
 * @file ReferenceVectorTests.cpp
 *
 * @author Calen Green
 *
 * Tests for the ReferenceVector class.
 */

#include "../../Group-05/src/Datum.h"
#include "../../Group-05/src/ReferenceVector.h"

#define CATCH_CONFIG_MAIN
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

TEST_CASE("push_back() functionality", "[push_back]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::ReferenceVector refVec;

  refVec.push_back(d1);
  refVec.push_back(d2);
  refVec.push_back(d3);

  CHECK(refVec.size() == 3);
}

TEST_CASE("pop_back() functionality", "[pop_back]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::ReferenceVector refVec;

  refVec.push_back(d1);
  refVec.push_back(d2);
  refVec.push_back(d3);
  refVec.pop_back();

  CHECK(refVec.size() == 2);
}

TEST_CASE("Element access functionality", "[access]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::ReferenceVector refVec;

  refVec.push_back(d1);
  refVec.push_back(d2);
  refVec.push_back(d3);

  CHECK(refVec.front().GetDouble().value() == 123.123);
  CHECK(refVec.at(1).GetString().value() == "test");
  CHECK(refVec.back().GetDouble().value() == 987);
}

TEST_CASE("Element modification functionality", "[modify]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::Datum newDatum("UpdatedDatum");
  cse::Datum newDatum2(987.987);
  cse::ReferenceVector refVec;

  refVec.push_back(d1);
  refVec.push_back(d2);
  refVec.push_back(d3);

  refVec[1] = newDatum;
  refVec[2] = newDatum2;
  CHECK(refVec.at(1).GetString().value() == "UpdatedDatum");
  CHECK(refVec.at(2).GetDouble().value() == 987.987);
}

TEST_CASE("erase() functionality", "[erase]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::ReferenceVector refVec;

  refVec.push_back(d1);
  refVec.push_back(d2);
  refVec.push_back(d3);
  refVec.erase(1);

  CHECK(refVec.at(1).GetDouble().value() == 987);
  CHECK(refVec.size() == 2);
}

TEST_CASE("clear() functionality", "[clear]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::ReferenceVector refVec;

  refVec.push_back(d1);
  refVec.push_back(d2);
  refVec.push_back(d3);
  refVec.clear();

  CHECK(refVec.size() == 0);
}

TEST_CASE("empty() functionality", "[empty]") {
  cse::ReferenceVector refVec;

  CHECK(refVec.empty());
}