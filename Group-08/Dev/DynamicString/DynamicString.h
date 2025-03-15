/**
 * @author Hannah Dale
 * @file DynamicString.h
 * @brief Declaration of the DynamicString class.
 */
#pragma once

#include <functional>
#include <string>
#include <vector>
#include <variant>

/**
 * @class DynamicString
 * @brief A class that holds both static and dynamic string segments, constructing
 *        a full string on demand by concatenating all segments.
 */
class DynamicString {
public:
    /// Alias to represent a dynamic text segment
    using str_fun_t = std::function<std::string()>;

    /// Constructors
    DynamicString();                                // Default
    DynamicString(const std::string &staticStr);    // Construct with one static segment
    DynamicString(str_fun_t func);                  // Construct with one dynamic segment

    /// Builds and returns the combined string
    std::string ToString() const;

    /// Append overloads
    DynamicString& Append(const std::string &staticStr);
    DynamicString& Append(str_fun_t func);

    /// Operator+ overloads
    friend DynamicString operator+(const DynamicString &lhs, const std::string &rhs);
    friend DynamicString operator+(const DynamicString &lhs, str_fun_t rhs);

private:
    /// The container that holds both string and function segments
    std::vector<std::variant<std::string, str_fun_t>> mSegments;
};