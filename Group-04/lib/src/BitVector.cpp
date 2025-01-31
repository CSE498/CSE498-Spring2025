#include <cse/BitVector.hpp>
#include <cstdint>
#include <iostream>

namespace cse {

//
// Reference functions
//

// Convert a reference into a boolean
BitVector::reference::operator bool() const {
  std::byte b = (std::byte{1} << bit_off) & *byte;
  if (b == std::byte{0}) return false;
  return true;
}

// Get the inverse of this reference's boolean value
bool BitVector::reference::operator~() const {
  return !(this->operator bool());
}

// Assign a boolean value to a reference
BitVector::reference& BitVector::reference::operator=(bool value) {
  if (*this != value) {
    std::byte mask = std::byte{1} << bit_off;
    if (value) {
      *byte |= mask;
      parent->num_set++;
    } else {
      *byte ^= mask;
      parent->num_set--;
    }
  }

  return *this;
}

// Assign a reference value to a reference
BitVector::reference& BitVector::reference::operator=(
    const BitVector::reference& value) {
  return this->operator=(value.operator bool());
}

// Flip the bit
BitVector::reference& BitVector::reference::flip() {
  (*this) = !(*this);
  return *this;
}

//
// BitVector functions
//

// Get the index as a reference
BitVector::reference BitVector::operator[](size_t idx) {
  return reference(this, &underlying[idx / 8], (uint8_t)(idx % 8));
}

// Get the index as a const bool
bool BitVector::operator[](size_t idx) const {
  const std::byte b = (std::byte{1} << (idx % 8)) & underlying[idx / 8];
  return b != std::byte{0};
}

// Set all bits in the vector
BitVector& BitVector::set(bool value) {
  std::byte replace = std::byte{0};

  if (value == true) {
    replace = std::byte{0b11111111};
    num_set = num_bits;
  } else
    num_set = 0;

  for (std::byte& b : underlying) {
    b = replace;
  }
  underlying.back() = underlying.back() >> (8 - (num_bits % 8));

  return *this;
}

// Set a bit in the vector
BitVector& BitVector::set(size_t idx, bool value) {
  if (idx < num_bits) (*this)[idx] = value;
  return *this;
}

// Set bits in the vector within a certain range, starting from
// start and ending at (start + count - 1)
BitVector& BitVector::set(size_t start, size_t count, bool value) {
  // const std::byte rep_true = std::byte{0b11111111};
  // const std::byte rep_false = std::byte{0b00000000};
  // TODO better impl, using byte setting instead of bit setting
  for (; start < count && start < num_bits; start++) {
    (*this)[start] = value;
  }

  return *this;
}

};  // namespace cse
