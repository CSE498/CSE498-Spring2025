/**
 * @file StaticString.hpp
 * @author Mehmet Efe Caylan
 * @brief StaticString Class implementation file.
 * @version 0.1
 * @date 2025-02-06
 *
 */

#ifndef CSE_STATIC_STRING_HPP_
#define CSE_STATIC_STRING_HPP_

#include <cassert>
#include <cstring>
#include <stdexcept>

namespace cse {

/**
* @brief StaticString Class that provides faster string operations by limiting
* the static size.
*
* StaticString class offers a compatible version of std::string class; a fixed
* sized array provides string operations.
*
* @tparam MaxSize Static size_t value to limit our string's size excluding the
* null terminator at the end.
*/
template <std::size_t MaxSize>
class StaticString {
public:
  /// @brief Constant value for StaticString npos, not found value.
  static constexpr std::size_t npos = static_cast<std::size_t>(-1);

  /*----------------------CONSTRUCTORS--------------------------------------*/

  /**
  * @brief Construct a new Static String object
  *
  * If the given string is empty then initialize it as empty.
  */
  constexpr StaticString() noexcept : mCurrentSize(0) {
    mString[0] = null_terminator;
  }

  /**
  * @brief Construct a new Static String object with a non-empty string
  *
  * Copies characters from the provided c style string to StaticString object.
  * @attention Make sure to check string provided is shorter than maximum size
  * defined.
  *
  * @param cstr Pointer to an array of characters that corresponds
  * to our string value.
  */
  constexpr StaticString(const char* cstr) : mCurrentSize(0) {
    // Loop over given array of characters until find null terminator
    // or the size exceeds static size initialized
    while (cstr[mCurrentSize] != null_terminator && mCurrentSize < MaxSize) {
      mString[mCurrentSize] = cstr[mCurrentSize];
      ++mCurrentSize;
    }

    // The provided string is longer than MaxSize defined.
    assert(mCurrentSize <= MaxSize &&
          "Error: Input string exceeds StaticString defined maximum size.");

    // Initialize the last location of the string to null terminator
    mString[mCurrentSize] = null_terminator;
    mString[MaxSize] = null_terminator;
  }

  /**
  * @brief Construct a new StaticString object from another StaticString object
  *
  * @param staticString Static String object to be copied.
  */
  constexpr StaticString(const StaticString& staticString) noexcept
      : mCurrentSize(staticString.mCurrentSize) {
    std::copy(staticString.mString, staticString.mString + MaxSize + 1,
              mString);
  }

  /**
  * @brief Construct a new templated Static String object copying from another
  * StaticString.
  *
  * To be able to copy form another object, new templated StaticString object
  *  must be equal or greater sized in terms of static limit defined.
  *
  * @tparam newMaxSize New allocated objects maximum size value
  * @param staticString Source staticString object
  */
  template <std::size_t newMaxSize>
  StaticString(const StaticString<newMaxSize>& staticString) {
    // Check if the string that we will copy is larger than MaxSize defined
    assert(staticString.length() <= MaxSize &&
          "Error: The length of copied string exceeds static limit defined.");

    std::copy(staticString.get_str(),
              staticString.get_str() + staticString.length(), mString);

    mCurrentSize = staticString.length();
    mString[mCurrentSize] = null_terminator;
  }

  /*----------------------------OPERATORS-----------------------------------*/

  /**
  * @brief Assignment operator.
  *
  * Copies the content from another StaticString.
  *
  * @param staticString staticString to be assigned.
  * @return StaticString& Reference to this StaticString object.
  */
  StaticString& operator=(const StaticString& staticString) {
    // Avoid assigning to itself
    assert(this != &staticString && "Assigning object itself is not allowed.");
    if (this == &staticString) {
      return *this;
    }

    if (this != &staticString) {
      // Check if the string that we will copy is larger than MaxSize defined
      assert(
          staticString.length() <= MaxSize &&
          "Error: The length of copied string exceeds static limit defined.");
      std::copy(staticString.mString,
                staticString.mString + staticString.length(), mString);

      mCurrentSize = staticString.mCurrentSize;
      mString[mCurrentSize] = null_terminator;
    }
    return *this;
  }

