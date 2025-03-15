/**
 * @file WebLayout.cpp
 * @author Mary Holt
 *
 */

#include <iostream>
#include <cassert>
#include "WebLayout.h"

namespace cse {
/**
 * Adds an image to the web layout
 * @param image to be added
 */
void WebLayout::addImage(const ImageLayout &image) {
  images.push_back(image);
}

/**
 * Removes a specific image from the web layout
 * @param image to be removed
 */
void WebLayout::removeImage(const ImageLayout &image) {
  auto it = std::find(images.begin(), images.end(), image);
  if (it != images.end()) {
    images.erase(it);
  }
}

/**
 * Adds a textbox to the web layout
 * @param textBox to be added
 */
void WebLayout::addTextBox(const TextBoxLayout &textBox) {
  textBoxes.push_back(textBox);
}

/**
 * Removes a textbox from the web layout
 * @param textBox to be removed
 */
void WebLayout::removeTextBox(const TextBoxLayout &textBox) {
  auto it = std::find(textBoxes.begin(), textBoxes.end(), textBox);
  if (it != textBoxes.end()) {
    textBoxes.erase(it);
  }
}

/**
 * Gets images vector of web layout
 * @return images that are connected
 */
std::vector<ImageLayout> WebLayout::getImages() {
  return images;
}

/**
 * Gets text boxes vector of web layout
 * @return textBoxes that are connected
 */
std::vector<TextBoxLayout> WebLayout::getTextBoxes() {
  return textBoxes;
}

/**
 * Converts textbox attributes into html
 * @param msg text of the textbox
 * @param width width of the textbox
 * @param height height of the textbox
 */
void WebLayout::PushTextBox(const std::string &msg, const int &width, const int &height, const int &x, const int &y) {

  assert(width > 0 && height > 0); //assert width and height are positive
  assert(x > 0 && y > 0); //assert x and y are positive

  EM_ASM({
           var msg = UTF8ToString($0);
           var width = $1;
           var height = $2;
           var x = $3;
           var y = $4;


           // Calculate the ratio to view height/width (1%)
           var widthRatio = document.documentElement.clientWidth / 100.0;
           var heightRatio = document.documentElement.clientHeight / 100.0;

           // Don't let placement exceed 100% of view width/height
           if (width > 100) { width = 100; }
           if (height > 95) { height = 95; }
           if (x > 100) { x = 100 - width; }
           if (y > 95) { y = 95 - height; }


           // Finds div with presentation-zone id, where all boxes and images will be placed
           var textBoxDiv = document.getElementById("presentation-zone");

           //position: absolute; left: x px; top: y px;

           if (textBoxDiv) {

             textBoxDiv.innerHTML +=
                 '<p style="position: absolute; left: ' + x + 'vw; top: ' + y
                     + 'vh; border: 1px solid black; margin: 0; border-radius: 5px; height: ' + height + 'vh; width: '
                     + width
                     + 'vw;">'
                     + msg + '</p>';
           }
         }, msg.c_str(), width, height, x, y
  );
}

/**
 * Converts image attributes into html
 * @param url of image source
 * @param width of image
 * @param height of images
 * @param xLoc of image
 * @param yLoc of image
 */
void WebLayout::PushImage(const std::string &url,
                          const int &width,
                          const int &height, const int &x, const int &y) {

  assert(width > 0 && height > 0); //assert width and height are positive
  assert(x > 0 && y > 0); //assert x and y are positive

  EM_ASM({
           var msg = UTF8ToString($0);
           var width = $1;
           var height = $2;
           var x = $3;
           var y = $4;

           // Don't let placement exceed 100% of view width/height or 95% height
           if (width > 100) { width = 100; }
           if (height > 95) { height = 95; }
           if (x > 100) { x = 100 - width; }
           if (y > 95) { y = 95 - height; }

           // Finds div with presentation-zone id, where all boxes and images will be placed
           var imageBoxDiv = document.getElementById("presentation-zone");
           if (imageBoxDiv) {
             imageBoxDiv.innerHTML +=
                 "<img src='" + msg + "' style='position: absolute; left: " + x + "vw; top: " + y
                     + "vh; margin: 0; object-fit: contain; width:" + width + "vw; height:" + height + "vh;' />";
           }
         }, url.c_str(), width, height, x, y
  );
}

/**
 * Loads all text boxes and images on current web layout
 */
void WebLayout::LoadPage() {
  // Display text boxes
  for (std::vector<TextBoxLayout>::iterator it = textBoxes.begin(); it != textBoxes.end(); it++) {

    // Verify values are valid
    if ((it->textBox.getHeight() > 0 && it->textBox.getWidth() > 0) && (it->x >= 0 && it->y >= 0)) {
      PushTextBox(it->textBox.getText(), it->textBox.getWidth(), it->textBox.getHeight(), it->x, it->y);
    }

  }

  // Display images
  for (std::vector<ImageLayout>::iterator it = images.begin(); it != images.end(); it++) {

    // Verify values are valid
    if ((it->image.getHeight() > 0 && it->image.getWidth() > 0) && (it->x >= 0 && it->y >= 0)) {
      PushImage(it->image.getURL(), it->image.getWidth(), it->image.getHeight(), it->x, it->y);
    }
  }
}
}
