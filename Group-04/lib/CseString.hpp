/**
 * @file CseString.hpp
 * @author ...
 *
 */

#pragma once

#include <sstream>  // for std::ostringstream
#include <string>

#include "CseAssert.hpp"

namespace cse {

#ifndef NDEBUG

/**
 * @class String
 * @brief A debug-audited string class derived from std::string.
 *
 * Provides additional index-range checks and other safety mechanisms in Debug
 * builds.
 */
class String : public std::string {
 public:
  // --------------------------------------------------------------------------
  // Bring in all constructors from std::string, including ones that accept
  // const char*, size_t, etc.
  using std::string::string;

  /**
   * @brief Explicit constructor from an existing std::string.
   *
   * This may help compilers that see std::__1::string as distinct
   * from std::string in certain environments (e.g., macOS clang).
   */
  String(const std::string &other) : std::string(other) {}

  /**
   * @brief Assignment operator from std::string.
   */
  String &operator=(const std::string &other) {
    std::string::operator=(other);
    return *this;
  }

  /**
   * @brief Overloaded operator[] (non-const) with debug checks.
   * @param pos The index to access.
   * @return Reference to the character at the specified position.
   */
  char &operator[](std::size_t pos) {
    dbg_assert(pos < size(),
               build_error_msg("cse::String operator[] index out of range", pos,
                               size())
                   .c_str());
    return std::string::operator[](pos);
  }

  /**
   * @brief Overloaded operator[] (const) with debug checks.
   * @param pos The index to access.
   * @return Const reference to the character at the specified position.
   */
  const char &operator[](std::size_t pos) const {
    dbg_assert(pos < size(),
               build_error_msg("cse::String operator[] index out of range", pos,
                               size())
                   .c_str());
    return std::string::operator[](pos);
  }

  /**
   * @brief Provides at() with debug checks.
   * @param pos The index to access.
   * @return Reference to the character at the specified position.
   */
  char &at(std::size_t pos) {
    dbg_assert(
        pos < size(),
        build_error_msg("cse::String at() index out of range", pos, size())
            .c_str());
    return std::string::at(
        pos);  // std::string::at() also throws std::out_of_range
  }

  /**
   * @brief Provides const at() with debug checks.
   * @param pos The index to access.
   * @return Const reference to the character at the specified position.
   */
  const char &at(std::size_t pos) const {
    dbg_assert(
        pos < size(),
        build_error_msg("cse::String at() index out of range", pos, size())
            .c_str());
    return std::string::at(pos);
  }

  /**
   * @brief Extracts a substring with debug checks.
   * @param pos Starting position of the substring.
   * @param count Number of characters to include, defaults to npos.
   * @return A cse::String containing the requested substring.
   */
  cse::String substr(std::size_t pos, std::size_t count = npos) const {
    dbg_assert(
        pos <= size(),
        build_error_msg("cse::String substr() start position out of range", pos,
                        size())
            .c_str());
    return cse::String(std::string::substr(pos, count));
  }

  /**
   * @brief Insert a string into this String at the specified position, with
   * debug checks.
   *
   * @param pos The position at which the content should be inserted.
   * @param str The string to insert.
   * @return Reference to this String after insertion.
   */
  String &insert(std::size_t pos, const String &str) {
    dbg_assert(pos <= size(),
               build_error_msg("cse::String insert() position out of range",
                               pos, size())
                   .c_str());
    std::string::insert(pos, str);
    return *this;
  }

  /**
   * @brief Erase a portion of this String, with debug checks.
   *
   * @param pos The starting position of the erase operation.
   * @param count The number of characters to erase (defaults to npos).
   * @return Reference to this String after erasure.
   */
  String &erase(std::size_t pos = 0, std::size_t count = npos) {
    dbg_assert(
        pos <= size(),
        build_error_msg("cse::String erase() start position out of range", pos,
                        size())
            .c_str());
    std::string::erase(pos, count);
    return *this;
  }

  /**
   * @brief Replace a portion of this String with another string, with debug
   * checks.
   *
   * @param pos The starting position of the replace operation.
   * @param count The number of characters to replace.
   * @param str The string to replace with.
   * @return Reference to this String after replacement.
   */
  String &replace(std::size_t pos, std::size_t count, const String &str) {
    dbg_assert(
        pos <= size(),
        build_error_msg("cse::String replace() start position out of range",
                        pos, size())
            .c_str());
    std::string::replace(pos, count, str);
    return *this;
  }

 private:
  /**
   * @brief Helper function to build a detailed debug error message.
   *
   * @param context Contextual message (e.g., which function is throwing the
   * error).
   * @param index The index/position causing the error.
   * @param length The current length of the string.
   * @return A formatted error message including context, index, and length.
   */
  static std::string build_error_msg(const char *context, std::size_t index,
                                     std::size_t length) {
    std::ostringstream oss;
    oss << context << ": pos=" << index << ", size=" << length;
    return oss.str();
  }
};

#else

// In Release builds, String is just an alias to std::string
using String = std::string;

#endif  // NDEBUG

}  // namespace cse
