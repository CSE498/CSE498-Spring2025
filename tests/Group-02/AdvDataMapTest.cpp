/**
 * @file AdvDataMapTest.cpp
 * @author Rahul B
 */

#include <cse/DataMap.hpp>
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

TEST_CASE("DataMap Default Constructor Test", "[DataMap]") {
  cse::DataMap data_map;
  data_map.insert("key", 20);

  SECTION("DataMap is not empty") {
    bool y = data_map.empty();
    REQUIRE(y == 0);
  }

  SECTION("Valid DataMap keys") {
    REQUIRE(data_map.count("key") == 1);
  }
}

TEST_CASE("DataMap Insert Method Tests", "[DataMap]") {
  cse::DataMap data_map;

  SECTION("Single insert into DataMap") {
    data_map.insert("key", 20);
    auto vals = data_map.at("key");
    REQUIRE(vals.size() == 1);
    REQUIRE(vals[0] == 20);
  }

  SECTION("Multiple insert into DataMap") {
    data_map.insert("key2", 10);
    data_map.insert("key2", 20);
    auto vals = data_map.at("key2");
    REQUIRE(vals.size() == 2);
    REQUIRE(vals[0] == 10);
    REQUIRE(vals[1] == 20);
  }

  TEST_CASE("DataMap to_string method Test") {
    cse::DataMap data_map;
    data_map.insert("key", 80.2);
    data_map.insert("key2", std::string("professor"));
    data_map.insert("key2", std::string("prof"));

    SECTION("Convert to string") {
      std::vector vals = {80.2}
      REQUIRE(data_map.to_string("key") == vals;)
    }
    /// no need for asking type this time and datamap to check how many values first within to_string method
    SECTION("Multiple values") {
      REQUIRE(data_map.to_string("key2") == vals;)
    }
  }

  TEST_CASE("DataMap get test") {
    cse::DataMap data_map;
    data_map.insert("key", 80.2);
    auto vals = data_map.get("key");
    REQUIRE(vals[0] == 80.2);
    auto vals2 = data_map.get("key2");
    REQUIRE(vals2[0] == 0);
  }

  TEST_CASE("DataMap erase method Test") {
    cse::DataMap data_map;
    data_map.insert("key", 80.2);
    data_map.erase("key");
    REQUIRE(data_map.empty() == 1);
  }

  TEST_CASE("DataMap clear method Test") {
    cse::DataMap data_map;
    data_map.insert("key", 80.2);
    data_map.clear();
    REQUIRE(data_map.empty() == 1);
  }

  TEST_CASE("DataMap size method Test") {
    cse::DataMap data_map;
    data_map.insert("key", 80.2);
    REQUIRE(data_map.size() == 1);
  }

  TEST_CASE("DataMap empty method Test") {
    cse::DataMap data_map;
    data_map.insert("key", 80.2);
    REQUIRE_FALSE(data_map.empty() == 1);

    data_map.clear();
    REQUIRE(data_map.empty() == 1);
  }
}