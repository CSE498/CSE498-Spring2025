#include <assert.h>

#include <app/BVTest.hpp>
#include <cse/BitVector.hpp>
#include <iostream>
#include <string>

const std::string TEST_GUARD = "****************\n";

void test_bitvect_1() {
  std::cout << TEST_GUARD;
  std::cout << "TEST 1 - Logical AND\n";

  cse::BitVector a(8);
  cse::BitVector b(8);

  std::cout
      << "*** 1a - same bit length (one byte) (all different value) ***\n";

  cse::BitVector c1(8);

  for (uint16_t i = 0; i < 256; ++i) {
    for (uint16_t j = 0; j < 256; j++) {
      a.set(false);
      b.set(false);
      c1.set(false);

      for (uint16_t k = 0; k < 8; ++k) {
        if (((i >> k) & 1) == 1) a[k] = true;
      }

      for (uint16_t k = 0; k < 8; ++k) {
        if (((j >> k) & 1) == 1) {
          b[k] = true;
          if (a[k]) c1[k] = true;
        }
      }

      b &= a;

      if (b != c1 || b.count() != c1.count()) {
        std::cout << "a - " << a << " count: " << a.count() << "\n";
        std::cout << "b - " << b << " count: " << b.count() << "\n";
        std::cout << "c - " << c1 << " count: " << c1.count() << "\n";
        std::cout << "TEST FAILED\n";
        return;
      }
    }
  }

  std::cout << "*** 1a - OK ***\n";

  std::cout << "*** 1b - diff bit len (one byte) (all different value) ***\n";

  cse::BitVector d(7);
  cse::BitVector e(4);
  cse::BitVector c2(4);
  cse::BitVector c3(7);

  for (uint16_t i = 0; i < 128; ++i) {
    for (uint16_t j = 0; j < 16; j++) {
      d.set(false);
      e.set(false);
      c2.set(false);

      for (uint16_t k = 0; k < 7; ++k) {
        if (((i >> k) & 1) == 1) d[k] = true;
      }

      for (uint16_t k = 0; k < 4; ++k) {
        if (((j >> k) & 1) == 1) {
          e[k] = true;
          if (d[k]) c2[k] = true;
        }
      }

      e &= d;

      if (e != c2 || e.count() != c2.count()) {
        std::cout << "d - " << d << " count: " << d.count() << "\n";
        std::cout << "e - " << e << " count: " << e.count() << "\n";
        std::cout << "c - " << c2 << " count: " << c2.count() << "\n";
        std::cout << "TEST FAILED\n";
        return;
      }
    }
  }

  for (uint16_t i = 0; i < 128; ++i) {
    for (uint16_t j = 0; j < 16; j++) {
      d.set(false);
      e.set(false);
      c3.set(false);

      for (uint16_t k = 0; k < 7; ++k) {
        if (((i >> k) & 1) == 1) d[k] = true;
      }

      for (uint16_t k = 0; k < 4; ++k) {
        if (((j >> k) & 1) == 1) {
          e[k] = true;
          if (d[k]) c3[k] = true;
        }
      }

      d &= e;

      if (d != c3 || d.count() != c3.count()) {
        std::cout << "d - " << d << " count: " << d.count() << "\n";
        std::cout << "e - " << e << " count: " << e.count() << "\n";
        std::cout << "c - " << c3 << " count: " << c3.count() << "\n";
        std::cout << "TEST FAILED\n";
        return;
      }
    }
  }
  std::cout << "*** 1b - OK ***\n";

  std::cout << TEST_GUARD;
}

void test_bitvect_2() {
  std::cout << TEST_GUARD;
  std::cout << "TEST 2 - Logical OR\n";

  cse::BitVector a(8);
  cse::BitVector b(8);
  cse::BitVector com(8);

  std::cout << "*** 2a - same bit length (all different value) ***\n";

  for (uint16_t i = 0; i < 256; ++i) {
    for (uint16_t j = 0; j < 256; j++) {
      a.set(false);
      b.set(false);
      com.set(false);

      for (uint16_t k = 0; k < 8; ++k) {
        if (((i >> k) & 1) == 1) {
          a[k] = true;
          com[k] = true;
        }
      }

      for (uint16_t k = 0; k < 8; ++k) {
        if (((j >> k) & 1) == 1) {
          b[k] = true;
          com[k] = true;
        }
      }

      b |= a;

      if (b != com || b.count() != com.count()) {
        std::cout << "a - " << a << " count: " << a.count() << "\n";
        std::cout << "b - " << b << " count: " << b.count() << "\n";
        std::cout << "c - " << com << " count: " << com.count() << "\n";
        std::cout << "TEST FAILED\n";
        return;
      }
    }
  }

  std::cout << "*** 2a - OK ***\n";

  std::cout << "*** 2b - diff bit len (one byte) (all different value) ***\n";

  cse::BitVector d(7);
  cse::BitVector e(4);
  cse::BitVector c2(4);
  cse::BitVector c3(7);

  for (uint16_t i = 0; i < 128; ++i) {
    for (uint16_t j = 0; j < 16; j++) {
      d.set(false);
      e.set(false);
      c2.set(false);

      for (uint16_t k = 0; k < 7; ++k) {
        if (((i >> k) & 1) == 1) {
          d[k] = true;
        }
      }

      for (uint16_t k = 0; k < 4; ++k) {
        if (((j >> k) & 1) == 1) {
          e[k] = true;
          c2[k] = true;
        } else if (d[k])
          c2[k] = true;
      }

      e |= d;

      if (e != c2 || e.count() != c2.count()) {
        std::cout << "d - " << d << " count: " << d.count() << "\n";
        std::cout << "e - " << e << " count: " << e.count() << "\n";
        std::cout << "c - " << c2 << " count: " << c2.count() << "\n";
        std::cout << "TEST FAILED\n";
        return;
      }
    }
  }

  for (uint16_t i = 0; i < 128; ++i) {
    for (uint16_t j = 0; j < 16; j++) {
      d.set(false);
      e.set(false);
      c3.set(false);

      for (uint16_t k = 0; k < 7; ++k) {
        if (((i >> k) & 1) == 1) {
          d[k] = true;
          c3[k] = true;
        }
      }

      for (uint16_t k = 0; k < 4; ++k) {
        if (((j >> k) & 1) == 1) {
          e[k] = true;
          c3[k] = true;
        }
      }

      d |= e;

      if (d != c3 || d.count() != c3.count()) {
        std::cout << "d - " << d << " count: " << d.count() << "\n";
        std::cout << "e - " << e << " count: " << e.count() << "\n";
        std::cout << "c - " << c3 << " count: " << c3.count() << "\n";
        std::cout << "TEST FAILED\n";
        return;
      }
    }
  }
  std::cout << "*** 2b - OK ***\n";

  std::cout << TEST_GUARD;
}

