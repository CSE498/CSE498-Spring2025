/**
 * @file FormattedText.cpp
 *
 * @author Allie Ianello
 *
 */

#pragma once

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
  if (type != TextType::Raw) return text;  // For non-raw text, return as-is.

  std::string escaped = text;
  // Replace '&' first to avoid double-escaping.
  size_t pos = 0;
  while ((pos = escaped.find("&", pos)) != std::string::npos) {
    escaped.replace(pos, 1, "&amp;");
    pos += 5;  // length of "&amp;"
  }
  pos = 0;
  while ((pos = escaped.find("<", pos)) != std::string::npos) {
    escaped.replace(pos, 1, "&lt;");
    pos += 4;  // length of "&lt;"
  }
  pos = 0;
  while ((pos = escaped.find(">", pos)) != std::string::npos) {
    escaped.replace(pos, 1, "&gt;");
    pos += 4;  // length of "&gt;"
  }
  return escaped;
}

/**
 * @brief Function to format the text based on its type.
 *
 * @return std::string
 */
std::string FormattedText::getFormattedOutput() const {
  if (type == TextType::HTML)
    return text;  // Return HTML unchanged so it renders correctly in a browser.
  else
    return getEscapedText();  // For raw text, return the escaped version.
}
}  // namespace cse