/**
 * @file StringSet.h
 * @brief Header file for StringSet class
 */

#pragma once

#include <unordered_set>
#include <string>
#include <vector>
#include <iostream>

namespace cse{
class StringSet {

private:

    /// @brief Unordered set of strings
    std::unordered_set <std::string> m_elements;

public:

    using iterator = std::unordered_set<std::string>::iterator;

    /**
     * @brief Begin iterator
     * @return
     */
    iterator begin() {return m_elements.begin();}

    /**
     * @brief End iterator
     * @return
     */
    iterator end() {return m_elements.end();}

    void insert(const std::string &str);

    void erase(const std::string &str);

    void clear();

    size_t size() const;

    bool empty() const;

    size_t count(const std::string &str) const;

    StringSet Union(const StringSet &other) const;

    StringSet Intersection(const StringSet &other) const;

    StringSet Difference(const StringSet &other) const;

   // void Filter( std::function<bool(std::string & in)> filter );

  //  void FilterOut( std::function<bool(std::string & in)> filter );

};
}
