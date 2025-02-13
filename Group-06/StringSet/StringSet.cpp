/**
 * @file StringSet.cpp
 * @brief Implementation of StringSet class
 */

#include "StringSet.h"

/**
 * @brief Add str into the set named m_elements
 * @param str Added to m_elements
 */
void cse::StringSet::insert(const std::string& str)
{
    m_elements.insert(str);
}


/**
 * @brief Erase str from m_elements
 * @param str Deleted from m_elements
 */
void cse::StringSet::erase(const std::string &str)
{
    m_elements.erase(str);
}

/**
 * @brief Make m_elements empty
 */
void cse::StringSet::clear()
{
    m_elements.clear();
}


/**
 * @brief Get the size of set
 * @return Size of m_elements
 */
size_t cse::StringSet::size() const
{
    return m_elements.size();
}

/**
 * @brief Check if m_elements is empty
 * @return True if the set is empty, false otherwise
 */
bool cse::StringSet::empty() const
{
    return m_elements.empty();
}

/**
 * @brief Check if str in the set or not
 * @param str
 * @return 0 or 1. If str in the set returns 1 otherwise 0
 */
size_t cse::StringSet::count(const std::string &str) const
{
    return m_elements.count(str);
}



/**
 * @brief Union of two sets
 * @param other The second set
 * @return A new set that contains unique elements from both sets
 */
cse::StringSet cse::StringSet::Union(const StringSet& other)const
{
    // Create new set result
    StringSet result;

    for(const auto& str : m_elements)
    {
        // Add elements in m_elements to result
        result.insert(str);
    }

    for(const auto& str : other.m_elements)
    {
        // Add elements in other to result
        result.insert(str);
    }

    return result;
}


/**
 * @brief Intersection of two sets
 * @param other The second set
 * @return A set of common values in 2 sets
 */
cse::StringSet cse::StringSet::Intersection(const StringSet& other)const
{
    // Create new set result
    StringSet result;

    // Iterate through every element in m_elements
    for(const auto& str : m_elements)
    {
        // Check if we have str in other, if we don't .find
        // returns other.end() iterator, otherwise iterator pointing
        // to that element
        if(other.m_elements.find(str) != other.m_elements.end())
        {
            result.insert(str);
        }
    }

    return result;
}

/**
 * @brief Operates differentiation between two string sets
 * @param other the second set
 * @return the difference set
 */
cse::StringSet cse::StringSet::Difference(const cse::StringSet &other) const {
    // Create new set result
    StringSet result;

    // Iterate through every element in m_elements
    for(const auto& str : m_elements)
    {
        // Check if str not in other
        if(other.m_elements.find(str) == other.m_elements.end())
        {
            result.insert(str);
        }
    }

    return result;
}


/*
void cse::StringSet::Filter(std::function<bool(std::string &)> filter)
{

}

void cse::StringSet::FilterOut(std::function<bool(std::string &)> filter)
{

}
*/