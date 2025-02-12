#pragma once
#include <cstdint>
#include <format>
#include <iostream>
#include <vector>

#include "CseAssert.hpp"

namespace cse {

// Author(s): Kyle Gunger
// BitVector represents a dynamic array of bits, packed into bytes for space
// efficiency. BitVector supports boolean operations on itself with other
// BitVectors of varying sizes.
class BitVector {
 private:
  // The underlying bytes of the vector
  std::vector<std::byte> underlying = {};
  // The number of bits the vector is currently holding
  size_t num_bits = 0;
  // The number of set bits in the BitVector
  size_t num_set = 0;

  // Lookup table for how many bits are 'on' in a byte
  const int8_t BYTE_SET_LOOKUP[256] = {
      0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,  // 0b00001111
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,  // 0b00011111
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,  // have
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  // 0b00111111
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,  // to
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  // put
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  // these stupid comments
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  // 0b01111111
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,  // here
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  // so
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  // that
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  // clang-format
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  // won't
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  // destroy
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  // my nice rectangle.
      4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,  // 0b11111111
  };

  // Keep the bottom "keep" bits of the given byte, discarding the rest and
  // updating the num_set
  void fixup_byte(size_t byte, uint8_t keep);

 public:
  // Author(s): Kyle Gunger
  // BitVector::reference is a reference to a single bit in the vector,
  // providing common bitwise operations as well as decomposing into a boolean
  class reference {
   private:
    // A pointer to the BitVector which created this instance
    BitVector* parent = nullptr;
    // A pointer to the byte where the bit is stored
    std::byte* byte = nullptr;
    // The index of the bit within the byte ((1 << bit_off) & *byte gets the
    // specific bit)
    uint8_t bit_off = 0;

   public:
    // Constructor
    reference(BitVector* bv, std::byte* b, uint8_t o)
        : parent(bv), byte(b), bit_off(o) {}

    // Set the value of this bit
    reference& operator=(bool value);
    // Set the value of this bit
    reference& operator=(const reference& value);
    // Flip the value of this bit
    reference& flip();

    // Get the value of this bit
    operator bool() const;
    // Get the negated value of this bit
    bool operator~() const;

    // Destructor
    ~reference() = default;
  };

  // Default constructor
  BitVector() = default;

  // Constructor
  BitVector(size_t bits) {
    num_bits = bits;
    underlying.resize(bits / 8 + (bits % 8 == 0 ? 0 : 1), std::byte{0});
  }

  // Bit string constructor
  BitVector(std::string bstr, char zero = '0', char one = '1');

  // Copy constructor
  BitVector(const BitVector& bv) {
    underlying = bv.underlying;
    num_bits = bv.num_bits;
    num_set = bv.num_set;
  }

  // Destructor
  ~BitVector() = default;

  // &= operation between two BitVectors
  BitVector& operator&=(const BitVector& rhs);
  // |= operation between two BitVectors
  BitVector& operator|=(const BitVector& rhs);
  // ^= operation between two BitVectors
  BitVector& operator^=(const BitVector& rhs);
  // ~ operation on a BitVector, produces a new BitVector
  BitVector operator~() const;

  // == operator
  bool operator==(const BitVector& rhs) const;

  // != operator
  bool operator!=(const BitVector& rhs) const { return !(*this == rhs); }

  // << operation on a BitVector
  BitVector operator<<(size_t pos) const;
  // <<= operation on a BitVector
  BitVector& operator<<=(size_t pos);
  // >> operation on a BitVector
  BitVector operator>>(size_t pos) const;
  // >>= operation on a BitVector
  BitVector& operator>>=(size_t pos);

  // ostream output on bit vector
  friend std::ostream& operator<<(std::ostream& os, const BitVector& bv);

  // & operation between two BitVectors
  BitVector operator&(const BitVector& rhs) const;
  // | operation between two BitVectors
  BitVector operator|(const BitVector& rhs) const;
  // ^ operation between two BitVectors
  BitVector operator^(const BitVector& rhs) const;

  // Get the bool representation of the bit at idx
  bool operator[](size_t idx) const;
  // Get a reference to the bit at idx
  reference operator[](size_t idx);

  // Copy assignment
  BitVector& operator=(const BitVector& bv);

  // Set count bits in a repeating pattern starting at the index start
  BitVector& pattern_set(size_t start, size_t count, std::byte pattern);

