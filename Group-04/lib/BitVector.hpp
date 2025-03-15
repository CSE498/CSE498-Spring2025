#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

#include "CseAssert.hpp"

namespace cse {

// A std::byte filled with ones
constexpr std::byte ALL_ONE = std::byte{0xFF};
// A std::byte filled with zeros
constexpr std::byte ALL_ZERO = std::byte{0};
// One
constexpr std::byte ONE_ONE = std::byte{1};
// Number of bits per element in the underlying vector
constexpr size_t BITS_PER_EL = 8;

// Author(s): Kyle Gunger
// BitVector represents a dynamic array of bits, packed into bytes for space
// efficiency. BitVector supports boolean operations on itself with other
// BitVectors of varying sizes.
class BitVector {
 private:
  // The m_underlying bytes of the vector
  std::vector<std::byte> m_underlying = {};
  // The number of bits the vector is currently holding
  size_t m_num_bits = 0;
  // The number of set bits in the BitVector
  size_t m_num_set = 0;

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
  // updating the m_num_set
  void truncate_byte(size_t byte, uint8_t keep);

  // Manages the case in pattern set where
  // only one byte needs changing
  BitVector& pattern_set_one(size_t start, size_t count, std::byte pattern);

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
    m_num_bits = bits;
    m_underlying.resize(bits / BITS_PER_EL + (bits % BITS_PER_EL == 0 ? 0 : 1),
                        ALL_ZERO);
  }

  // Bit string constructor
  BitVector(std::string bstr, char zero = '0', char one = '1');

