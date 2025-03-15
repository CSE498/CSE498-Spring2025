// Tests Header
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

// Misc. Headers
#include <iostream>
#include <stdexcept>
#include <string>

// Class Header
#include "../../Group-10/Classes/MemoryFactory.h"

TEST_CASE("MemoryFactory Construction", "[constructor]") {
  SECTION("Testing default construction") {
    // Constructor with Default Size
    cse::MemoryFactory<int> intFactory = cse::MemoryFactory<int>();
    REQUIRE(intFactory.GetSpace() == 10);

    cse::MemoryFactory<std::string> stringFactory =
        cse::MemoryFactory<std::string>();
    REQUIRE(stringFactory.GetSpace() == 10);
  }

  SECTION("Testing Custom Size for Allocation") {
    // Constructor with Custom Size
    cse::MemoryFactory<int> intFactory2 = cse::MemoryFactory<int>(20);
    REQUIRE(intFactory2.GetSpace() == 20);

    cse::MemoryFactory<std::string> stringFactory2 =
        cse::MemoryFactory<std::string>(20);
    REQUIRE(stringFactory2.GetSpace() == 20);

    cse::MemoryFactory<int> intFactory3 = cse::MemoryFactory<int>(1);
    REQUIRE(intFactory3.GetSpace() == 1);
    REQUIRE(intFactory3.GetSize() == 1);
  }

  SECTION("Testing Customized Initial Values for Allocation") {
    cse::MemoryFactory<int> intFactory = cse::MemoryFactory<int>(10, 37);
    int* firstItem = intFactory.Allocate();
    int* secondItem = intFactory.Allocate();
    REQUIRE(*firstItem == 37);
    REQUIRE(*secondItem == 37);
    intFactory.Deallocate(firstItem);
    intFactory.Deallocate(secondItem);

    std::string originalLiteral = "Hello There";
    cse::MemoryFactory<std::string> stringFactory =
        cse::MemoryFactory<std::string>(10, originalLiteral);
    std::string* stringLiteral = stringFactory.Allocate();
    std::string* stringLiteral2 = stringFactory.Allocate();
    REQUIRE(*stringLiteral == originalLiteral);
    REQUIRE(*stringLiteral2 == originalLiteral);
    stringFactory.Deallocate(stringLiteral);
    stringFactory.Deallocate(stringLiteral2);
    
  }
}


TEST_CASE("MemoryFactory Allocation", "[standard_use]") {
  SECTION("Testing variable allocation and assignments.") {
    cse::MemoryFactory<int> intFactory = cse::MemoryFactory<int>(5);
    REQUIRE(intFactory.GetSpace() == 5);
    int* Test = intFactory.Allocate();
    *Test = 5;
    REQUIRE(intFactory.GetSpace() == 4);
    REQUIRE(*Test == 5);
    intFactory.Deallocate(Test);
    REQUIRE(intFactory.GetSpace() == 5);
  }
  
  SECTION("Testing advanced variable initialization") {
    cse::MemoryFactory<int> intFactory = cse::MemoryFactory<int>(5);
    REQUIRE(intFactory.GetSpace() == 5);
    int* customTest = intFactory.Allocate(6);
    REQUIRE(*customTest == 6);
    intFactory.Deallocate(customTest);
    REQUIRE(intFactory.GetSpace() == 5);
    
    int* defaultTest = intFactory.Allocate();
    REQUIRE(*defaultTest == 0);
    intFactory.Deallocate(defaultTest);
    
    struct TestStruct {
      double variable1 = 1.0;
      std::string variable2 = "";
      TestStruct() {}
      TestStruct(double var1, std::string var2)
      : variable1(var1), variable2(var2) {}
      
      bool operator!=(const TestStruct& other) {
        return (variable1 != other.variable1) || (variable2 != other.variable2);
      }
      
      bool operator==(const TestStruct& other) {
        return (variable1 == other.variable1) && (variable2 == other.variable2);
      }
    };
    
    cse::MemoryFactory<TestStruct> structFactory =
    cse::MemoryFactory<TestStruct>();
    TestStruct* struct1 = structFactory.Allocate(37.5, "Hello Struct");
    REQUIRE(struct1->variable1 == 37.5);
    REQUIRE(struct1->variable2 == "Hello Struct");
    structFactory.Deallocate(struct1);
  }
}

TEST_CASE("MemoryFactory Deallocation", "[errors]") {
  cse::MemoryFactory<int> intFactory = cse::MemoryFactory<int>(5);
  REQUIRE(intFactory.GetSpace() == 5);
  int* Test = intFactory.Allocate();
  int errorVariable = 5;
  int* errorTest = &errorVariable;
  REQUIRE_THROWS_AS(intFactory.Deallocate(errorTest), std::invalid_argument);
  REQUIRE(intFactory.GetSpace() == 4);
  intFactory.Deallocate(Test);
  REQUIRE(intFactory.GetSpace() == 5);
  
}

TEST_CASE("MemoryFactory Max Capacity Usage", "[private_functionality]") {
  SECTION("Testing max factory usage.") {
    cse::MemoryFactory<int> intFactory = cse::MemoryFactory<int>(2);
    int* item1 = intFactory.Allocate(0);
    CHECK(*item1 == 0);
    int* item2 = intFactory.Allocate(1);
    CHECK(*item2 == 1);
    REQUIRE(intFactory.GetSpace() == 0);
    int* item3 = intFactory.Allocate(2);
    REQUIRE(*item3 == 2);
    REQUIRE(intFactory.GetSpace() == 1);

    intFactory.Deallocate(item1);
    intFactory.Deallocate(item2);
    intFactory.Deallocate(item3);
    // Memory Allocated should have doubled after item3 was allocated
    REQUIRE(intFactory.GetSpace() == 4);
  }
}