  /**
  * @brief Assignment operator from a C-string.
  *
  * New string to be assigned must be shorter than size limit or exact length
  * with maximum size limit. When a StaticString assigned to a nullptr,
  * it will automatically clear itself and will be empty
  * as well as empty string initialization.
  *
  * @param cstr C-string to be assigned.
  * @return StaticString& Reference to this StaticString object.
  */
  StaticString& operator=(const char* cstr) {
    // Empty string or nullptr assign handle
    if (!cstr) {
      // Set all indexes to null terminator
      for (std::size_t i = 0; i <= MaxSize; ++i) {
        mString[i] = null_terminator;
      }
      mCurrentSize = 0;
      return *this;
    }

    size_t newLength = 0;
    // Copy the new string
    while (cstr[newLength] != null_terminator && newLength < MaxSize) {
      mString[newLength] = cstr[newLength];
      ++newLength;
    }

    // Check new copied string is under static limits
    assert((newLength < MaxSize || cstr[newLength] == null_terminator) &&
          "Invalid size for assign input, input string is too long.");

    // Replace remaining part of the string with null terminator
    for (size_t i = newLength; i <= MaxSize; ++i) {
      mString[i] = null_terminator;
    }

    mCurrentSize = newLength;
    return *this;
  }

  /**
  * @brief Index operator to get value in the specific index of string.
  *
  * Index operator only used to get a copy of character on the given index.
  *
  * @see set() to change a character on a given index.
  *
  * @param index size_t The index of character.
  * @return Indexed char value.
  */
  char operator[](std::size_t index) const {
    // Indexed value is out of range or
    // trying to index to the null terminator at the end
    assert(index < mCurrentSize && "Index value is out of range.");
    return mString[index];
  }

  /**
  * @brief Equality comparison with another StaticString.
  *
  * @param rhs The StaticString to compare with.
  * @return true if both strings are equal.
  * @return false if both strings are not equal.
  */
  bool operator==(const StaticString& rhs) const noexcept {
    return mCurrentSize == rhs.mCurrentSize &&
          std::strcmp(mString, rhs.mString) == 0;
  }

  /**
  * @brief Equality comparison with a C-string.
  *
  * @param rhs The C-string to compare with.
  * @return true if both strings are equal.
  * @return false if both strings are not equal.
  */
  bool operator==(const char* rhs) const {
    assert(rhs != nullptr && "Nullptr comparisons not a legal comparison");
    if (!rhs) return false;
    return std::strcmp(mString, rhs) == 0;
  }

  /**
  * @brief Inequality comparison with another StaticString.
  *
  * @param rhs The StaticString to compare with.
  * @return true if both strings are not equal.
  * @return false if both strings are equal.
  */
  bool operator!=(const StaticString& rhs) const noexcept {
    return !(*this == rhs);
  }

  /**
  * @brief Inequality comparison with a C-string.
  *
  * @param rhs The StaticString to compare with.
  * @return true if both strings are not equal.
  * @return false if both strings are equal.
  */
  bool operator!=(const char* rhs) const noexcept {
    return std::strcmp(mString, rhs) != 0;
  }

  /**
  * @brief Less-than comparison with another StaticString.
  *
  * @param rhs The StaticString to compare with.
  * @return true if this string is lexicographically less than.
  * @return false if this string is lexicographically greater than.
  */
  bool operator<(const StaticString& rhs) const noexcept {
    return std::strcmp(mString, rhs.mString) < 0;
  }

  /**
  * @brief Less-than comparison with a C-string.
  *
  * @param rhs The StaticString to compare with.
  * @return true if this string is lexicographically less than.
  * @return false if this string is lexicographically greater than.
  */
  bool operator<(const char* rhs) const {
    if (!rhs) return false;
    assert(rhs != nullptr && "Nullptr comparisons not a legal comparison");
    return std::strcmp(mString, rhs) < 0;
  }

  /**
  * @brief Greater-than comparison with another StaticString.
  *
  * @param rhs The StaticString to compare with.
  * @return true if this string is lexicographically greater than.
  * @return false if this string is lexicographically less than.
  */
  bool operator>(const StaticString& rhs) const noexcept {
    return std::strcmp(mString, rhs.mString) > 0;
  }

  /**
  * @brief Greater-than comparison with a C-string.
  *
  * @param rhs The StaticString to compare with.
  * @return true if this string is lexicographically greater than.
  * @return false if this string is lexicographically less than.
  */
  bool operator>(const char* rhs) const {
    if (!rhs) return true;
    assert(rhs != nullptr && "Nullptr comparisons not a legal comparison");
    return std::strcmp(mString, rhs) > 0;
  }

  /**
  * @brief Less-than-or-equal-to comparison with another StaticString.
  *
  * @param rhs The StaticString to compare with.
  * @return true if this string is lexicographically less than or equal to rhs.
  * @return false if this string is lexicographically greater than rhs.
  */
  bool operator<=(const StaticString& rhs) const noexcept {
    return std::strcmp(mString, rhs.mString) <= 0;
  }

