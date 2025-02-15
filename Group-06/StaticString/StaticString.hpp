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
        assert(staticString.length() <= MaxSize && "Error: The length of coppied string exceeds static limit defined.");

        std::copy(staticString.get_str(), staticString.get_str() + staticString.length(), mString);

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
            assert(staticString.length() <= MaxSize && "Error: The length of coppied string exceeds static limit defined.");
            std::copy(staticString.mString, staticString.mString + staticString.length(),
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

        // Replace remaining part of the string with null terminator
        for (size_t i = newLength; i <= MaxSize; ++i) {
            mString[i] = '\0';
        }

        mCurrentSize = newLength;
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
        assert(index < mCurrentSize && "Index value is out of range.");
        return mString[index];
    }


    bool operator==(const StaticString &rhs) const {
        return mCurrentSize == rhs.mCurrentSize && std::strcmp(mString, rhs.mString) == 0;
    }
    
    bool operator==(const char* rhs) const {
        if (!rhs) return false;
        assert(rhs != nullptr && "Nullptr comparsions not a legal comparison");
        return std::strcmp(mString, rhs) == 0;
    }
    
    bool operator!=(const StaticString &rhs) const {
        return !(*this == rhs);
    }
    
    bool operator!=(const char* rhs) const {
        return std::strcmp(mString, rhs) != 0;
    }
    
    bool operator<(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) < 0; 
    }
    
    bool operator<(const char* rhs) const {
        if (!rhs) return false;
        assert(rhs != nullptr && "Nullptr comparsions not a legal comparison");
        return std::strcmp(mString, rhs) < 0;
    }
    
    bool operator>(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) > 0; 
    }
    
    bool operator>(const char* rhs) const {
        if (!rhs) return true;
        assert(rhs != nullptr && "Nullptr comparsions not a legal comparison");        
        return std::strcmp(mString, rhs) > 0;
    }
    
    bool operator<=(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) <= 0;
    }
    
    bool operator<=(const char* rhs) const {
        if (!rhs) return false;
        assert(rhs != nullptr && "Nullptr comparsions not a legal comparison");
        return std::strcmp(mString, rhs) <= 0;
    }
    
    bool operator>=(const StaticString &rhs) const {
        return std::strcmp(mString, rhs.mString) >= 0;
    }
    
    bool operator>=(const char* rhs) const {
        if (!rhs) return true;
        assert(rhs != nullptr && "Nullptr comparsions not a legal comparison");
        return std::strcmp(mString, rhs) >= 0;
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
    std::size_t find(const char& c) const {
        for (std::size_t i = 0; i < mCurrentSize; ++i) {
            if (mString[i] == c) return i;
        }
        return npos;
    }

    /**
     * @brief Set the given character to given index
     * 
     * Index starts from 0, if the MaxSize is 10 then last possible index is 9
     * 
     * @param index Index to be changed
     * @param c Char value to be assigned 
     */
    void set(const size_t& index, const char& c)
    {
        assert(index < mCurrentSize && "Index value is out of range");
        if(index >= mCurrentSize || index >= MaxSize)
        {
            throw std::out_of_range("Index value is out of range");
        }

        // If user explicitly tries to cut their strings with null terminator
        // Handle the size appropriately
        if(c == '\0')
        {   
            mCurrentSize = index;
        }
        mString[index] = c;
    }


    /**
     * @brief Converts the StaticString to an std::string.
     *
     * @return std::string The equivalent std::string.
     */
    std::string to_string() const {
        return std::string(mString, mCurrentSize);
    }

    

    /*--------------------- STRING OPERATIONS ----------------------*/

    void append(const char * cstr) {

        const std::size_t cstr_length = std::strlen(cstr);

        assert((mCurrentSize + cstr_length <= MaxSize) && "Appending string exceeds maximum size");
        if(mCurrentSize + cstr_length > MaxSize)
        {
            throw std::out_of_range("Static limit exceeded, appended string must be within limits defined");
        }

        std::copy(cstr, cstr + cstr_length, mString + mCurrentSize);

        mCurrentSize += cstr_length;
        mString[mCurrentSize] = '\0';
    }

    void append(const char & character) {

        assert((mCurrentSize + 1 <= MaxSize) && "Appending string exceeds maximum size");
        if(mCurrentSize + 1 > MaxSize)
        {
            throw std::out_of_range("Static limit exceeded, appended string must be within limits defined");
        }

        mString[mCurrentSize] = character;
        mCurrentSize++;
        mString[mCurrentSize] = '\0';
    }

    void append(const std::string & str) {

        const std::size_t str_length = str.length();

        assert((mCurrentSize + str_length < MaxSize) && "Appending string exceeds maximum size");
        if(mCurrentSize + str_length >= MaxSize)
        {
            throw std::out_of_range("Static limit exceeded, appended string must be within limits defined");
        }

        std::copy(str.begin(), str.end(), mString + mCurrentSize);

        mCurrentSize += str_length;
        mString[mCurrentSize] = '\0';
    }

    void append(const std::string_view & str) {

        const std::size_t str_length = str.length();
    
        assert((mCurrentSize + str_length < MaxSize) && "Appending string exceeds maximum size");
        if (mCurrentSize + str_length >= MaxSize) {
            throw std::out_of_range("Static limit exceeded, appended string must be within limits defined");
        }
    
        std::copy(str.begin(), str.end(), mString + mCurrentSize);
    
        mCurrentSize += str_length;
        mString[mCurrentSize] = '\0';
    }


    StaticString & concat(const StaticString& rhs) {
        assert((mCurrentSize + rhs.mCurrentSize <= MaxSize) && "Concatenated string exceeds maximum size");\

        if(mCurrentSize + rhs.mCurrentSize > MaxSize)
        {
            throw std::out_of_range("Static limit exceeded, concatinated string must be within limits defined");
        }

        std::copy(rhs.mString, rhs.mString + rhs.mCurrentSize + 1, mString + mCurrentSize);
        mCurrentSize += rhs.mCurrentSize;
        mString[mCurrentSize] = '\0';
        return *this;
    }

    /**
     * @brief 
     * Start index is inclusive while end index exclusive.
     * @param start 
     * @param end 
     * @return std::string_view 
     */
    std::string_view substr(std::size_t start, std::size_t end) const {

        assert((start < end || end <= mCurrentSize) && "Index provided for substring are invalid");

        if (start > end || end > mCurrentSize) {
            throw std::out_of_range("Invalid substring request");
        }
        return std::string_view(mString + start, end - start);
    }
    
};

}  