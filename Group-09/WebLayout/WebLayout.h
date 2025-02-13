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

class WebLayout {
 private:
  std::vector<TextBox> textBoxes;
  std::vector<Image> images;

  void PushTextBox(const std::string &msg, const int &width, const int &height);
  void PushImage(const std::string &url, const int &width, const int &height);

 public:
  WebLayout() = default;
  ~WebLayout() = default;
  void addImage(const Image &image);
  void removeImage(const Image &image);
  void addTextBox(const TextBox &textBox);
  void removeTextBox(const TextBox &textBox);
  void LoadPage();
  void TransitionToPage(const WebLayout &newPage);
  std::vector<Image> getImages();
  std::vector<TextBox> getTextBoxes();

};
}
