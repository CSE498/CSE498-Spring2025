#include <iostream>
#include <test1.hpp>

int main() {
  cse::BitVector bv(8);
  bv.set(true);

  std::cout << bits(bv) << std::endl;

  return 0;
}