  // Copy constructor
  BitVector(const BitVector& bv) {
    m_underlying = bv.m_underlying;
    m_num_bits = bv.m_num_bits;
    m_num_set = bv.m_num_set;
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

  // Add a BitVector to the end of this one
  BitVector& operator+=(const BitVector& bv);
  // Add a BitVector to a copy of this one, producing a new BitVector
  BitVector operator+(const BitVector& bv) const;

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
  // Flip count bits starting at index start
  BitVector& flip(size_t start, size_t count);

  // Returns true if all the bits in the BitVector are true
  bool all() const { return m_num_set == m_num_bits; }
  // Returns true if any of the bits in the BitVector are true
  bool any() const { return m_num_set > 0; }
  // Returns true if none of the bits in the BitVector are true
  bool none() const { return m_num_set == 0; }
  // Returns the number of set bits in the BitVector
  size_t count() const { return m_num_set; }
  // Returns the number of bits contained by the BitVector
  size_t size() const { return m_num_bits; }

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
#ifdef CSE4_IMPL

//
// Reference functions
//

// Convert a reference into a boolean
BitVector::reference::operator bool() const {
  std::byte b = (ONE_ONE << bit_off) & *byte;
  return !(b == ALL_ZERO);
}

// Get the inverse of this reference's boolean value
bool BitVector::reference::operator~() const {
  return !(this->operator bool());
}

// Assign a boolean value to a reference
BitVector::reference& BitVector::reference::operator=(bool value) {
  if (*this != value) {
    std::byte mask = ONE_ONE << bit_off;
    if (value) {
      *byte |= mask;
      parent->m_num_set++;
    } else {
      *byte ^= mask;
      parent->m_num_set--;
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
  m_num_bits = bstr.size();
  m_num_set = 0;
  m_underlying.resize(
      m_num_bits / BITS_PER_EL + (m_num_bits % BITS_PER_EL == 0 ? 0 : 1),
      ALL_ZERO);

  for (size_t i = 0; i < m_num_bits; ++i) {
    size_t idx = m_num_bits - (i + 1);
    if (bstr[idx] == one) {
      (*this)[i] = true;
    } else {
      cse_assert_eq(
          bstr[idx], zero,
          std::format(
              "Unexpected character in bit string (1 = '{}') (0 = '{}'): '{}'",
              one, zero, bstr[idx]));
    }
  }
}

// Get the index as a reference
BitVector::reference BitVector::operator[](size_t idx) {
  dbg_assert(m_num_bits > idx,
             std::format("Invalid index into BitVector: idx - {}, max - {}",
                         idx, m_num_bits));
  return reference(this, &m_underlying[idx / BITS_PER_EL],
                   (uint8_t)(idx % BITS_PER_EL));
}

// Get the index as a const bool
bool BitVector::operator[](size_t idx) const {
  dbg_assert(m_num_bits > idx,
             std::format("Invalid index into BitVector: idx - {}, max - {}",
                         idx, m_num_bits));
  const std::byte b =
      (ONE_ONE << (idx % BITS_PER_EL)) & m_underlying[idx / BITS_PER_EL];
  return b != ALL_ZERO;
}

// Update a single byte with pattern set
BitVector& BitVector::pattern_set_one(size_t start, size_t count,
                                      std::byte pattern) {
  std::byte mask = ALL_ONE;
  if (count % BITS_PER_EL != 0) mask >>= (BITS_PER_EL - (count) % BITS_PER_EL);
  mask <<= (start % BITS_PER_EL);

  pattern = (pattern << (start % BITS_PER_EL)) |
            (pattern >> (BITS_PER_EL - (start % BITS_PER_EL)));

  size_t idx = start / BITS_PER_EL;

  m_num_set -= BIT_LOOKUP(m_underlying[idx] & mask);
  m_num_set += BIT_LOOKUP(pattern & mask);

  m_underlying[idx] = (m_underlying[idx] & ~mask) | (pattern & mask);

  return (*this);
}

// Set bits in a repeating pattern
// start - the index in the BitVector to start filling with the sequence
// count - the number of bits to fill with the sequence
// pattern - the pattern of bits to fill with
BitVector& BitVector::pattern_set(size_t start, size_t count,
                                  std::byte pattern) {
  if (count == 0) return *this;

  cse_assert(
      (start + count) <= m_num_bits,
      std::format("Invalid range to pattern_set BitVector: start: {}, count: "
                  "{}, number of bits is: {}",
                  start, count, m_num_bits));

  // Case where we only need to change one byte
  if (start % BITS_PER_EL + count <= BITS_PER_EL)
    return pattern_set_one(start, count, pattern);

  // Masks for end bytes in the seq
  std::byte bot_mask = ALL_ONE << (start % BITS_PER_EL);
  std::byte top_mask = ALL_ONE;
  if ((start + count) % BITS_PER_EL)
    top_mask >>= (BITS_PER_EL - (start + count) % BITS_PER_EL);

  // Total bits set in the new sequence
  size_t ps_total = (size_t)BIT_LOOKUP(pattern) * (count / BITS_PER_EL);
  ps_total += (size_t)BIT_LOOKUP(
      pattern & (ALL_ONE >> (BITS_PER_EL - count % BITS_PER_EL)));
  // Counter for the number of bytes in the old sequence
  size_t ps_before = 0;

  // Offset the pattern due to where the start bit is
  pattern = (pattern << (start % BITS_PER_EL)) |
            (pattern >> (BITS_PER_EL - (start % BITS_PER_EL)));

  // Index of the byte we are changing
  size_t idx = start / BITS_PER_EL;

  // First byte
  ps_before += BIT_LOOKUP(m_underlying[idx] & bot_mask);
  m_underlying[idx] = (m_underlying[idx] & ~bot_mask) | (pattern & bot_mask);

  // Loop set
  for (++idx; (idx + 1) * BITS_PER_EL < start + count; ++idx) {
    ps_before += BIT_LOOKUP(m_underlying[idx]);
    m_underlying[idx] = pattern;
  }

  // Last byte
  ps_before += BIT_LOOKUP(m_underlying[idx] & top_mask);
  m_underlying[idx] = (m_underlying[idx] & ~top_mask) | (pattern & top_mask);

  m_num_set += ps_total;
  m_num_set -= ps_before;

  return *this;
}

// Set all bits in the vector
BitVector& BitVector::set() { return pattern_set(0, m_num_bits, ALL_ONE); }

// Set a bit in the vector
BitVector& BitVector::set(size_t idx) {
  cse_assert(
      idx < m_num_bits,
      std::format("Attempt to set BitVector at index {}, number of bits is {}",
                  idx, m_num_bits));
  (*this)[idx] = true;
  return *this;
}

// Set bits in the vector within a certain range, starting from
// start and ending at (start + count - 1)
BitVector& BitVector::set(size_t start, size_t count) {
  cse_assert(
      (start + count) <= m_num_bits,
      std::format("Invalid range to set BitVector: start: {}, count: {}, "
                  "number of bits is: {}",
                  start, count, m_num_bits));
  return pattern_set(start, count, ALL_ONE);
}

// Reset all bits in the vector
BitVector& BitVector::reset() { return pattern_set(0, m_num_bits, ALL_ZERO); }

// Reset a bit in the vector
BitVector& BitVector::reset(size_t idx) {
  cse_assert(idx < m_num_bits,
             std::format(
                 "Attempt to reset BitVector at index {}, number of bits is {}",
                 idx, m_num_bits));
  (*this)[idx] = false;
  return *this;
}

// Reset bits in the vector within a certain range, starting from
// start and ending at (start + count - 1)
BitVector& BitVector::reset(size_t start, size_t count) {
  cse_assert(
      (start + count) <= m_num_bits,
      std::format("Invalid range to reset BitVector: start: {}, count: {}, "
                  "number of bits is: {}",
                  start, count, m_num_bits));
  return pattern_set(start, count, ALL_ZERO);
}

// Test to see if a bit is set
bool BitVector::test(size_t idx) const {
  cse_assert(
      idx < m_num_bits,
      std::format("Attempt to test BitVector at index {}, number of bits is {}",
                  idx, m_num_bits));
  return (*this)[idx];
}

// Flip all bits in the BitVector
BitVector& BitVector::flip() {
  m_num_set = 0;

  for (size_t i = 0; i < m_underlying.size(); i++) {
    m_underlying[i] = m_underlying[i] ^ ALL_ONE;
    m_num_set += BIT_LOOKUP(m_underlying[i]);
  }
  truncate_byte(m_underlying.size() - 1, m_num_bits);

  return *this;
}

// Flip a specific bit in the BitVector
BitVector& BitVector::flip(size_t idx) {
  cse_assert(
      idx < m_num_bits,
      std::format("Attempt to flip BitVector at index {}, number of bits is {}",
                  idx, m_num_bits));

  (*this)[idx].flip();

  return *this;
}

// Flip all bits in the BitVector
BitVector& BitVector::flip(size_t start, size_t count) {
  if (count == 0) return *this;

  cse_assert((start + count) <= m_num_bits,
             std::format("Invalid range to flip BitVector: start: {}, count: "
                         "{}, number of bits is: {}",
                         start, count, m_num_bits));

  std::byte flipper = ALL_ONE;
  // Index of the byte we are changing
  size_t idx = start / BITS_PER_EL;

  // We only need to change one byte in this case
  if (start % BITS_PER_EL + count <= BITS_PER_EL) {
    // Constrict the flipped bits to only the ones we want
    if (count % BITS_PER_EL) flipper >>= (BITS_PER_EL - (count % BITS_PER_EL));

    m_num_set -= BIT_LOOKUP(m_underlying[idx]);
    m_underlying[idx] ^= (flipper << (start % BITS_PER_EL));
    m_num_set += BIT_LOOKUP(m_underlying[idx]);

    return (*this);
  }

  // First byte
  m_num_set -= BIT_LOOKUP(m_underlying[idx]);
  m_underlying[idx] ^= flipper << (start % BITS_PER_EL);
  m_num_set += BIT_LOOKUP(m_underlying[idx]);

  // Loop flip
  for (++idx; (idx + 1) * BITS_PER_EL < start + count; ++idx) {
    m_num_set -= BIT_LOOKUP(m_underlying[idx]);
    m_underlying[idx] ^= flipper;
    m_num_set += BIT_LOOKUP(m_underlying[idx]);
  }

  // Last byte
  m_num_set -= BIT_LOOKUP(m_underlying[idx]);
  if ((start + count) % BITS_PER_EL)
    flipper >>= (BITS_PER_EL - (start + count) % BITS_PER_EL);
  m_underlying[idx] ^= flipper;
  m_num_set += BIT_LOOKUP(m_underlying[idx]);

  return *this;
}

// Fix the given byte by mapping bits to zero after keep bits
// e.g. 0b10101010 with keep 3 -> 0b00000010 (top 5 bits are cut off)
// note: keep is modded, so don't worry about putting in too high a number
void BitVector::truncate_byte(size_t byte, uint8_t keep) {
  // No need to cut off if keep is a multiple of 8
  if (keep > 0 && keep % BITS_PER_EL == 0) return;
  // Generate cutoff mask
  std::byte mask = ALL_ONE >> (BITS_PER_EL - (keep % BITS_PER_EL));

  // Get set bit diff as well as apply mask
  m_num_set -= BIT_LOOKUP(m_underlying[byte]);
  m_underlying[byte] &= mask;
  m_num_set += BIT_LOOKUP(m_underlying[byte]);
}

// AND the BitVector with another, setting the m_underlying to
// the product
BitVector& BitVector::operator&=(const BitVector& rhs) {
  size_t i = 0;

  // Main loop doing the anding
  for (; i < m_underlying.size() && i < rhs.m_underlying.size(); i++) {
    m_num_set -= BIT_LOOKUP(m_underlying[i]);
    m_underlying[i] &= rhs.m_underlying[i];
    m_num_set += BIT_LOOKUP(m_underlying[i]);
  }

  // Fixup the last byte
  if (rhs.m_num_bits < m_num_bits)
    truncate_byte(rhs.m_underlying.size() - 1, rhs.m_num_bits);
  else
    truncate_byte(i - 1, m_num_bits);

  // If we stopped before the last byte, all the rest should be assumed zero
  for (; i < m_underlying.size(); i++) {
    m_num_set -= BIT_LOOKUP(m_underlying[i]);
    m_underlying[i] = ALL_ZERO;
  }

  return *this;
}

// OR the BitVector with another, setting the m_underlying to
// the product
BitVector& BitVector::operator|=(const BitVector& rhs) {
  size_t i = 0;

  // Main loop doing the or
  for (; i < m_underlying.size() && i < rhs.m_underlying.size(); i++) {
    m_num_set -= BIT_LOOKUP(m_underlying[i]);
    m_underlying[i] |= rhs.m_underlying[i];
    m_num_set += BIT_LOOKUP(m_underlying[i]);
  }

  // Fixup last byte just in case extra bits from rhs
  // were put at end of byte
  if (i == m_underlying.size())
    truncate_byte(m_underlying.size() - 1, m_num_bits);

  return *this;
}

// XOR the BitVector with another, setting the m_underlying to
// the product
BitVector& BitVector::operator^=(const BitVector& rhs) {
  size_t i = 0;

  // Main loop doing the xor
  for (; i < m_underlying.size() && i < rhs.m_underlying.size(); i++) {
    m_num_set -= BIT_LOOKUP(m_underlying[i]);
    m_underlying[i] ^= rhs.m_underlying[i];
    m_num_set += BIT_LOOKUP(m_underlying[i]);
  }

  // Fixup last byte just in case extra bits from rhs
  // were put at end of byte
  if (i == m_underlying.size())
    truncate_byte(m_underlying.size() - 1, m_num_bits);

  return *this;
}

// Produce a BitVector with all bits flipped
BitVector BitVector::operator~() const {
  BitVector out(m_num_bits);

  for (size_t i = 0; i < m_underlying.size(); i++) {
    out.m_underlying[i] = m_underlying[i] ^ ALL_ONE;
    out.m_num_set += BIT_LOOKUP(out.m_underlying[i]);
  }
  out.truncate_byte(out.m_underlying.size() - 1, out.m_num_bits);

  return out;
}

// equals operator
bool BitVector::operator==(const BitVector& rhs) const {
  if (rhs.m_num_bits != m_num_bits || rhs.m_num_set != m_num_set) return false;

  for (size_t i = 0; i < m_underlying.size(); ++i) {
    if (m_underlying[i] != rhs.m_underlying[i]) return false;
  }

  return true;
}

// Copy assign
BitVector& BitVector::operator=(const BitVector& bv) {
  m_underlying = bv.m_underlying;
  m_num_bits = bv.m_num_bits;
  m_num_set = bv.m_num_set;
  return *this;
}

// AND operator with another BitVector
BitVector BitVector::operator&(const BitVector& rhs) const {
  if (m_num_bits < rhs.m_num_bits) {
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
  if (m_num_bits < rhs.m_num_bits) {
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
  if (m_num_bits < rhs.m_num_bits) {
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
  else if (pos >= m_num_bits) {
    reset();
    return *this;
  }

  m_num_set = 0;
  // The first byte that has information we will keep
  size_t skip = pos / BITS_PER_EL;
  // The number of bits to interpolate between shift and shift+1 bytes
  uint8_t slide = pos % BITS_PER_EL;
  // The index of the byte we are modifying
  size_t idx = m_underlying.size() - 1;

  // Loop for combining neighboring bytes
  for (; skip < idx; --idx) {
    m_underlying[idx] = m_underlying[idx - skip] << slide;
    m_underlying[idx] |=
        m_underlying[idx - (skip + 1)] >> (BITS_PER_EL - slide);
    m_num_set += BIT_LOOKUP(m_underlying[idx]);
  }

  // Last byte
  m_underlying[idx] = m_underlying[0] << slide;
  m_num_set += BIT_LOOKUP(m_underlying[idx]);
  truncate_byte(m_underlying.size() - 1, m_num_bits);

  // Clear the rest of the bytes (<< fills with 0s from the right)
  while (idx) {
    --idx;
    m_underlying[idx] = ALL_ZERO;
  }

  return *this;
}

// Right-shift and set operator
BitVector& BitVector::operator>>=(size_t pos) {
  if (pos == 0)
    return *this;
  else if (pos >= m_num_bits) {
    reset();
    return *this;
  }

  m_num_set = 0;
  // The first byte that has information we will keep
  size_t skip = pos / BITS_PER_EL;
  // The number of bits to interpolate between shift and shift+1 bytes
  uint8_t slide = pos % BITS_PER_EL;
  // The index of the byte we are modifying
  size_t idx = 0;

  // Combine neighbor bytes
  for (; idx + skip < m_underlying.size() - 1; ++idx) {
    m_underlying[idx] = m_underlying[idx + skip] >> slide;
    m_underlying[idx] |= m_underlying[idx + skip + 1] << (BITS_PER_EL - slide);
    m_num_set += BIT_LOOKUP(m_underlying[idx]);
  }

  // Last byte
  m_underlying[idx] = m_underlying[idx + skip] >> slide;
  m_num_set += BIT_LOOKUP(m_underlying[idx]);

  // Clear the rest of the bytes (>> fills with 0s from the left)
  for (++idx; idx < m_underlying.size(); ++idx) {
    m_underlying[idx] = ALL_ZERO;
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
  for (auto b = bv.m_underlying.rbegin(); b != bv.m_underlying.rend(); ++b) {
    if (byte % 4 == 3)
      os << std::format("{:0>8b}\n", std::to_integer<uint8_t>(*b));
    else {
      os << std::format("{:0>8b}", std::to_integer<uint8_t>(*b));
      if (b != (bv.m_underlying.rend() - 1)) os << " ";
    }
    byte++;
  }

  return os;
}

// Resize this BitVector
void BitVector::resize(size_t size, std::byte fill) {
  size_t bytes = (size / BITS_PER_EL);
  if (size % BITS_PER_EL) bytes++;

  if (size > m_num_bits) {
    if (m_num_bits % BITS_PER_EL) {
      // Add bits from the pattern to the end of the last byte
      int8_t diff = BIT_LOOKUP(m_underlying.back());
      m_underlying.back() |= fill << (m_num_bits % BITS_PER_EL);
      diff -= BIT_LOOKUP(m_underlying.back());

      // Update m_num_set
      m_num_set += diff;
      fill = (fill >> (BITS_PER_EL - (m_num_bits % BITS_PER_EL))) |
             (fill << (m_num_bits % BITS_PER_EL));
    }

    // Add to num set based on the number of bytes we will be appending on to
    // m_underlying
    m_num_set += BIT_LOOKUP(fill) * (bytes - m_underlying.size());
  }

  m_underlying.resize(bytes, fill);
  m_num_bits = size;
  truncate_byte(m_underlying.size() - 1, m_num_bits);
}

// Resize this bitvector, optionally filling with bits
void BitVector::resize(size_t size, bool fill) {
  std::byte b = fill ? ALL_ONE : ALL_ZERO;
  resize(size, b);
}

// Append a bit to this BitVector
void BitVector::append(bool value) {
  if (m_num_bits % BITS_PER_EL == 0) m_underlying.push_back(ALL_ZERO);
  m_num_bits++;
  (*this)[m_num_bits - 1] = value;
}

// Append a BitVector to this BitVector
void BitVector::append(const BitVector& bv) {
  if (bv.m_num_bits == 0) return;

  // Pack bits into the last byte if there is room
  uint8_t over = m_num_bits % BITS_PER_EL;
  if (over > 0) m_underlying.back() |= bv.m_underlying[0] << over;

  // Loop to push new bytes on to the back
  for (size_t i = 0; i < bv.m_underlying.size() - 1; ++i) {
    std::byte add = bv.m_underlying[i];
    // Merge with next byte if offset
    if (over > 0) {
      add = add >> (BITS_PER_EL - over);
      add |= bv.m_underlying[i + 1] << over;
    }
    m_underlying.push_back(add);
  }

  // The number of bits we had in our upper byte to begin with
  uint8_t open_slots = (BITS_PER_EL - (m_num_bits % BITS_PER_EL)) % BITS_PER_EL;
  // The number of bits taken up in the upper byte of bv
  uint8_t req_slots = BITS_PER_EL - (bv.m_num_bits % BITS_PER_EL);
  // Add the remaining bits if required
  if (req_slots < open_slots) {
    std::byte add = bv.m_underlying.back() >> (BITS_PER_EL - over);
    m_underlying.push_back(add);
  }

  m_num_bits += bv.m_num_bits;
  m_num_set += bv.m_num_set;
}

// Prepend a single bit to the BitVector
void BitVector::prepend(bool value) {
  if (m_num_bits % BITS_PER_EL == 0) m_underlying.push_back(ALL_ZERO);
  m_num_bits++;
  *this <<= 1;
  (*this)[0] = value;
}

// Prepend another BitVector to the BitVector
void BitVector::prepend(const BitVector& bv) {
  BitVector tmp = *this;
  *this = bv;
  append(tmp);
}

// Append a bit vector to the end of this one
BitVector& BitVector::operator+=(const BitVector& bv) {
  this->append(bv);
  return *this;
}

// Append two bit vectors (NOT ASSOCIATIVE, right gets added to left)
BitVector BitVector::operator+(const BitVector& bv) const {
  BitVector out = *this;
  out.append(bv);
  return out;
}

#endif  // CSE4_IMPL

};  // namespace cse
