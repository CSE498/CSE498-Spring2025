/**
 * @file StaticString.hpp
 * @author Mehmet Efe Caylan
 * @author Will Crawford
 * @brief StaticString Class implementation file.
 * @version 0.2
 * @date 2025-02-06
 *
 */

#ifndef CSE_STATIC_STRING_HPP_
#define CSE_STATIC_STRING_HPP_

#include <unordered_map>
#include <cassert>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <array>

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

  /**
  * @brief Iterator to the beginning of static string (begin iterator)
  * @return Iterator pointing to beginning of static string
  */
  constexpr char* begin() { return mString; }

  /**
  * @brief Iterator to the end of static string (end iterator)
  * @return Iterator pointing past the end of static string
  */
  constexpr char* end() { return mString + mCurrentSize; }

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
   * This constructor initializes the StaticString object by copying characters from 
   * the provided objects `std::string`, `std::string_view`, or `const char*`
   * into the fixed size character array. It ensures that no more than MaxSize
   * characters are copied and appends a null terminator at the end.
   * 
   * @attention Make sure to check string provided is shorter than maximum size
   * defined.
   * 
   * @tparam T A type that is implicitly convertible to `std::string_view`, such as 
   * `const char*`, `std::string`, or `std::string_view`.
   * @tparam typename 
   * @tparam std::string_view>> 
   */
  template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, std::string_view>>>
  constexpr StaticString(const T& cstr) : mCurrentSize(0) {

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
    // assert(this != &staticString && "Assigning object itself is not allowed.");
    if (this == &staticString) {
      return *this;
    }

    // Check if the string that we will copy is larger than MaxSize defined
    assert(
        staticString.length() <= MaxSize &&
        "Error: The length of copied string exceeds static limit defined.");
    std::copy(staticString.mString,
              staticString.mString + staticString.length(), mString);

    mCurrentSize = staticString.mCurrentSize;
    mString[mCurrentSize] = null_terminator;
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
  char operator[](std::size_t index) const noexcept {
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
   * @brief Finds the first occurrence of a character, string, string_view,
   *  char* in the string.
   * 
   * @tparam T Templated types are string, string_view, char*
   * @param str Templated parameter to searched in the string
   * @return constexpr std::size_t The index of the character if found;
   * if not found StaticString::npos.
   */
  template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, std::string_view>>>
  constexpr std::size_t find(const T& str) const noexcept {
    // std::string, char*, char[N] are all convertible to string_view, thus
    // We convert templated input to convert into string_view to perform find
    std::string_view size(str);

    for (std::size_t i = 0; i <= mCurrentSize - size.length(); ++i) {
      std::size_t j = 0;
      for (; j < size.length(); ++j) {
        if (mString[i + j] != str[j]) break;
      }
      if (j == size.length()) return i;
    }
    return npos;
  }

  // Overloading find for char because  string_view is not convertible from char
  constexpr std::size_t find(char ch) const noexcept {
      for (std::size_t i = 0; i < mCurrentSize; ++i) {
          if (mString[i] == ch) return i;
      }
      return npos;
  }
  
  /**
  * @brief Sets the given character at given index.
  *
  * Indexing starts from 0; if the MaxSize is 10 then last possible index is 9.
  * If inserted character is a null terminator, StaticString will behave as
  * the rest of the string will be ignored and won't be able to recover it.
  *
  * @attention If '\0' is explicitly set as a character,
  * rest of the string will be terminated.
  *
  * @param index size_t Index to be changed.
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

  /**
   * @brief Insert provided string to the given index and shift the rest.
   * 
   * Insert adds given string to starting from the given index such that 
   * StaticString s("123456789");
   * s.insert("Test", 0); -> "Test123456789"
   * Allowed types for insert is char, string, char*, string_view
   * 
   * @tparam T Templated type 
   * @param str String to be inserted
   * @param index size_t index to insert string.
   */
  template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, std::string_view>>>
  void insert(const T& str, const std::size_t& index) {
    std::string_view temp_view = str;

    if(index > mCurrentSize || mCurrentSize + temp_view.size() > MaxSize) {
      throw std::out_of_range("Static limit exceeded, inserted string must be within MaxSize with current string size.");
    }

    // Move the curent characters to create space for insert
    std::memmove(mString + index + temp_view.size(), mString + index, mCurrentSize - index);

    std::memcpy(mString + index, temp_view.data(), temp_view.size());

    mCurrentSize += temp_view.size();
    mString[mCurrentSize] = null_terminator;
  }

  /**
   * @brief Insert provided string to the given index and shift the rest.
   * 
   * Overload for char as parameter.
   * Insert adds given string to starting from the given index such that 
   * StaticString s("123456789");
   * s.insert('T', 0); -> "T123456789"
   * Allowed types for insert is char, string, char*, string_view
   * 
   * @param chr charater to be inserted
   * @param index size_t index to insert character
   */
  void insert(const char& chr, const std::size_t& index) {
    if(index > mCurrentSize || mCurrentSize + 1 > MaxSize) {
      throw std::out_of_range("Static limit exceeded, inserted string must be within MaxSize with current string size.");
    }

    // Move the curent characters to create space for insert
    std::memmove(mString + index + 1, mString + index, mCurrentSize - index);

    mString[index] = chr;
    ++mCurrentSize;
    mString[mCurrentSize] = null_terminator;
  }

  /**
   * @brief Removes characters of a range from the StaticString.
   * 
   * Removes charaters within a valid range of indexes, start index is inclusive
   * while end index is exclusive. 
   * 
   * @param start size_t start index of the range (inclusive).
   * @param end size_t end index of the range (exclusive).
   */
  void remove(const size_t& start, const size_t& end) {
    if(start >= end || end > mCurrentSize) {
      throw std::out_of_range("Index is out of bound , start and end index for remove must be withing static limits.");
    }
    size_t length = end - start;

    std::memmove(mString + start, mString + end, mCurrentSize - end);

    mCurrentSize -= length;
    mString[mCurrentSize] = null_terminator;
  }

  /**
   * @brief Finds every occurrence of a character, string, string_view,
   *  char* in the string.
   * 
   * @tparam T Templated types are string, string_view, char*
   * @param str Templated parameter to be searched in the string
   * @return constexpr std::vector<std::size_t>, a vector of the indexes of the character if found;
   * if not found {}.
  */
  template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, std::string_view>>>
  constexpr  std::vector<std::size_t> findAll(const T& str) const noexcept {
    // std::string, char*, char[N] are all convertible to string_view, thus
    // We convert templated input to convert into string_view to perform findAll
    std::string_view size(str);

    // A list of all of the indexes found
    std::vector<size_t> indexesFound = std::vector<size_t>{};
    int counter = 0;
    
    for (std::size_t i = 0; i <= mCurrentSize - size.length(); ++i) {
      std::size_t j = 0;
      for (; j < size.length(); ++j) {
        if (mString[i + j] != str[j]) break;
      }
      if (j == size.length()) {
        indexesFound.push_back(i);
        counter++;
      }
    }
    return indexesFound;
  }

  // Overloading findAll for char because string_view is not convertible from char
  constexpr std::vector<std::size_t> findAll(char ch) const noexcept {
      std::vector<std::size_t> indexesFound = std::vector<size_t>{};
      int counter = 0;

      for (std::size_t i = 0; i < mCurrentSize; ++i) {
          if (mString[i] == ch) {
            indexesFound.push_back(i);
            counter++;
          };
      }
      return indexesFound;
  }
  
  /**
   * @brief Finds the first occurrence of a character, string, string_view,
   * char* in the string, in reverse search order.
   * 
   * @tparam T Templated types are string, string_view, char*
   * @param str Templated parameter to searched in the string
   * @return constexpr std::size_t The index of the character if found;
   * if not found StaticString::npos.
   */
  template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, std::string_view>>>
  constexpr std::vector<std::size_t> rFind(const T& str) const noexcept {
    // std::string, char*, char[N] are all convertible to string_view, thus
    // We convert templated input to convert into string_view to perform find
    std::string_view size(str);

    std::vector<size_t> indexesFound = std::vector<size_t>{};
    int counter = 0;
    
    for (std::size_t i = 0; i <= mCurrentSize - size.length(); ++i) {
      std::size_t j = 0;
      for (; j < size.length(); ++j) {
        if (mString[i + j] != str[j]) break;
      }
      if (j == size.length()) {
        indexesFound.insert(indexesFound.begin(), i);
        counter++;
      }
    }
    return indexesFound;
  }


  // Overloading rFind for char because  string_view is not convertible from char
  constexpr std::vector<std::size_t> rFind(char ch) const noexcept {
      std::vector<std::size_t> indexesFound = std::vector<size_t>{};
      int counter = 0;

      for (std::size_t i = 0; i < mCurrentSize; ++i) {
          if (mString[i] == ch) {
            indexesFound.insert(indexesFound.begin(), i);
            counter++;
          };
      }
      return indexesFound;
  }

  /**
  * @brief replaces all instances of the first string given with the second string 
  * 
  * @tparam T Templated types are string, string_view, char*
  * @param the string to replace
  * @param the string to replace the string
  */
  template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, std::string_view>>>
  void replace(const T& str1, const char* str2) {
    std::vector<size_t> index = findAll(str1);
    std::string_view size(str1);
    std::string_view size2(str2);
    if (index.size() * size2.length() > MaxSize)
      throw std::out_of_range("replace exceeds the size allowed");

    for (int i = 0; i < (int)index.size(); i++) {
      remove(index[i], index[i] + size.length());
      insert(str2, index[i]);
    }
  }

  // Overloading replace for char because string_view is not convertible from char
  void replace(char ch, char ch2) {
    std::vector<size_t> index = findAll(ch);
    for (int i = 0; i < (int)index.size(); i++) {
      remove(index[i], index[i] + size_t(1));
      insert(ch2, index[i]);
    }
  }

  // Overloading replace for char because string_view is not convertible from char
  template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, std::string_view>>>
  void replace(const T& str1, char ch2) {
    std::vector<size_t> index = findAll(str1);
    std::string_view size(str1);
    for (int i = 0; i < (int)index.size(); i++) {
      remove(index[i], index[i] + size.length());
      insert(ch2, index[i]);
    }
  }

  // Overloading replace for char because string_view is not convertible from char
  template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, std::string_view>>>
  void replace(char ch, const T& str2) {
    std::vector<size_t> index = findAll(ch);

    std::string_view size2(str2);
    if (index.size() * size2.length() > MaxSize)
      throw std::out_of_range("replace exceeds the size allowed");

    for (int i = 0; i < (int)index.size(); i++) {
      remove(index[i], index[i] + std::size_t(1));
      insert(str2, index[i]);
    }
  }

  /**
   * @brief Applies a given function to each character in the StaticString.
   * 
   * This is a utility function and can be used to perform operations or 
   * custom changes over the string using your own functions. 
   * Foreach iterates over each charater and applies changes to each character
   * if advised.
   * 
   * @tparam Func The function type to be applied to each character.
   * @param lambda A function or lambda that accepts a character.
   */
  template <typename Func>
  void foreach(Func lambda) {

    for (size_t i = 0; i < mCurrentSize; ++i) {
      lambda(mString[i]);
    }
  }

  /**
   * @brief Transforms the StaticString by applying a function to each character
   * 
   * This is not an in place function, changes made on StaticString by the 
   * function will be applied to a copy of the current object, and 
   * new modified object will be returned. 
   * 
   * @tparam Func The function type to be applied to each character.
   * @param lambda A function or lambda that accepts a character.
   * @return StaticString A new transformed StaticString.
   */
  template <typename Func>
  [[nodiscard]] StaticString transform(Func lambda) const {
    StaticString result(*this);

    for (std::size_t i = 0; i < result.length(); ++i) {
      result.get_str()[i] = lambda(result.get_str()[i]);
    }
    return std::move(result);
  }

  /**
   * @brief Counts the occurrences of each character in the StaticString.
   * 
   * @return constexpr std::unordered_map<char, std::size_t> A map of character to its count.
   */
  constexpr std::unordered_map<char, std::size_t> char_count() const noexcept {
    std::unordered_map<char, std::size_t> counts;

    for (std::size_t i = 0; i < mCurrentSize; ++i) {
      ++counts[mString[i]];
    }
    return counts;
  }
  
  /**
   * @brief Splits the given StaticString based on delimiter defined.
   * 
   * Splits the given StaticStrings into smaller staticString objects from
   * delimiter provided and returns a vector of new StaticString objects
   * splitted from delimiter.
   * 
   * @param delimiter char The delimiter to split StaticString.
   * @return std::vector<StaticString<MaxSize>> Collection of splitted StaticString objects.
   */
  std::vector<StaticString<MaxSize>> split(char delimiter) const {

    std::vector<StaticString<MaxSize>> result;

    StaticString<MaxSize> new_string;
    
    for (std::size_t i = 0; i < mCurrentSize; ++i) {
      if (mString[i] == delimiter) {
        result.push_back(new_string);
        new_string = StaticString<MaxSize>(); 
      } else {
        new_string.append(mString[i]);
      }
    }
    
    result.push_back(new_string);

    return result;
  }

  /**
   * @brief Compares this StaticString to another using a custom comparator.
   * 
   * Useful for lexicographical or conditional comparison beyond equality.
   * @attention Inorder to make comparison both StaticString objects must be 
   * equal length.
   * 
   * @tparam Func A comparator function taking two characters and returning a bool.
   * @param rhs The StaticString to compare against.
   * @param lambda The comparator function.
   * @return true If all character comparisons return true.
   * @return false Otherwise.
   */
  template <typename Func>
  constexpr bool compare(const StaticString& rhs, Func lambda) const noexcept {
    if (mCurrentSize != rhs.mCurrentSize) return false;

    for (std::size_t i = 0; i < mCurrentSize; ++i) {
      if (!lambda(mString[i], rhs.mString[i])) {
        return false;
      }
    }
    return true;
  }

  /**
   * @brief Returns a string_view of the current StaticString content.
   * 
   * @return constexpr std::string_view A view of the current string data.
   */
  constexpr std::string_view view() const noexcept { 
    return std::string_view(mString, mCurrentSize); 
  }

private: 
  /// @brief Constant value for StaticString null terminator used.
  static constexpr char null_terminator = '\0';

  /// @brief Array of characters stores the string with a predefined size.
  char mString[MaxSize + 1] = {null_terminator};  // Array of characters '\0'

  /// @brief size_t The current length of the string.
  std::size_t mCurrentSize = 0;  // Tracks the current length of the string.
};

/**
 * @brief This is a custom hasher for StaticString class.
 * 
 * To use custom hasher for operations in unorderd_map pass the hasher as param.
 * std::unordered_map<cse::StaticString<32>, int, cse::StaticStringHasher<32>> myMap;
 * 
 * @tparam MaxSize Max limit defined for StaticString.
 */
template <std::size_t MaxSize>
struct StaticStringHasher {
  /**
   * @brief Hash function operator for StaticString.
   * 
   * Allows StaticString to be used in hashed containers like std::unordered_map.
   * 
   * @param obj The StaticString object to hash.
   * @return std::size_t The hash value.
   */
  std::size_t operator()(const cse::StaticString<MaxSize>& obj) const noexcept {
    return std::hash<std::string_view>{}(obj.view());
  }
};

}  // namespace cse

#endif  // CSE_STATIC_STRING_HPP_