  /**
  * @brief Less-than-or-equal-to comparison with a C-string.
  *
  * @param rhs The StaticString to compare with.
  * @return true if this string is lexicographically less than or equal to rhs.
  * @return false if this string is lexicographically greater than rhs.
  */
  bool operator<=(const char* rhs) const {
    if (!rhs) return false;
    assert(rhs != nullptr && "Nullptr comparisons not a legal comparison");
    return std::strcmp(mString, rhs) <= 0;
  }

  /**
  * @brief Greater-than-or-equal-to comparison with another StaticString.
  *
  * @param rhs The StaticString to compare with.
  * @return true if this string is lexicographically greater than or equal rhs.
  * @return false if this string is lexicographically less than rhs.
  */
  bool operator>=(const StaticString& rhs) const noexcept {
    return std::strcmp(mString, rhs.mString) >= 0;
  }

  /**
  * @brief Greater-than-or-equal-to comparison with a C-string.
  *
  * @param rhs The StaticString to compare with.
  * @return true if this string is lexicographically greater than or equal rhs.
  * @return false if this string is lexicographically less than rhs.
  */
  bool operator>=(const char* rhs) const {
    if (!rhs) return true;
    assert(rhs != nullptr && "Nullptr comparisons not a legal comparison");
    return std::strcmp(mString, rhs) >= 0;
  }

  /*--------------------------FUNCTIONS-------------------------------------*/

  /**
  * @brief Return the maximum size of the string.
  *
  * @return std::size_t static size of the string.
  */
  constexpr std::size_t size() const noexcept { return MaxSize; }

  /**
  * @brief Return the current length of the string.
  *
  * @return std::size_t Length of the string.
  */
  constexpr std::size_t length() const noexcept { return mCurrentSize; }

  /**
  * @brief Get the stored string in StaticString.
  *
  * @return const char* A pointer to the character array.
  */
  constexpr const char* get_str() const noexcept { return mString; }

  /**
  * @brief Get the stored string in StaticString.
  *
  * @return char* A pointer to the character array.
  */
  constexpr char* get_str() noexcept { return mString; }

  /**
  * @brief Finds the first occurrence of a character in the string.
  *
  * @param character Character to be searched.
  * @return std::size_t The index of the character if found;
  * if not found StaticString::npos.
  */
  constexpr std::size_t find(const char& character) const noexcept {
    for (std::size_t i = 0; i < mCurrentSize; ++i) {
      if (mString[i] == character) return i;
    }
    return npos;
  }

  /**
  * @brief Sets the given character at given index.
  *
  * Indexing starts from 0; if the MaxSize is 10 then last possible index is 9.
  * If inserted character is a null terminator, StaticString will behave as
  * a new string creation and the rest of the string after the null terminated
  * part will be assigned to '\0' again.
  *
  * @attention If '\0' is explicitly set as a character,
  * rest of the string will be terminated.
  *
  * @param index Index to be changed.
  * @param character Char value to be assigned.
  * @throws std::out_of_range if the index is invalid.
  */
  void set(const size_t& index, const char& character) {
    assert(index < mCurrentSize && "Index value is out of range");
    if (index >= mCurrentSize || index >= MaxSize) {
      throw std::out_of_range("Index value is out of range");
    }

    // If user explicitly tries to cut their strings with null terminator
    // Handle the size appropriately
    if (character == '\0') {
      mCurrentSize = index;
    }
    mString[index] = character;
  }

  /**
  * @brief Converts the StaticString to an std::string.
  *
  * @return std::string The equivalent std::string.
  */
  std::string to_string() const { return std::string(mString, mCurrentSize); }

  /*--------------------- STRING OPERATIONS ----------------------*/

  /**
  * @brief Appends a C-string to the end of the current string.
  *
  * @param cstr The C-string to append.
  * @throws std::out_of_range if the resulting string would exceed the MaxSize.
  */
  void append(const char* cstr) {
    // Calculate the length of the given string.
    const std::size_t cstr_length = std::strlen(cstr);

    // Validate that given string fits into our string within static limit.
    assert((mCurrentSize + cstr_length <= MaxSize) &&
          "Appending string exceeds maximum size");
    if (mCurrentSize + cstr_length > MaxSize) {
      throw std::out_of_range(
          "Static limit exceeded, appended string must be within limits "
          "defined");
    }

    std::copy(cstr, cstr + cstr_length, mString + mCurrentSize);

    // Update the length.
    mCurrentSize += cstr_length;
    mString[mCurrentSize] = null_terminator;
  }

