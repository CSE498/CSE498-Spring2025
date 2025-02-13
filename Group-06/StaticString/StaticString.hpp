/**
 * @file StaticString.hpp
 * @author Mehmet Efe Caylan
 * @brief StaticString Class implementation file.
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
    char mString[MaxSize + 1] = { '\0' };  // Array of characters that stores our string with '\0'
                                // terminator at the end.

    /// @brief size_t current size of the string.
    std::size_t mCurrentSize = 0;  // Tracks the current size of string.

    /**
     * @brief Update the current length of the StaticString
     * 
     * After changes made to the string, updates the length of the staticString
     * New size calculated based until first hit to null terminator.
     * Changes occured after a null terminator such as [test\0\0test2\0] wouldn't
     * be reflected on length.
     */
    void Update_Length()
    {
        size_t newLength = 0;
        while (mString[newLength] != '\0' && newLength < MaxSize) {
            ++newLength;
        }
        mCurrentSize = newLength;
    }

   public:
    /// @brief Constant value for StaticString npos, not found value.
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    /*----------------------CONSTRUCTORS--------------------------------------*/

    /**
     * @brief Construct a new Static String object
     * If the given string is empty then initialize it as empty.
     */
    StaticString() : mCurrentSize(0) { }

    /**
     * @brief Construct a new Static String object with a non-empty string
     *
     * @param cstr Pointer to an array of characters that corresponds to our
     * string value.
     */
    StaticString(const char* cstr) : mCurrentSize(0) {
        // Loop over given array of characters until find null terminator
        // or the size exceeds static size initialized
        while (cstr[mCurrentSize] != '\0' && mCurrentSize < MaxSize) {
            mString[mCurrentSize] = cstr[mCurrentSize];
            ++mCurrentSize;
        }

        // The provided string is longer than MaxSize defined.
        assert(mCurrentSize <= MaxSize && "Error: Input string exceeds StaticString defined maximum size.");

        // Initialize the last location of the string to null terminator
        mString[mCurrentSize] = '\0'; // Should be null terminator already.
        mString[MaxSize] = '\0';
    }

    /**
     * @brief Construct a new Static String object from copying another Static String
     * object.
     *
     * @param staticString Static String object to be coppied.
     */
    StaticString(const StaticString& staticString)
        : mCurrentSize(staticString.mCurrentSize) {
        std::copy(staticString.mString, staticString.mString + MaxSize + 1, mString);
    }

    /**
     * @brief Construct a new Static String object copying from another StaticString
     * 
     * To be able to copy form another object, new StaticString object must be 
     * equal or greater sized in terms of static limit defined.
     * 
     * @tparam newMaxSize New allocated objects MaxSize value
     * @param staticString StaticString object
     */
    template <std::size_t newMaxSize>
    StaticString(const StaticString<newMaxSize>& staticString) {
        
        // Check if the string that we will copy is larger than new MaxSize defined
        assert(staticString.size() <= MaxSize && "Error: The length of coppied string exceeds static limit defined.");

        std::copy(staticString.get_str(), staticString.get_str() + staticString.size(), mString);

        mCurrentSize = staticString.length();
    }


    /*----------------------------OPERATORS-----------------------------------*/

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
            
            // Check if the string that we will copy is larger than new MaxSize defined
            assert(staticString.size() <= MaxSize && "Error: The length of coppied string exceeds static limit defined.");
            std::copy(staticString.mString, staticString.mString + staticString.size(),
                      mString);

            mCurrentSize = staticString.mCurrentSize;
        }
        return *this;
    }


    /**
     * @brief Assign staticString to a new string
     * 
     * New string to be assigned must be shorter than size limit or exact 
     * lenght with size limit. When a StaticString assigned to a nullptr, 
     * it will automatically clear itself and will be empty as well as empty string
     * initialization. 
     * 
     * @param cstr string to be coppied
     * @return StaticString& return objects itself
     */
    StaticString& operator=(const char* cstr)
    {   
        // Empty string or nullptr assign handle
        if(!cstr)
        {
            for(std::size_t i = 0; i <= MaxSize; ++i)
            {
                mString[i] = '\0';
            }
            mCurrentSize = 0;
            return *this;
        }

        size_t newLength = 0;
        // Copy the new string
        while (cstr[newLength] != '\0' && newLength < MaxSize) {
            mString[newLength] = cstr[newLength];
            ++newLength;
        }

        assert((newLength < MaxSize || cstr[newLength] == '\0') && "Invalid size for assign input, input string is too long.");

        mCurrentSize = newLength;
        mString[mCurrentSize] = '\0';

        return *this;
    }    

    /**
     * @brief Index operator to get value in the specific index of string
     *
     * @param index size_t index value
     * @return Indexed char value
     */
    char operator[](std::size_t index) {
    
        // Indexed value is out of range or trying to index to the null terminator at the end
        assert(index <= MaxSize && "Index value is out of range.");

        return mString[index];
    }

    bool operator==(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) == 0;
    }
    
    bool operator==(const char* rhs) const {
        return std::strcmp(this->get_str(), rhs) == 0;
    }

    bool operator!=(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) != 0;
    }

    bool operator<(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) < 0;
    }

    bool operator>(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) > 0;
    }   

    bool operator<=(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) <= 0;
    }

    bool operator>=(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) >= 0;
    }


    /*--------------------------FUNCTIONS-------------------------------------*/

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
    std::size_t length() const { return mCurrentSize; }

    /**
     * @brief Get the stored string in StaticString
     *
     * @return const char* Pointer to the start of the string.
     */
    const char* get_str() const { return mString; }

    /**
     * @brief Get the stored string in StaticString
     * 
     * @return char* Pointer to the start of the string.
     */
    char * get_str() { return mString; }


    /**
     * @brief Find a character in the string.
     * 
     * @param c character to be searched.
     * @return std::size_t Position of the character or npos if not found.
     */
    std::size_t find(char c) const {
        for (std::size_t i = 0; i < mCurrentSize; ++i) {
            if (mString[i] == c) return i;
        }
        return npos;
    }

    /**
     * @brief Set the given character to given index
     * 
     * @param index Index to be changed
     * @param c Char value to be assigned 
     */
    void set(const size_t& index, const char& c)
    {
        assert(index < MaxSize && "Index value is out of range");
        mString[index] = c;
        Update_Length();    // Update the current length
    }


    /**
     * @brief Converts the StaticString to an std::string.
     *
     * @return std::string The equivalent std::string.
     */
    std::string to_string() const {
        return std::string(mString, mCurrentSize);
    }

    
    
};

}  