void test_bitvect_3() {
  std::cout << TEST_GUARD;
  std::cout << "TEST 3 - Logical XOR\n";

  cse::BitVector a(8);
  cse::BitVector b(8);
  cse::BitVector com(8);

  std::cout << "*** 3a - same bit length (all different value) ***\n";

  for (uint16_t i = 0; i < 256; ++i) {
    for (uint16_t j = 0; j < 256; j++) {
      a.set(false);
      b.set(false);
      com.set(false);

      for (uint16_t k = 0; k < 8; ++k) {
        if (((i >> k) & 1) == 1) {
          a[k] = true;
          com[k] = true;
        }
      }

      for (uint16_t k = 0; k < 8; ++k) {
        if (((j >> k) & 1) == 1) {
          b[k] = true;
          if (com[k])
            com[k] = false;
          else
            com[k] = true;
        }
      }

      b ^= a;

      if (b != com || b.count() != com.count()) {
        std::cout << "a - " << a << " count: " << a.count() << "\n";
        std::cout << "b - " << b << " count: " << b.count() << "\n";
        std::cout << "c - " << com << " count: " << com.count() << "\n";
        std::cout << "TEST FAILED\n";
        return;
      }
    }
  }

  std::cout << "*** 3a - OK ***\n";

  std::cout << "*** 3b - diff bit len (one byte) (all different value) ***\n";

  cse::BitVector d(7);
  cse::BitVector e(4);
  cse::BitVector c2(4);
  cse::BitVector c3(7);

  for (uint16_t i = 0; i < 128; ++i) {
    for (uint16_t j = 0; j < 16; j++) {
      d.set(false);
      e.set(false);
      c2.set(false);

      for (uint16_t k = 0; k < 7; ++k) {
        if (((i >> k) & 1) == 1) d[k] = true;
      }

      for (uint16_t k = 0; k < 4; ++k) {
        if (((j >> k) & 1) == 1) {
          e[k] = true;
          if (d[k]) c2[k] = true;
        }
      }

      e ^= d;

      if (e != c2 || e.count() != c2.count()) {
        std::cout << "d - " << d << " count: " << d.count() << "\n";
        std::cout << "e - " << e << " count: " << e.count() << "\n";
        std::cout << "c - " << c2 << " count: " << c2.count() << "\n";
        std::cout << "TEST FAILED\n";
        return;
      }
    }
  }

  for (uint16_t i = 0; i < 128; ++i) {
    for (uint16_t j = 0; j < 16; j++) {
      d.set(false);
      e.set(false);
      c3.set(false);

      for (uint16_t k = 0; k < 7; ++k) {
        if (((i >> k) & 1) == 1) d[k] = true;
      }

      for (uint16_t k = 0; k < 4; ++k) {
        if (((j >> k) & 1) == 1) {
          e[k] = true;
          if (d[k]) c3[k] = true;
        }
      }

      d ^= e;

      if (d != c3 || d.count() != c3.count()) {
        std::cout << "d - " << d << " count: " << d.count() << "\n";
        std::cout << "e - " << e << " count: " << e.count() << "\n";
        std::cout << "c - " << c3 << " count: " << c3.count() << "\n";
        std::cout << "TEST FAILED\n";
        return;
      }
    }
  }
  std::cout << "*** 3b - OK ***\n";

  std::cout << TEST_GUARD;
}

void test_bitvect_4() {
  cse::BitVector a(16);
  cse::BitVector b(7);

  a.set();
  b.set();
}

void test_bitvect() {
  test_bitvect_1();
  test_bitvect_2();
  test_bitvect_3();
  test_bitvect_4();
}
