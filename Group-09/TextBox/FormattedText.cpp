/**
 * @file FormattedText.cpp
 *
 * @author Allie Ianello
 *
 */

#include "FormattedText.hpp"

#include <algorithm>
#include <sstream>

namespace cse {
/**
 * @brief Function to escape special characters in raw text.
 *
 * @return std::string
 */
std::string FormattedText::getEscapedText() const {
  assert(!text.empty() && "Attempting to escape an empty text");

  std::ostringstream escaped;
  for (char c : text) {
    switch (c) {
      case '&':
        escaped << "&amp;";
        break;
      case '<':
        escaped << "&lt;";
        break;
      case '>':
        escaped << "&gt;";
        break;
      default:
        escaped << c;
    }
  }
  return escaped.str();
}

/**
 * @brief Function to format the text based on its type.
 *
 * @return std::string
 */
std::string FormattedText::getFormattedOutput() const {
  // If the text is HTML, return it as-is. Otherwise, escape special characters.
  return (type == TextType::HTML) ? text : getEscapedText();
}
}  // namespace cse