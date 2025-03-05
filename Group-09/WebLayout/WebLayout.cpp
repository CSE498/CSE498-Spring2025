/**
 * @file WebLayout.cpp
 * @author Mary Holt
 *
 */

#include <iostream>
#include <cassert>
#include "WebLayout.h"

namespace cse {

// Magic Numbers
constexpr int MAX_WIDTH_PERCENT = 100;
constexpr int MAX_HEIGHT_PERCENT = 95;
constexpr int MIN_PERCENT = 0;

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
const std::vector<ImageLayout> &WebLayout::getImages() {
  return images;
}

/**
 * Gets text boxes vector of web layout
 * @return textBoxes that are connected
 */
const std::vector<TextBoxLayout> &WebLayout::getTextBoxes() {
  return textBoxes;
}

/**
 * Converts textbox attributes into html
 * @param msg text of the textbox
 * @param width width of the textbox
 * @param height height of the textbox
 */
void const WebLayout::renderTextBox(const std::string &msg,
                                    const int &width,
                                    const int &height,
                                    const int &x,
                                    const int &y) {

  assert(width >= MIN_PERCENT && height >= MIN_PERCENT); //assert width and height are positive
  assert(x >= MIN_PERCENT && y >= MIN_PERCENT); //assert x and y are positive

  EM_ASM({
           var msg = UTF8ToString($0);
           var width = $1;
           var height = $2;
           var x = $3;
           var y = $4;
           var MAX_WIDTH_PERCENT = $5;
           var MAX_HEIGHT_PERCENT = $6;

           // Calculate the ratio to view height/width (1%)
           var widthRatio = document.documentElement.clientWidth / MAX_WIDTH_PERCENT;
           var heightRatio = document.documentElement.clientHeight / MAX_WIDTH_PERCENT;

           // Don't let placement exceed 100% of view width/height
           if (width > MAX_WIDTH_PERCENT) { width = MAX_WIDTH_PERCENT; }
           if (height > MAX_HEIGHT_PERCENT) { height = MAX_HEIGHT_PERCENT; }
           if (x > MAX_WIDTH_PERCENT) { x = MAX_WIDTH_PERCENT - width; }
           if (y > MAX_HEIGHT_PERCENT) { y = MAX_HEIGHT_PERCENT - height; }


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
         }, msg.c_str(), width, height, x, y, MAX_WIDTH_PERCENT, MAX_HEIGHT_PERCENT
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
void const WebLayout::renderImage(const std::string &url,
                                  const int &width,
                                  const int &height, const int &x, const int &y) {

  assert(width >= MIN_PERCENT && height >= MIN_PERCENT); //assert width and height are positive
  assert(x >= MIN_PERCENT && y >= MIN_PERCENT); //assert x and y are positive

  EM_ASM({
           var msg = UTF8ToString($0);
           var width = $1;
           var height = $2;
           var x = $3;
           var y = $4;
           var MAX_WIDTH_PERCENT = $5;
           var MAX_HEIGHT_PERCENT = $6;

           // Don't let placement exceed 100% of view width/height or 95% height
           if (width > MAX_WIDTH_PERCENT) { width = MAX_WIDTH_PERCENT; }
           if (height > MAX_HEIGHT_PERCENT) { height = MAX_HEIGHT_PERCENT; }
           if (x > MAX_WIDTH_PERCENT) { x = MAX_WIDTH_PERCENT - width; }
           if (y > MAX_HEIGHT_PERCENT) { y = MAX_HEIGHT_PERCENT - height; }

           // Finds div with presentation-zone id, where all boxes and images will be placed
           var imageBoxDiv = document.getElementById("presentation-zone");
           if (imageBoxDiv) {
             imageBoxDiv.innerHTML +=
                 "<img src='" + msg + "' style='position: absolute; left: " + x + "vw; top: " + y
                     + "vh; margin: 0; object-fit: contain; width:" + width + "vw; height:" + height + "vh;' />";
           }
         }, url.c_str(), width, height, x, y, MAX_WIDTH_PERCENT, MAX_HEIGHT_PERCENT
  );
}

/**
 * Loads all text boxes and images on current web layout
 */
void WebLayout::loadPage() {
  // Display text boxes
  for (const auto &layout : textBoxes) {

    // Future add functionality to fully format text

    // Verify values are valid
    if ((layout.textBox->getHeight() > MIN_PERCENT && layout.textBox->getWidth() > MIN_PERCENT)
        && (layout.xPos >= MIN_PERCENT && layout.yPos >= MIN_PERCENT)) {
      renderTextBox(layout.textBox->getFormattedText().getText(),
                    layout.textBox->getWidth(),
                    layout.textBox->getHeight(),
                    layout.xPos,
                    layout.yPos);
    }

  }

  // Display images
  for (const auto &layout : images) {

    // Verify values are valid
    if ((layout.image->getHeight() > MIN_PERCENT && layout.image->getWidth() > MIN_PERCENT)
        && (layout.xPos >= MIN_PERCENT && layout.yPos >= MIN_PERCENT)) {
      renderImage(layout.image->getURL(),
                  layout.image->getWidth(),
                  layout.image->getHeight(),
                  layout.xPos,
                  layout.yPos);
    }
  }
}
}