  /**
  * @brief Appends a character to the end of the current string.
  *
  * @param character The character to append.
  * @throws std::out_of_range if the resulting string would exceed
  * the maximum size.
  */
  void append(const char& character) {
    // Validate that given string fits into our string within static limit.
    assert((mCurrentSize + 1 <= MaxSize) &&
          "Appending string exceeds maximum size");
    if (mCurrentSize + 1 > MaxSize) {
      throw std::out_of_range(
          "Static limit exceeded, appended string must be within limits "
          "defined");
    }

    // Update the length and set the character.
    mString[mCurrentSize] = character;
    mCurrentSize++;
    mString[mCurrentSize] = null_terminator;
  }

  /**
  * @brief Appends an std::string to the end of the current string.
  *
  * @param str The std::string to append.
  * @throws std::out_of_range if the resulting string would exceed
  * the maximum size.
  */
  void append(const std::string& str) {
    // Calculate the length of the given string.
    const std::size_t str_length = str.length();

    // Validate that given string fits into our string within static limit.
    assert((mCurrentSize + str_length < MaxSize) &&
          "Appending string exceeds maximum size");
    if (mCurrentSize + str_length >= MaxSize) {
      throw std::out_of_range(
          "Static limit exceeded, appended string must be within limits "
          "defined");
    }

    std::copy(str.begin(), str.end(), mString + mCurrentSize);

    // Update the length.
    mCurrentSize += str_length;
    mString[mCurrentSize] = null_terminator;
  }

  /**
  * @brief Appends an std::string_view to the end of the current string.
  *
  * @param str The std::string_view to append.
  * @throws std::out_of_range if the resulting string would exceed
  * the maximum size.
  */
  void append(const std::string_view& str) {
    // Calculate the length of the given string.
    const std::size_t str_length = str.length();

    // Validate that given string fits into our string within static limit.
    assert((mCurrentSize + str_length < MaxSize) &&
          "Appending string exceeds maximum size");
    if (mCurrentSize + str_length >= MaxSize) {
      throw std::out_of_range(
          "Static limit exceeded, appended string must be within limits "
          "defined");
    }

    std::copy(str.begin(), str.end(), mString + mCurrentSize);

    // Update the length.
    mCurrentSize += str_length;
    mString[mCurrentSize] = null_terminator;
  }

  /**
  * @brief Concatenates another StaticString onto this StaticString object.
  *
  * @param rhs The StaticString to concatenate.
  * @return StaticString& Reference to this StaticString.
  * @throws std::out_of_range if the resulting string would exceed
  * the maximum size.
  */
  StaticString& concat(const StaticString& rhs) {
    // Validate that given string fits into our string within static limit.
    assert((mCurrentSize + rhs.mCurrentSize <= MaxSize) &&
          "Concatenated string exceeds maximum size");

    if (mCurrentSize + rhs.mCurrentSize > MaxSize) {
      throw std::out_of_range(
          "Static limit exceeded, concatenated string must be within MaxSize");
    }

    std::copy(rhs.mString, rhs.mString + rhs.mCurrentSize + 1,
              mString + mCurrentSize);

    // Update the length.
    mCurrentSize += rhs.mCurrentSize;
    mString[mCurrentSize] = null_terminator;
    return *this;
  }

  /**
  * @brief Extracts a substring as a std::string_view.
  *
  * Substring function returns std::string_view,
  * read only access to given range of substring.
  *
  * @attention Minus indexing is not allowed.
  *
  * @param start The starting index (inclusive).
  * @param end The ending index (exclusive).
  * @return std::string_view representing the substring.
  * @throws std::out_of_range if the resulting string would exceed
  * the maximum size.
  */
  std::string_view substr(const std::size_t& start,
                          const std::size_t& end) const {
    // Validate that given string fits into our string within static limit.
    assert((start < end || end <= mCurrentSize) &&
          "Index provided for substring are invalid");

    if (start > end || end > mCurrentSize) {
      throw std::out_of_range("Invalid substring request");
    }
    return std::string_view(mString + start, end - start);
  }

private:
  /// @brief Constant value for StaticString null terminator used.
  static constexpr char null_terminator = '\0';

  /// @brief Array of characters stores the string with a predefined size.
  char mString[MaxSize + 1] = {null_terminator};  // Array of characters '\0'

  /// @brief size_t The current length of the string.
  std::size_t mCurrentSize = 0;  // Tracks the current length of the string.
};

}  // namespace cse

#endif  // CSE_STATIC_STRING_HPP_