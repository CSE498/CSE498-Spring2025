/**
 * @file WebLayout.h
 * @author Mary Holt
 *
 */

#pragma once
#include <iostream>
#include <vector>
#include <emscripten.h>
#include "../Image/image.hpp"
#include "../TextBox/TextBox.hpp"

namespace cse {

struct TextBoxLayout {
  TextBox textBox;
  int y;
  int x;

  TextBoxLayout() : textBox(), x(0), y(0) {};

  TextBoxLayout(const TextBox &textBox, int x, int y)
      : textBox(textBox), x(x), y(y) {}

  bool operator==(const TextBoxLayout &textboxLayout) const {
    return ((textboxLayout.textBox.getText() == textBox.getText())
        && (textboxLayout.textBox.getWidth() == textBox.getWidth())
        && (textboxLayout.textBox.getHeight() == textBox.getHeight()));
  }
};

struct ImageLayout {
  Image image;
  int y;
  int x;

  ImageLayout() : image("", 0, 0), x(0), y(0) {};

  ImageLayout(const Image &image, int x, int y)
      : image(image), x(x), y(y) {}

  bool operator==(const ImageLayout &imageLayout) const {
    return ((imageLayout.image.getURL() == image.getURL()) && (imageLayout.image.getWidth() == image.getWidth())
        && (imageLayout.image.getHeight() == image.getHeight()));
  }
};

class WebLayout {
 private:
  std::vector<TextBoxLayout> textBoxes;
  std::vector<ImageLayout> images;

  void PushTextBox(const std::string &msg, const int &width, const int &height, const int &x, const int &y);
  void PushImage(const std::string &url, const int &width, const int &height, const int &x, const int &y);

 public:
  WebLayout() = default;
  ~WebLayout() = default;
  void addImage(const ImageLayout &image);
  void removeImage(const ImageLayout &image);
  void addTextBox(const TextBoxLayout &textBox);
  void removeTextBox(const TextBoxLayout &textBox);
  void LoadPage();
  void TransitionToPage(const WebLayout &newPage);
  std::vector<ImageLayout> getImages();
  std::vector<TextBoxLayout> getTextBoxes();

};
}
