/**
 * @file StringSet.h
 * @author Orhan Aydin
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

    void insert(const std::string &str);

    void erase(const std::string &str);

    void clear();

    size_t size() const;

    bool empty() const;

    StringSet Union(const StringSet &other) const;

    StringSet Intersection(const StringSet &other) const;

};
}
