#include <string>

#include "BitVector.hpp"
#include "catch.hpp"

TEST_CASE("Test basic resize operation", "[bitvector]") {
  // Basic constructors with number of bits
  cse::BitVector bv1(8), bc1("0011111111");
  bv1.set();
  CHECK(bv1.size() == 8);

  bv1.resize(10);
  CHECK(bv1.size() == 10);
  CHECK(bv1 == bc1);
}

TEST_CASE("Test basic append and prepend operations", "[bitvector]") {
  cse::BitVector bv1(7), bc1("10000000");
  bv1.append(true);
  CHECK(bv1 == bc1);

  cse::BitVector bv2(7), bc2("00000001");
  bv2.prepend(true);
  CHECK(bv2 == bc2);

  cse::BitVector bv3(16), bc3("101010101010101010");
  bv3.pattern_set(0, 16, std::byte{0b01010101});
  bv3.append(true);
  bv3.prepend(false);
  CHECK(bv3[17]);
  CHECK(bv3 == bc3);
}