  // Set all bits in the vector to true
  BitVector& set();
  // Set a specific bit in the vector to true
  BitVector& set(size_t pos);
  // Set count bits to true starting at the index start
  BitVector& set(size_t start, size_t count);

  // Set all bits in the vector to false
  BitVector& reset();
  // Set a specific bit in the vector to false
  BitVector& reset(size_t pos);
  // Set count bits to false starting at the index start
  BitVector& reset(size_t start, size_t count);

  // Test a specific bit in the BitVector
  bool test(size_t idx) const;

  // Flip all bits in the BitVector
  BitVector& flip();
  // Flip a specific bit in the BitVector
  BitVector& flip(size_t idx);

  // Returns true if all the bits in the BitVector are true
  bool all() const { return num_set == num_bits; }
  // Returns true if any of the bits in the BitVector are true
  bool any() const { return num_set > 0; }
  // Returns true if none of the bits in the BitVector are true
  bool none() const { return num_set == 0; }
  // Returns the number of set bits in the BitVector
  size_t count() const { return num_set; }
  // Returns the number of bits contained by the BitVector
  size_t size() const { return num_bits; }

  // Returns the number of bits in this std::byte
  inline int8_t BIT_LOOKUP(std::byte b) const {
    return BYTE_SET_LOOKUP[std::to_integer<uint8_t>(b)];
  }

  // Resize the BitVector to the provided size, filling any new bits with the
  // given value
  void resize(size_t size, bool fill = false);
  void resize(size_t size, std::byte fill);

