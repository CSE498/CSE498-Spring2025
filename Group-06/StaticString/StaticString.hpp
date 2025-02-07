/**
 * @file StaticString.hpp
 * @author Mehmet Efe Caylan
 * @brief StaticString Class implementatio file.
 * @version 0.1
 * @date 2025-02-06
 *
 */

#pragma once

#include <cassert>
#include <cstring>
#include <stdexcept>

namespace cse {

/**
 * @brief StaticString Class that provides faster string operations by static size.
 *
 * @tparam MaxSize Static size_t value to limit our string's size.
 */
template <std::size_t MaxSize>
class StaticString {
   private:
    /// @brief Array of characters with a predefined size.
    char mString[MaxSize + 1];  // Array of characters that stores our string with '\0'
                                // terminator at the end.

    /// @brief size_t current size of the string.
    std::size_t currentSize{};  // Tracks the current size of string.

   public:
    /// @brief Constant value for StaticString npos, not found value.
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    /**
     * @brief Construct a new Static String object
     * If the given string is empty then initialize it as empty.
     */
    StaticString() : currentSize(0) { mString[0] = '\0'; }

    /**
     * @brief Construct a new Static String object with a non-empty string
     *
     * @param cstr Pointer to an array of characters that corresponds to our
     * string value.
     */
    StaticString(const char* cstr) : currentSize(0) {
        // Loop over given array of characters until find null terminator
        // or the size exceeds static size initialized
        while (cstr[currentSize] != '\0' && currentSize < MaxSize) {
            mString[currentSize] = cstr[currentSize];
            ++currentSize;
        }
        if (cstr[currentSize] != '\0') {
            // The provided string is longer than MaxSize defined.
            throw std::length_error(
                "Input string exceeds StaticString defined maximum size.");
        }
        // Initialize the last location of the string to null terminator
        mString[currentSize] = '\0';
    }

    /**
     * @brief Construct a new Static String object from copying another Static String
     * object.
     *
     * @param staticString Static String object to be coppied.
     */
    StaticString(const StaticString& staticString)
        : currentSize(staticString.currentSize) {
        std::strcpy(mString, staticString.mString);
    }

    /**
     * @brief Assignment operator for Static String.
     *
     * @param staticString Referance to Static String object to be assigned.
     * @return StaticString& Address of Static String object.
     */
    StaticString& operator=(const StaticString& staticString) {
        // Avoid assigning to itself
        assert(this != &staticString && "Assigning object itself is not allowed.");

        if (this != &staticString) {
            currentSize = staticString.currentSize;
            std::copy(staticString.mString, staticString.mString + currentSize + 1,
                      mString);
        }
        return *this;
    }

    /**
     * @brief Return the size of string.
     *
     * @return std::size_t static size of the string
     */
    std::size_t size() const { return MaxSize; }

    /**
     * @brief Return the length of the string.
     *
     * @return std::size_t Length of the string.
     */
    std::size_t length() const { return currentSize; }

    /**
     * @brief Get the stored string in StaticString
     *
     * @return const char* Pointer to the start of the string.
     */
    const char* get_str() const { return mString; }

    /**
     * @brief Find a character in the string.
     * 
     * @param c character to be searched.
     * @return std::size_t Position of the character or npos if not found.
     */
    std::size_t find(char c) const {
        for (std::size_t i = 0; i < currentSize; ++i) {
            if (mString[i] == c) return i;
        }
        return npos;
    }

    /**
     * @brief Index operator to get value in the specific index of string
     *
     * @param index size_t index value
     * @return char& Address of indexed char value
     */
    char& operator[](std::size_t index) {
        assert(index <= currentSize && "Index value is out of range.");

        if (index >= currentSize) {
            throw std::out_of_range("Indexed value is out of range, Index = " +
                                    std::to_string(index));
        }
        return mString[index];
    }

    /**
     * @brief Index operator to get constant value in the specific index of string
     *
     * @param index size_t index value
     * @return const char& Address of constant indexed char value
     */
    const char& operator[](std::size_t index) const {
        assert(index <= currentSize && "Index value is out of range.");

        if (index >= currentSize) {
            throw std::out_of_range("Indexed value is out of range, Index = " +
                                    std::to_string(index));
        }
        return mString[index];
    }
};

}  // namespace cse