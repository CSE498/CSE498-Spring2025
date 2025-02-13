/**
 * @file TextBox.hpp
 *
 * @author Allie Ianello
 *
 */
#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <algorithm>
#include <string>

namespace cse {
/**
 * @brief Configuration structure for TextBox.
 *
 */
struct TextBoxConfig {
  std::string text;  // Initial text
  int width;         // Initial width
  int height;        // Initial height
};

/**
 * @class TextBox
 * @brief A class to handle text boxes with formatted text.
 *
 * This class stores FormattedText and provides methods to manipulate it.
 */
class TextBox {
 public:
  /**
   * @brief Construct a new Text Box object
   *
   */
  TextBox() : text(""), width(0), height(0) {}

  /**
   * @brief Construct a new Text Box object
   * @param config The configuration for the TextBox.
   *
   */
  TextBox(const TextBoxConfig& config)
      : text(config.text), width(config.width), height(config.height) {}

  /**
   * @brief Compares two TextBox objects and determine if they are the same values
   * @param text_box to compare
   * @return true if same values
   */
  bool operator==(const TextBox &text_box) const {
    return ((text_box.text == text) && (text_box.width == width) && (text_box.height == height));
  }

  /**
   * @brief Get the Text object
   *
   * @return std::string
   */
  std::string getText() const { return text; }

  /**
   * @brief Set the Text object
   *
   * @param newText
   */
  void setText(const std::string& newText) { text = newText; }

  /**
   * @brief Get the Width object
   *
   * @return int
   */
  int getWidth() const { return width; }

  /**
   * @brief Get the Height object
   *
   * @return int
   */
  int getHeight() const { return height; }

  /**
   * @brief Resize the Text Box
   *
   * @param newWidth
   * @param newHeight
   */
  void resize(int newWidth, int newHeight) {
    width = std::max(0, newWidth);
    height = std::max(0, newHeight);
  }

  /**
   * @brief Clear the Text Box
   *
   */
  void clearText() { text.clear(); }

  /**
   * @brief Append text to the Text Box
   *
   * @param additionalText
   */
  void appendText(const std::string& additionalText) { text += additionalText; }

 private:
  std::string text;
  int width;
  int height;
};
}  // namespace cse

#endif  // TEXTBOX_H