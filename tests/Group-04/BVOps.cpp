#include <string>

#include "BitVector.hpp"
#include "catch.hpp"

TEST_CASE("Test basic BitVector constructors", "[bitvector]") {
  // Basic constructors with number of bits
  cse::BitVector bv1;
  cse::BitVector bv2(8);
  cse::BitVector bv3(13);

  // Constructor with bit string
  std::string bstr = "100110101110001111011";
  cse::BitVector bv4(bstr);
  cse::BitVector bv5("abbaababaaabbbaaaabaa", 'b', 'a');

  CHECK(bv4.size() == bstr.size());
  CHECK(bv4 == bv5);
}

TEST_CASE("Test setting bits", "[bitvector]") {
  // Single byte case
  cse::BitVector bv1(8);

  for (size_t i = 0; i < bv1.size(); i++) {
    bv1[i] = true;
    CHECK(bv1[i] == true);
    CHECK(bv1.count() == i + 1);
  }

  // Set all function (single byte)
  cse::BitVector bv2(8), bc2("11111111");
  bv2.set();

  CHECK(bv2.count() == bv2.size());
  CHECK(bv2 == bc2);

  // Single byte case (set function)
  cse::BitVector bv3(8);

  for (size_t i = 0; i < bv3.size(); i++) {
    bv3.set(i);
    CHECK(bv3.test(i) == true);
    CHECK(bv3.count() == i + 1);
  }

  // Single byte case (ranged set function)
  cse::BitVector bv4(8), bc4("00111000");
  bv4.set(3, 3);
  CHECK(bv4.count() == bc4.count());
  CHECK(bv4 == bc4);

  // Set all function (multi-byte case)
  cse::BitVector bv5(16), bc5("1111111111111111");
  bv5.set();

  CHECK(bv5.count() == bv5.size());
  CHECK(bv5 == bc5);

  // Multi byte case (set function)
  cse::BitVector bv6(16);

  for (size_t i = 0; i < bv6.size(); i++) {
    bv6.set(i);
    CHECK(bv6.test(i));
    CHECK(bv6.count() == i + 1);
  }

  // Multi byte case (ranged set function)
  cse::BitVector bv7(16), bc7("0000001111111000");
  bv7.set(3, 7);
  CHECK(bv7.count() == bc7.count());
  CHECK(bv7 == bc7);
}

TEST_CASE("Test pattern setting bits", "[bitvector]") {
  // Pattern set whole byte
  cse::BitVector bv1(8), bc1("10010110");
  bv1.pattern_set(0, 8, std::byte{0b10010110});
  CHECK(bv1.count() == 4);
  CHECK(bv1 == bc1);

  // Pattern set part of byte
  cse::BitVector bv2(8), bc2("00000110");
  bv2.pattern_set(0, 3, std::byte{0b01010110});
  CHECK(bv2.count() == bc2.count());
  CHECK(bv2 == bc2);

  // Pattern set part of byte (offset)
  cse::BitVector bv3(8), bc3("00010000");
  bv3.pattern_set(4, 3, std::byte{0b10110001});
  CHECK(bv3.count() == bc3.count());
  CHECK(bv3 == bc3);

  // Pattern set multiple bytes
  cse::BitVector bv4(16), bc4("1011000010110000");
  bv4.pattern_set(0, 16, std::byte{0b10110000});
  CHECK(bv4.count() == bc4.count());
  CHECK(bv4 == bc4);

  // Pattern set multiple bytes (offset)
  cse::BitVector bv5(16), bc5("0000010010100000");
  bv5.pattern_set(5, 6, std::byte{0b11100101});
  CHECK(bv5.count() == bc5.count());
  CHECK(bv5 == bc5);
}

TEST_CASE("Test resetting bits", "[bitvector]") {
  // Single byte case
  cse::BitVector bv1(8);
  bv1[0] = 1;
  bv1[1] = 1;
  bv1[4] = 1;
  bv1[7] = 1;

  CHECK(bv1.count() == 4);

  bv1.reset();

  cse::BitVector bv2(8);

  CHECK(bv1.count() == 0);
  CHECK(bv1 == bv2);
  CHECK(!bv2.test(0));
  CHECK(!bv2.test(1));
  CHECK(!bv2.test(4));
  CHECK(!bv2.test(7));
}

void AND_TEST(cse::BitVector& a, cse::BitVector& b) {
  cse::BitVector chk(a.size());

  for (size_t i = 0; i < ((size_t)1 << a.size()); i++) {
    for (size_t j = 0; j < ((size_t)1 << b.size()); j++) {
      a.reset();
      b.reset();
      chk.reset();

      for (size_t k = 0; (i >> k) > 0; k++) {
        if ((i >> k) & 1) {
          a[k] = true;
        }
      }

      for (size_t k = 0; (j >> k) > 0; k++) {
        if ((j >> k) & 1) {
          b[k] = true;
          if (k < a.size() && a[k] == true) chk[k] = true;
        }
      }

      a &= b;

      CHECK(a == chk);
      CHECK(a.count() == chk.count());
    }
  }
}

