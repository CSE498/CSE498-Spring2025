/**
 * @file FormattedText.hpp
 *
 * @author Allie Ianello
 *
 */

#pragma once

#include <string>

namespace cse {
/**
 * @class FormattedText
 * @brief A class to handle formatted text, either raw or HTML.
 *
 * This class provides functionality to store and retrieve text,
 * while distinguishing between raw text and formatted HTML.
 */
class FormattedText {
 public:
  /**
   * @enum TextType
   * @brief Specifies whether the text is raw or HTML formatted.
   */
  enum class TextType { Raw, HTML };

  /**
   * @brief Construct a new Formatted Text object
   * @param text The text to be stored.
   */
  FormattedText() : text(""), type(TextType::Raw) {}

  /**
   * @brief Construct a new Formatted Text object
   * @param text The text to be stored.
   * @param type The type of the text (Raw or HTML).
   */
  FormattedText(const std::string& text, TextType type)
      : text(text), type(type) {}

  /**
   * @brief Get the Text object
   *
   * @return const std::string&
   */
  const std::string& getText() const { return text; }

  /**
   * @brief Get the Type object
   *
   * @return TextType
   */
  TextType getType() const { return type; }

  /**
   * @brief Set the Text object
   *
   * @param newText
   */
  void setText(const std::string& newText) { text = newText; }

  /**
   * @brief Set the Type object
   *
   * @param newType
   */
  void setType(TextType newType) { type = newType; }

  /**
   * @brief Retrieves the text with special characters escaped (if applicable).
   *
   * @return The escaped text as a std::string.
   */
  std::string getEscapedText() const;

  /**
   * @brief Get the Formatted Output object
   *
   * @return std::string
   */
  std::string getFormattedOutput() const;

 private:
  std::string text;  // The actual text content.
  TextType type;     // The format type (Raw or HTML).
};
}  // namespace cse
