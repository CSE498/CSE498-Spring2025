/**
 * @file DataMapTest.cpp
 * @author Rahul B
 */

#define CATCH_CONFIG_MAIN
#include "../../include/third-party/Catch/single_include/catch2/catch.hpp"
#include "../../include/cse/DataMap.h"

TEST_CASE("DataMap Initialization", "[DataMap]") {
  cse::DataMap data_map = {
    {"name", std::string("rahul")},
    {"age", 22},
    {"dob", std::string("1209")}
  };

  SECTION("DataMap is not empty") {
    bool y = data_map.empty();
    REQUIRE(y == 0);
  }

  SECTION("Valid DataMap keys") {
    REQUIRE(data_map.count("name") == 1);
  }
}

TEST_CASE("DataMap Insert Method Tests", "[DataMap]") {
  cse::DataMap data_map;

  SECTION("Insert into DataMap") {
    data_map.insert("key", 20);
    int val = data_map.at<int>("key");
    REQUIRE(val == 20);
  }

  SECTION("DataMap contains method") {
    data_map.insert("key", 20);
    bool t = data_map.contains("key");
    REQUIRE(t == 1);

    bool f = data_map.contains("map");
    REQUIRE(f == 0);
  }
}

TEST_CASE("DataMap .at method","[DataMap]") {
  cse::DataMap data_map;
  data_map.insert("key", 80.2);
  data_map.insert("joe", std::string("value"));

  SECTION("Success .at method") {
    auto val = data_map.at<double>("key");
    CHECK(val == 80.2);
  }

  SECTION(".at method wrong key specified") {
    REQUIRE_FALSE(data_map.contains("bob"));
  }
}

TEST_CASE("DataMap delete key test") {
  cse::DataMap data_map;
  data_map.insert("key", 80.2);
  data_map.key_delete("key");
  REQUIRE(data_map.empty() == 1);
}

TEST_CASE("DataMap [] operator test") {
  cse::DataMap data_map;
  data_map["joe"] = 80;
  int val = std::any_cast<int>(data_map["joe"]);
  REQUIRE(val == 80);

  data_map["bob"];
  auto value = std::any_cast<int>(data_map["bob"]);
  REQUIRE(value == 0);
}
