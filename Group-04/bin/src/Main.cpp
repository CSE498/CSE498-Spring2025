#include <cse/BitVector.hpp>
#include <iostream>

int main() {
  cse::BitVector b(1);
  cse::BitVector::reference r = b[0];
  std::cout << r;
  r = true;
  std::cout << r;
  std::cout << std::endl;
  return 0;
}