  // Append the given bit to the BitVector
  void append(bool value);
  // Append the provided bit vector at the end of this bit vector
  void append(const BitVector& bv);
  // Prepend the given bit to the BitVector
  void prepend(bool value);
  // Prepend the given BitVector to this bit vector
  void prepend(const BitVector& bv);
};

// IMPL GUARD
#ifdef CSET_IMPLEMENTATION

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

// Bit string constructor
BitVector::BitVector(std::string bstr, char zero, char one) {
  num_bits = bstr.size();
  num_set = 0;
  underlying.resize(num_bits / 8 + (num_bits % 8 == 0 ? 0 : 1), std::byte{0});

  for (size_t i = 0; i < num_bits; ++i) {
    size_t idx = num_bits - (i + 1);
    if (bstr[idx] == one) {
      (*this)[i] = true;
    } else if (bstr[idx] != zero) {
      throw std::invalid_argument(std::format(
          "Unexpected character in bit string (1 = '{}') (0 = '{}'): '{}'", one,
          zero, bstr[idx]));
    }
  }
}

// Get the index as a reference
BitVector::reference BitVector::operator[](size_t idx) {
#ifndef NDEBUG
  if (num_bits <= idx)
    throw std::out_of_range(std::format(
        "Invalid index into BitVector: idx - {}, max - {}", idx, num_bits));
#endif
  return reference(this, &underlying[idx / 8], (uint8_t)(idx % 8));
}

// Get the index as a const bool
bool BitVector::operator[](size_t idx) const {
#ifndef NDEBUG
  if (num_bits <= idx)
    throw std::out_of_range(std::format(
        "Invalid index into BitVector: idx - {}, max - {}", idx, num_bits));
#endif
  const std::byte b = (std::byte{1} << (idx % 8)) & underlying[idx / 8];
  return b != std::byte{0};
}

// Set bits in a pattern
BitVector& BitVector::pattern_set(size_t start, size_t count,
                                  std::byte pattern) {
  if (count == 0)
    return *this;
  else if ((start + count) > num_bits)
    throw std::out_of_range(
        std::format("Invalid range to pattern_set BitVector: start: {}, count: "
                    "{}, number of bits is: {}",
                    start, count, num_bits));

  // Offset the pattern due to where the start bit is
  pattern = (pattern << (start % 8)) | (pattern >> (8 - (start % 8)));

  // Masks for end bytes in the seq
  std::byte bot_mask = std::byte{0b11111111} << (start % 8);
  std::byte top_mask = std::byte{0b11111111};
  if ((start + count) % 8) top_mask >>= (8 - (start + count) % 8);

  // Total bits set in the new sequence
  size_t ps_total = (size_t)BIT_LOOKUP(pattern) * (count / 8);
  ps_total +=
      (size_t)BIT_LOOKUP(pattern & (std::byte{0b11111111} >> (8 - count % 8)));
  // Counter for the number of bytes in the old sequence
  size_t ps_before = 0;

  // Index of the byte we are changing
  size_t idx = start / 8;

  // First byte
  if (start % 8 + count <= 8) {
    // We only need to change one byte in this case
    top_mask = std::byte{0b11111111};
    if (count % 8 != 0) top_mask >>= (8 - (count) % 8);

    bot_mask &= top_mask << (start % 8);
    ps_before = BIT_LOOKUP(underlying[idx] & bot_mask);
    ps_total = BIT_LOOKUP(pattern & bot_mask);

    underlying[idx] = (underlying[idx] & ~bot_mask) | (pattern & bot_mask);

    num_set += ps_total;
    num_set -= ps_before;
    return (*this);
  }

  ps_before += BIT_LOOKUP(underlying[idx] & bot_mask);
  underlying[idx] = (underlying[idx] & ~bot_mask) | (pattern & bot_mask);

  // Loop set
  for (++idx; (idx + 1) * 8 < start + count; ++idx) {
    ps_before += BIT_LOOKUP(underlying[idx]);
    underlying[idx] = pattern;
  }

  // Last byte
  ps_before += BIT_LOOKUP(underlying[idx] & top_mask);
  underlying[idx] = (underlying[idx] & ~top_mask) | (pattern & top_mask);

  num_set += ps_total;
  num_set -= ps_before;

  return *this;
}

// Set all bits in the vector
BitVector& BitVector::set() {
  return pattern_set(0, num_bits, std::byte{0b11111111});
}

// Set a bit in the vector
BitVector& BitVector::set(size_t idx) {
  if (idx >= num_bits)
    throw std::out_of_range(std::format(
        "Attempt to set BitVector at index {}, number of bits is {}", idx,
        num_bits));
  (*this)[idx] = true;
  return *this;
}

// Set bits in the vector within a certain range, starting from
// start and ending at (start + count - 1)
BitVector& BitVector::set(size_t start, size_t count) {
  if ((start + count) > num_bits)
    throw std::out_of_range(
        std::format("Invalid range to set BitVector: start: {}, count: {}, "
                    "number of bits is: {}",
                    start, count, num_bits));
  return pattern_set(start, count, std::byte{0b11111111});
}

// Reset all bits in the vector
BitVector& BitVector::reset() { return pattern_set(0, num_bits, std::byte{0}); }

// Reset a bit in the vector
BitVector& BitVector::reset(size_t idx) {
  if (idx >= num_bits)
    throw std::out_of_range(std::format(
        "Attempt to reset BitVector at index {}, number of bits is {}", idx,
        num_bits));
  (*this)[idx] = false;
  return *this;
}

// Reset bits in the vector within a certain range, starting from
// start and ending at (start + count - 1)
BitVector& BitVector::reset(size_t start, size_t count) {
  if ((start + count) > num_bits)
    throw std::out_of_range(
        std::format("Invalid range to reset BitVector: start: {}, count: {}, "
                    "number of bits is: {}",
                    start, count, num_bits));
  return pattern_set(start, count, std::byte{0});
}

// Test to see if a bit is set
bool BitVector::test(size_t idx) const {
  if (idx >= num_bits)
    throw std::out_of_range(std::format(
        "Attempt to test BitVector at index {}, number of bits is {}", idx,
        num_bits));
  return (*this)[idx];
}

// Flip all bits in the BitVector
BitVector& BitVector::flip() {
  num_set = 0;

  for (size_t i = 0; i < underlying.size(); i++) {
    underlying[i] = underlying[i] ^ std::byte{0b11111111};
    num_set += BIT_LOOKUP(underlying[i]);
  }
  fixup_byte(underlying.size() - 1, num_bits);

  return *this;
}

// Flip a specific bit in the BitVector
BitVector& BitVector::flip(size_t idx) {
  if (idx >= num_bits)
    throw std::out_of_range(std::format(
        "Attempt to flip BitVector at index {}, number of bits is {}", idx,
        num_bits));

  (*this)[idx].flip();

  return *this;
}

// Fix the given byte by mapping bits to zero after keep bits
// e.g. 0b10101010 with keep 3 -> 0b00000010 (top 5 bits are cut off)
// note: keep is modded, so don't worry about putting in too high a number
void BitVector::fixup_byte(size_t byte, uint8_t keep) {
  // No need to cut off if keep is a multiple of 8
  if (keep > 0 && keep % 8 == 0) return;
  // Generate cutoff mask
  std::byte mask = std::byte{0b11111111} >> (8 - (keep % 8));

  // Get set bit diff as well as apply mask
  int8_t diff = BIT_LOOKUP(underlying[byte]);
  underlying[byte] &= mask;
  diff = BIT_LOOKUP(underlying[byte]) - diff;

  // Update num_set
  if (diff < 0)
    num_set -= -diff;
  else
    num_set += diff;
}

// AND the BitVector with another, setting the underlying to
// the product
BitVector& BitVector::operator&=(const BitVector& rhs) {
  size_t i = 0;

  // Main loop doing the anding
  for (; i < underlying.size() && i < rhs.underlying.size(); i++) {
    int8_t diff = BIT_LOOKUP(underlying[i]);
    underlying[i] &= rhs.underlying[i];
    diff = BIT_LOOKUP(underlying[i]) - diff;
    if (diff < 0)
      num_set -= -diff;
    else
      num_set += diff;
  }

  // Fixup the last byte
  if (rhs.num_bits < num_bits)
    fixup_byte(rhs.underlying.size() - 1, rhs.num_bits);
  else
    fixup_byte(i - 1, num_bits);

  // If we stopped before the last byte, all the rest should be assumed zero
  for (; i < underlying.size(); i++) {
    uint8_t diff = BIT_LOOKUP(underlying[i]);
    underlying[i] = std::byte{0};
    num_set -= diff;
  }

  return *this;
}

// OR the BitVector with another, setting the underlying to
// the product
BitVector& BitVector::operator|=(const BitVector& rhs) {
  size_t i = 0;

  // Main loop doing the or
  for (; i < underlying.size() - 1 && i < rhs.underlying.size() - 1; i++) {
    int8_t diff = BIT_LOOKUP(underlying[i]);
    underlying[i] |= rhs.underlying[i];
    diff = BIT_LOOKUP(underlying[i]) - diff;
    // diff can never be less than zero, since we don't lose bits when we or
    num_set += diff;
  }

  // Or the last byte with a mask
  if (i < underlying.size()) {
    int8_t diff = BIT_LOOKUP(underlying[i]);
    uint8_t mask_num = (8 - std::min(num_bits, rhs.num_bits) % 8);
    std::byte or_mask = mask_num != 8 ? std::byte{0b11111111} >> mask_num
                                      : std::byte{0b11111111};
    underlying[i] |= (rhs.underlying[i] & or_mask);
    diff = BIT_LOOKUP(underlying[i]) - diff;
    // diff can never be less than zero, since we don't lose bits when we or
    num_set += diff;
  }

  return *this;
}

// XOR the BitVector with another, setting the underlying to
// the product
BitVector& BitVector::operator^=(const BitVector& rhs) {
  size_t i = 0;

  // Main loop doing the xor
  for (; i < underlying.size() - 1 && i < rhs.underlying.size() - 1; i++) {
    int8_t diff = -BIT_LOOKUP(underlying[i]);
    underlying[i] ^= rhs.underlying[i];
    diff += BIT_LOOKUP(underlying[i]);
    if (diff < 0)
      num_set -= -diff;
    else
      num_set += diff;
  }

  // Xor the last byte with a mask
  if (i < underlying.size()) {
    int8_t diff = -BIT_LOOKUP(underlying[i]);
    uint8_t mask_num = (8 - std::min(num_bits, rhs.num_bits) % 8);
    std::byte xor_mask = mask_num != 8 ? std::byte{0b11111111} >> mask_num
                                       : std::byte{0b11111111};
    underlying[i] ^= (rhs.underlying[i] & xor_mask);
    diff += BIT_LOOKUP(underlying[i]);
    // diff can never be less than zero, since we don't lose bits when we or
    if (diff < 0)
      num_set -= -diff;
    else
      num_set += diff;
  }

  return *this;
}

// Produce a BitVector with all bits flipped
BitVector BitVector::operator~() const {
  BitVector out(num_bits);

  for (size_t i = 0; i < underlying.size(); i++) {
    out.underlying[i] = underlying[i] ^ std::byte{0b11111111};
    out.num_set += BIT_LOOKUP(out.underlying[i]);
  }
  out.fixup_byte(out.underlying.size() - 1, out.num_bits);

  return out;
}

// equals operator
bool BitVector::operator==(const BitVector& rhs) const {
  if (rhs.num_bits != num_bits || rhs.num_set != num_set) return false;

  size_t i = 0;
  for (; i < underlying.size() - 1; ++i) {
    if (underlying[i] != rhs.underlying[i]) return false;
  }

  uint8_t mask_num = (8 - std::min(num_bits, rhs.num_bits) % 8);
  std::byte mask =
      mask_num != 8 ? std::byte{0b11111111} >> mask_num : std::byte{0b11111111};

  return (underlying[i] & mask) == (rhs.underlying[i] & mask);
}

// Copy assign
BitVector& BitVector::operator=(const BitVector& bv) {
  underlying = bv.underlying;
  num_bits = bv.num_bits;
  num_set = bv.num_set;
  return *this;
}

// AND operator with another BitVector
BitVector BitVector::operator&(const BitVector& rhs) const {
  if (num_bits < rhs.num_bits) {
    BitVector out = rhs;
    out &= *this;
    return out;
  }

  BitVector out = *this;
  out &= rhs;
  return out;
}

// OR operator with another BitVector
BitVector BitVector::operator|(const BitVector& rhs) const {
  if (num_bits < rhs.num_bits) {
    BitVector out = rhs;
    out |= *this;
    return out;
  }

  BitVector out = *this;
  out |= rhs;
  return out;
}

// XOR operator with another BitVector
BitVector BitVector::operator^(const BitVector& rhs) const {
  if (num_bits < rhs.num_bits) {
    BitVector out = rhs;
    out ^= *this;
    return out;
  }

  BitVector out = *this;
  out ^= rhs;
  return out;
}

// Left-shift and set operator
BitVector& BitVector::operator<<=(size_t pos) {
  if (pos == 0)
    return *this;
  else if (pos >= num_bits) {
    set(false);
    return *this;
  }

  num_set = 0;
  // The first byte that has information we will keep
  size_t skip = pos / 8;
  // The number of bits to interpolate between shift and shift+1 bytes
  uint8_t slide = pos % 8;
  // The index of the byte we are modifying
  size_t i = 0;
  size_t max = underlying.size();

  if (slide == 0) {
    // Loop where we only need to copy bytes with no tweaks
    for (; i + skip < max; ++i) {
      size_t idx = max - (i + 1);
      underlying[idx] = underlying[idx - skip];
      num_set += BIT_LOOKUP(underlying[idx]);
    }
  } else {
    // Pre loop byte fixing
    size_t idx = max - (i + 1);
    uint8_t mask_num = (8 - (num_bits % 8));
    std::byte mask = mask_num != 8 ? std::byte{0b11111111} >> mask_num
                                   : std::byte{0b11111111};

    underlying[idx] = underlying[idx - skip] << slide;
    underlying[idx] |= underlying[idx - (skip + 1)] >> (8 - slide);
    underlying[idx] &= mask;
    num_set += BIT_LOOKUP(underlying[idx]);

    ++i;

    // Loop when we need to combine neighboring bytes
    for (; i + skip < max; ++i) {
      size_t idx = max - (i + 1);
      underlying[idx] = underlying[idx - skip] << slide;
      underlying[idx] |= underlying[idx - (skip + 1)] >> (8 - slide);
      num_set += BIT_LOOKUP(underlying[idx]);
    }
  }

  // Clear the rest of the bytes (<< fills with 0s from the right)
  for (; i < max; ++i) {
    underlying[max - (i + 1)] = std::byte{0};
  }

  return *this;
}

// Right-shift and set operator
BitVector& BitVector::operator>>=(size_t pos) {
  if (pos == 0)
    return *this;
  else if (pos >= num_bits) {
    set(false);
    return *this;
  }

  num_set = 0;
  // The first byte that has information we will keep
  size_t skip = pos / 8;
  // The number of bits to interpolate between shift and shift+1 bytes
  uint8_t slide = pos % 8;
  // The index of the byte we are modifying
  size_t i = 0;

  if (slide == 0) {
    // Loop where we only need to copy bytes with no tweaks
    for (; i + skip < underlying.size(); ++i) {
      underlying[i] = underlying[i + skip];
      num_set += BIT_LOOKUP(underlying[i]);
    }
  } else {
    // Loop when we need to combine neighboring bytes
    for (; i + skip < underlying.size() - 1; ++i) {
      underlying[i] = underlying[i + skip] >> slide;
      underlying[i] |= underlying[i + skip + 1] << (8 - slide);
      num_set += BIT_LOOKUP(underlying[i]);
    }

    // Post loop byte fixing
    underlying[i] = underlying[i + skip] >> slide;
    num_set += BIT_LOOKUP(underlying[i]);
    ++i;
  }

  // Clear the rest of the bytes (>> fills with 0s from the left)
  for (; i < underlying.size(); ++i) {
    underlying[i] = std::byte{0};
  }

  return *this;
}

// Left-shift operator
BitVector BitVector::operator<<(size_t pos) const {
  BitVector out = *this;
  out <<= pos;
  return out;
}

// Right-shift operator
BitVector BitVector::operator>>(size_t pos) const {
  BitVector out = *this;
  out >>= pos;
  return out;
}

// How to format when outputting to a stream
// Current decision: groups of 8 bits space separated,
// and with max groupings of 32 bits per line
std::ostream& operator<<(std::ostream& os, const BitVector& bv) {
  int byte = 0;
  for (auto b = bv.underlying.rbegin(); b != bv.underlying.rend(); ++b) {
    if (byte % 4 == 3)
      os << std::format("{:0>8b}\n", std::to_integer<uint8_t>(*b));
    else {
      os << std::format("{:0>8b}", std::to_integer<uint8_t>(*b));
      if (b != (bv.underlying.rend() - 1)) os << " ";
    }
    byte++;
  }

  return os;
}

// Resize this BitVector
void BitVector::resize(size_t size, std::byte fill) {
  uint8_t over = size % 8;
  size_t bytes = (size / 8) + (over ? 1 : 0);

  if (size > num_bits) {
    if (num_bits % 8) {
      // Add bits from the pattern to the end of the last byte
      int8_t diff = BIT_LOOKUP(underlying.back());
      underlying.back() |= fill << (num_bits % 8);
      diff -= BIT_LOOKUP(underlying.back());

      // Update num_set
      num_set += diff;
      fill = (fill >> (8 - (num_bits % 8))) | (fill << (num_bits % 8));
    }

    // Add to num set based on the number of bytes we will be appending on to
    // underlying
    num_set += BIT_LOOKUP(fill) * (bytes - underlying.size());
  }

  underlying.resize(bytes, fill);
  num_bits = size;
  fixup_byte(underlying.size() - 1, num_bits);
}

// Resize this bitvector, optionally filling with bits
void BitVector::resize(size_t size, bool fill) {
  std::byte b = fill ? std::byte{0b11111111} : std::byte{0};
  resize(size, b);
}

// Append a bit to this BitVector
void BitVector::append(bool value) {
  if (num_bits % 8 == 0) underlying.push_back(std::byte{0});
  num_bits++;
  (*this)[num_bits - 1] = value;
}

// Append a BitVector to this BitVector
void BitVector::append(const BitVector& bv) {
  if (bv.num_bits == 0) return;

  // Pack bits into the last byte if there is room
  uint8_t over = num_bits % 8;
  if (over > 0) underlying.back() |= bv.underlying[0] << over;

  // Loop to push new bytes on to the back
  for (size_t i = 0; i < bv.underlying.size() - 1; ++i) {
    std::byte add = bv.underlying[i];
    // Merge with next byte if offset
    if (over > 0) {
      add = add >> (8 - over);
      add |= bv.underlying[i + 1] << over;
    }
    underlying.push_back(add);
  }

  // The number of bits we had in our upper byte to begin with
  uint8_t open_slots = (8 - (num_bits % 8)) % 8;
  // The number of bits taken up in the upper byte of bv
  uint8_t req_slots = 8 - (bv.num_bits % 8);
  // Add the remaining bits if required
  if (req_slots < open_slots) {
    std::byte add = bv.underlying.back() >> (8 - over);
    underlying.push_back(add);
  }

  num_bits += bv.num_bits;
  num_set += bv.num_set;
}

// Prepend a single bit to the BitVector
void BitVector::prepend(bool value) {
  if (num_bits % 8 == 0) underlying.push_back(std::byte{0});
  num_bits++;
  *this <<= 1;
  (*this)[0] = value;
}

// Prepend another BitVector to the BitVector
void BitVector::prepend(const BitVector& bv) {
  BitVector tmp = *this;
  *this = bv;
  append(tmp);
}

#endif

};  // namespace cse
