/**
 * @file TextBox.hpp
 *
 * @author Allie Ianello
 *
 */
#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <algorithm>
#include <cassert>
#include <string>

#include "FormattedText.hpp"

namespace cse {
/**
 * @brief Configuration structure for TextBox.
 *
 */
struct TextBoxConfig {
  FormattedText content;
  int width;
  int height;
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
   * @brief Construct a new Text Box object.
   *
   */
  TextBox() = default;

  /**
   * @brief Construct a new TextBox.
   *
   * @param boxID If empty, an ID is auto-generated.
   * @param config The configuration for the TextBox.
   */
  TextBox(std::string boxID, const TextBoxConfig& config)
      : id(boxID.empty() ? generateID() : boxID),
        content(config.content),
        width(config.width),
        height(config.height) {}

  /**
   * @brief Copy constructor.
   */
  TextBox(const TextBox& other)
      : id(other.id),
        content(other.content),
        width(other.width),
        height(other.height) {}

  /**
   * @brief Move constructor.
   */
  TextBox(TextBox&& other) noexcept
      : id(std::move(other.id)),
        content(std::move(other.content)),
        width(other.width),
        height(other.height) {}

  /**
   * @brief Copy assignment operator.
   */
  TextBox& operator=(const TextBox& other) {
    if (this != &other) {
      id = other.id;
      content = other.content;
      width = other.width;
      height = other.height;
    }
    return *this;
  }

  /**
   * @brief Move assignment operator.
   */
  TextBox& operator=(TextBox&& other) noexcept {
    if (this != &other) {
      id = std::move(other.id);
      content = std::move(other.content);
      width = other.width;
      height = other.height;
    }
    return *this;
  }

  /**
   * @brief Get the FormattedText object.
   *
   * @return const FormattedText&
   */
  const FormattedText& getFormattedText() const { return content; }

  /**
   * @brief Set the FormattedText object.
   *
   * @param newFormattedText
   */
  void setFormattedText(const FormattedText& newFormattedText) {
    content.updateFrom(newFormattedText);
  }

  /**
   * @brief Get the ID object.
   *
   * @return std::string
   */
  std::string getID() const {
    assert(!id.empty() && "TextBox ID should never be empty!");
    return id;
  }

  /**
   * @brief Get the Width object.
   *
   * @return int
   */
  int getWidth() const { return width; }

  /**
   * @brief Get the Height object.
   *
   * @return int
   */
  int getHeight() const { return height; }

  /**
   * @brief Resize the Text Box.
   *
   * @param newWidth
   * @param newHeight
   */
  void resize(int newWidth, int newHeight) {
    // Clamp to zero for negative inputs.
    width = std::max(0, newWidth);
    height = std::max(0, newHeight);
  }

  /**
   * @brief Clear the Text Box by calling clearText on the FormattedText object.
   *
   */
  void clearText() { content.clearText(); }

  /**
   * @brief Append text to the Text Box by calling appendText on the
   * FormattedText object.
   *
   * @param additionalText
   */
  void appendText(const std::string& addText) { content.appendText(addText); }

  /**
   * @brief Generate a unique ID for a TextBox.
   *
   * @return std::string
   */
  static std::string generateID() {
    static int counter = 1;
    return "textbox-" + std::to_string(counter++);
  }

 private:
  std::string id;  // Unique identifier for the TextBox.
  FormattedText content;
  int width = 0;
  int height = 0;
};
}  // namespace cse

#endif  // TEXTBOX_H