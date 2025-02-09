/**
 * @file WebLayout.h
 * @author Mary Holt
 *
 */

#ifndef CSE498_SPRING2025_GROUP_09_WEBLAYOUT_WEBLAYOUT_H
#define CSE498_SPRING2025_GROUP_09_WEBLAYOUT_WEBLAYOUT_H

#pragma once
#include <iostream>
#include <vector>
#include <emscripten.h>

/**
 * Temporary Image struct in place of Image class
 */
struct Image {
  int xLoc;
  int yLoc;
  int width;
  int height;
  std::string url;
  int id;

  bool operator==(const Image &image) const {
    return id == image.id;
  }
};

/**
 * Temporary TextBox struct in place of TextBox class
 */
struct TextBox {
  int xLoc;
  int yLoc;
  int width;
  int height;
  std::string text;
  int id;

  bool operator==(const TextBox &textBox) const {
    return id == textBox.id;
  }
};

class WebLayout {
 private:
  std::vector<TextBox> textBoxes;
  std::vector<Image> images;
  void PushTextBox(const std::string &msg, const int &width, const int &height);
  void PushImage(const std::string &url, const int &width, const int &height, const int &xLoc, const int &yLoc);

 public:
  WebLayout() = default;
  ~WebLayout() = default;
  void addImage(const Image &image);
  void removeImage(const Image &image);
  void addTextBox(const TextBox &textBox);
  void removeTextBox(const TextBox &textBox);
  void LoadPage();
  std::string GenerateJS();
  void TransitionToPage(const WebLayout &newPage);
};

#endif //CSE498_SPRING2025_GROUP_09_WEBLAYOUT_WEBLAYOUT_H
