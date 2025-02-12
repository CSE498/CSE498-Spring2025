/**
 * @file FormattedText.hpp
 *
 * @author Allie Ianello
 *
 */

#pragma once

#include <cassert>
#include <string>

namespace cse {

/**
 * @enum TextType
 * @brief Specifies whether the text is raw or HTML formatted.
 */
enum class TextType { Raw, HTML };

/**
 * @brief Configuration structure for FormattedText.
 *
 */
struct FormattedTextConfig {
  std::string text;
  TextType type;
  std::string font;
  int fontSize;
  std::string color;
};

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
   * @brief Construct a new Formatted Text object.
   *
   */
  FormattedText() = default;

  /**
   * @brief Construct a new Formatted Text object.
   * @param text The text to be stored.
   * @param type The type of the text (Raw or HTML).
   * @param font The font of the text.
   * @param fontSize The font size of the text.
   * @param color The color of the text.
   *
   */
  FormattedText(const FormattedTextConfig& config)
      : text(config.text),
        type(config.type),
        font(config.font),
        fontSize(config.fontSize),
        color(config.color) {
    assert(!text.empty() && "Text should not be empty");
    assert(fontSize > 0 && "Font size must be positive");
  }

  /**
   * @brief Comparison operator for FormattedText.
   *
   * @param other
   * @return true if equal, false otherwise.
   */
  bool operator==(const FormattedText& other) const {
    return text == other.text && type == other.type && font == other.font &&
           fontSize == other.fontSize && color == other.color;
  }

  /**
   * @brief Get the Text object.
   *
   * @return const std::string&
   */
  const std::string& getText() const { return text; }

  /**
   * @brief Get the Type object.
   *
   * @return TextType
   */
  TextType getType() const { return type; }

  // Getters for font, fontSize, and color.
  const std::string& getFont() const { return font; }
  int getFontSize() const { return fontSize; }
  const std::string& getColor() const { return color; }

  /**
   * @brief Set the Text object.
   *
   * @param newText
   */
  void setText(const std::string& newText) { text = newText; }

  /**
   * @brief Set the Type object.
   *
   * @param newType
   */
  void setType(TextType newType) { type = newType; }

  // Setters for font, fontSize, and color.
  void setFont(const std::string& newFont) {
    assert(!newFont.empty() && "Font name should not be empty");
    font = newFont;
  }
  void setFontSize(int newSize) {
    assert(newSize > 0 && "Font size must be positive");
    fontSize = newSize;
  }
  void setColor(const std::string& newColor) {
    assert(!newColor.empty() && "Color should not be empty");
    color = newColor;
  }

  /**
   * @brief Retrieves the text with special characters escaped (if applicable).
   *
   * @return The escaped text as a std::string.
   */
  std::string getEscapedText() const;

  /**
   * @brief Get the Formatted Output object.
   *
   * @return std::string
   */
  std::string getFormattedOutput() const;

  /**
   * @brief Clear the text.
   *
   */
  void clearText() { text.clear(); }

  /**
   * @brief Append text to the current text.
   *
   * @param additionalText The text to append.
   */
  void appendText(const std::string& addText) { text += addText; }

  /**
   * @brief Update the current object with values from another FormattedText
   * object.
   *
   * @param other The other FormattedText object to copy values from.
   */
  void updateFrom(const FormattedText& other) {
    text = other.text;
    type = other.type;
    font = other.font;
    fontSize = other.fontSize;
    color = other.color;
  }

 private:
  std::string text = "";
  TextType type = TextType::Raw;
  std::string font = "Arial";
  int fontSize = 12;
  std::string color = "#000000";  // Default black text
};
}  // namespace cse
