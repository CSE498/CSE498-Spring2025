#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../Group-10/Classes/MemoryFactory.h"

/// Test Initial Construction and Deletion
/// Test Standard Allocation and Deallocation of int
/// Test Standard Allocation and Deallocation of string
/// Test Standard Allocation and Deallocation of a custom struct
/// Test Custom amounts of Allocation with the same objects

TEST_CASE("Test ", "[base]")
{
  cse::MemoryFactory<int> intFactory = cse::MemoryFactory<int>(5);
  REQUIRE(intFactory.GetSpace() == 5);
  int* Test = intFactory.Allocate();
  *Test = 5;
  REQUIRE(intFactory.GetSpace() == 4);
  intFactory.Deallocate(Test);
}