/**
 * @file WebLayout.h
 * @author Mary Holt
 *
 */

#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <emscripten.h>
#include "../Image/image.hpp"
#include "../TextBox/TextBox.hpp"

namespace cse {

struct TextBoxLayout {
  std::shared_ptr<TextBox> textBox;
  int yPos;
  int xPos;

  TextBoxLayout() : textBox(), xPos(0), yPos(0) {};

  TextBoxLayout(std::shared_ptr<TextBox> textBox, int x, int y)
      : textBox(std::move(textBox)), xPos(x), yPos(y) {}

  bool operator==(const TextBoxLayout &textboxLayout) const {
    return ((textboxLayout.textBox->getFormattedText().getText() == textBox->getFormattedText().getText())
        && (textboxLayout.textBox->getWidth() == textBox->getWidth())
        && (textboxLayout.textBox->getHeight() == textBox->getHeight()));
  }
};

struct ImageLayout {
  std::shared_ptr<Image> image;
  int yPos;
  int xPos;

  ImageLayout() : image(), yPos(0), xPos(0) {};

  ImageLayout(std::shared_ptr<Image> image, int x, int y)
      : image(std::move(image)), yPos(y), xPos(x) {}

  bool operator==(const ImageLayout &imageLayout) const {
    return ((imageLayout.image->getURL() == image->getURL()) && (imageLayout.image->getWidth() == image->getWidth())
        && (imageLayout.image->getHeight() == image->getHeight()));
  }
};

class WebLayout {
 private:
  std::vector<TextBoxLayout> textBoxes;
  std::vector<ImageLayout> images;

  void const renderTextBox(const std::string &msg, const int &width, const int &height, const int &x, const int &y);
  void const renderImage(const std::string &url, const int &width, const int &height, const int &x, const int &y);

 public:
  WebLayout() = default;
  ~WebLayout() = default;
  void addImage(const ImageLayout &image);
  void removeImage(const ImageLayout &image);
  void addTextBox(const TextBoxLayout &textBox);
  void removeTextBox(const TextBoxLayout &textBox);
  void loadPage();
  const std::vector<ImageLayout> &getImages();
  const std::vector<TextBoxLayout> &getTextBoxes();

  //TODO: Future Implement Clear Layout Function

};
}
