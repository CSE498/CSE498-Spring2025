
/**
 * @author Hannah Dale
 * @file DynamicString.cpp
 */

#include "DynamicString.h"
#include <sstream>

DynamicString::DynamicString()
{
    // Default when mSegments is empty
}

/**
 * @brief Constructs a DynamicString initialized with one static string segment.
 * @param staticStr The initial static string.
 */
DynamicString::DynamicString(const std::string &staticStr)
{
    mSegments.push_back(staticStr);
}

/**
 * @brief Constructs a DynamicString initialized with one dynamic function segment.
 * @param func The function returning a std::string, invoked on each ToString() call.
 */
DynamicString::DynamicString(str_fun_t func)
{
    mSegments.push_back(func);
}

/**
 * @brief Appends a static string segment to the existing DynamicString.
 *
 * @param staticStr The static string to append.
 * @return A reference to this DynamicString, allowing chained calls.
 */
DynamicString& DynamicString::Append(const std::string &staticStr)
{
    mSegments.push_back(staticStr);
    return *this;
}

/**
 * @brief Appends a dynamic function segment to the existing DynamicString.
 *
 * @param func The std::function<std::string()> to append.
 * @return A reference to this DynamicString, allowing chained calls.
 */
DynamicString& DynamicString::Append(str_fun_t func)
{
    mSegments.push_back(func);
    return *this;
}

/**
 * @brief Concatenates a DynamicString with a std::string.
 *
 * Creates a new DynamicString by copying @p lhs, then appending @p rhs.
 *
 * @param lhs The left-hand DynamicString.
 * @param rhs A static string to append.
 * @return A new DynamicString containing lhs followed by rhs.
 */
DynamicString operator+(const DynamicString &lhs, const std::string &rhs)
{
    // Creates a new DynamicString object initialized from lhs
    DynamicString result(lhs);

    // Adds the string segment to the existing DynamicString object
    result.Append(rhs);

    // Return the new combined segments as one DynamicString
    return result;
}

/**
 * @brief Concatenates a DynamicString with a function segment.
 *
 * Creates a new DynamicString by copying @p lhs, then appending the function @p rhs,
 * which will be called on each ToString() call.
 *
 * @param lhs The left-hand DynamicString.
 * @param rhs A std::function that returns a std::string.
 * @return A new DynamicString containing lhs followed by the function segment.
 */
DynamicString operator+(const DynamicString &lhs, DynamicString::str_fun_t rhs)
{
    DynamicString result(lhs);
    result.Append(rhs);
    return result;
}

/**
 * @brief Builds and returns the full string, concatenating all segments in order.
 *
 * If a segment is a std::function<std::string()>, that function is called
 * on each invocation of ToString(), providing updated results.
 *
 * @return A std::string containing the combined text of all segments.
 */
std::string DynamicString::ToString() const
{
    std::string result; // create an initial string
    for (const auto &segment : mSegments)
    {
        // visit is a function from the <variant> header
        // USe to access each type in our vector
        std::visit(
            // A lambda that gets a reference to our result string
            // segValue represents the value held in std::variant (segment)
            [&result](auto &&segValue) {
            // Determines the type of the segment
            using segType = std::decay_t<decltype(segValue)>;
            // Checks if the segment is a std::string
            if constexpr (std::is_same_v<segType, std::string>)
            {
                result += segValue; // append the string
            }
            // If the segment is a function, call it
            else
            {
                // Call function to get the updated text and append it
                result += segValue();
            }
        }, segment);
    }
    return result;
}