TEST_CASE("Test AND operation on BitVectors", "[bitvector]") {
  // Test all combos of bits (same size)
  cse::BitVector a1(9), b1(9);
  AND_TEST(a1, b1);

  // Test all combos of bits (a < b)
  cse::BitVector a2(7), b2(9);
  AND_TEST(a2, b2);

  // Test all combos of bits (b > a)
  cse::BitVector a3(9), b3(7);
  AND_TEST(a3, b3);
}

void OR_TEST(cse::BitVector& a, cse::BitVector& b) {
  cse::BitVector chk(a.size());

  for (size_t i = 0; i < ((size_t)1 << a.size()); i++) {
    for (size_t j = 0; j < ((size_t)1 << b.size()); j++) {
      a.reset();
      b.reset();
      chk.reset();

      for (size_t k = 0; (i >> k) > 0; k++) {
        if ((i >> k) & 1) {
          a[k] = true;
          chk[k] = true;
        }
      }

      for (size_t k = 0; (j >> k) > 0; k++) {
        if ((j >> k) & 1) {
          b[k] = true;
          if (k < chk.size()) chk[k] = true;
        }
      }

      a |= b;

      CHECK(a == chk);
      CHECK(a.count() == chk.count());
    }
  }
}

TEST_CASE("Test OR operation on BitVectors", "[bitvector]") {
  // Test all combos of bits
  cse::BitVector a1(9), b1(9);
  OR_TEST(a1, b1);

  // Test all combos of bits (a < b)
  cse::BitVector a2(7), b2(9);
  OR_TEST(a2, b2);

  // Test all combos of bits (b > a)
  cse::BitVector a3(9), b3(7);
  OR_TEST(a3, b3);
}

void XOR_TEST(cse::BitVector& a, cse::BitVector& b) {
  cse::BitVector chk(a.size());

  for (size_t i = 0; i < ((size_t)1 << a.size()); i++) {
    for (size_t j = 0; j < ((size_t)1 << b.size()); j++) {
      a.reset();
      b.reset();
      chk.reset();

      for (size_t k = 0; (i >> k) > 0; k++) {
        if ((i >> k) & 1) {
          a[k] = true;
          chk[k] = true;
        }
      }

      for (size_t k = 0; (j >> k) > 0; k++) {
        if ((j >> k) & 1) {
          b[k] = true;
          if (k < chk.size()) chk[k] = !chk[k];
        }
      }

      a ^= b;

      CHECK(a == chk);
      CHECK(a.count() == chk.count());
    }
  }
}

TEST_CASE("Test bitwise XOR on BitVectors", "[bitvector]") {
  // Test all combos of bits
  cse::BitVector a1(9), b1(9);
  XOR_TEST(a1, b1);

  // Test all combos of bits (a < b)
  cse::BitVector a2(7), b2(9);
  XOR_TEST(a2, b2);
  cse::BitVector a3(4), b3(5);
  XOR_TEST(a3, b3);

  // Test all combos of bits (b > a)
  cse::BitVector a4(9), b4(7);
  XOR_TEST(a4, b4);
  cse::BitVector a5(5), b5(4);
  XOR_TEST(a5, b5);
}

TEST_CASE("Test bitwise shifting", "[bitvector]") {
  // One byte
  cse::BitVector bv1(8), bc1("10101000");
  bv1.pattern_set(0, 8, std::byte{0b01010101});
  bv1 <<= 3;
  CHECK(bv1 == bc1);

  // Multi-byte
  cse::BitVector bv2(14), bc2("10101010000000");
  bv2.pattern_set(0, 14, std::byte{0b01010101});
  bv2 <<= 7;
  CHECK(bv2 == bc2);
}

TEST_CASE("Test bitwise NOT", "[bitvector]") {
  // One Byte
  cse::BitVector bv1(8), bc1("01010001");
  bv1.pattern_set(0, 8, std::byte{0b10101110});
  CHECK(bc1 == ~bv1);
  bv1.flip();
  CHECK(bc1 == bv1);

  cse::BitVector bv2(21), bc2(21);
  bv2.pattern_set(0, 21, std::byte{0b01101011});
  bc2 = bv2;

  bv2.flip(6, 13);
  for (size_t i = 6; i < 19; i++) {
    bc2.flip(i);
  }

  CHECK(bv2 == bc2);
}
