/**
 * @file WebLayout.cpp
 * @author Mary Holt
 *
 */

#include <iostream>
#include "WebLayout.h"

/**
 * Adds an image to the web layout
 * @param image to be added
 */
void WebLayout::addImage(const Image &image) {
  images.push_back(image);
}

/**
 * Removes a specific image from the web layout
 * @param image to be removed
 */
void WebLayout::removeImage(const Image &image) {
  images.erase(std::remove(images.begin(), images.end(), image));
}

/**
 * Adds a textbox to the web layout
 * @param textBox to be added
 */
void WebLayout::addTextBox(const TextBox &textBox) {
  textBoxes.push_back(textBox);
}

/**
 * Removes a textbox from the web layout
 * @param textBox to be removed
 */
void WebLayout::removeTextBox(const TextBox &textBox) {
  textBoxes.erase(std::remove(textBoxes.begin(), textBoxes.end(), textBox));
}

/**
 * Converts textbox attributes into html
 * @param msg text of the textbox
 * @param width width of the textbox
 * @param height height of the textbox
 */
void WebLayout::PushTextBox(const std::string &msg, const int &width, const int &height) {
  EM_ASM({
             var msg = UTF8ToString($0);
      var width = $1;
      var height = $2;
      // Finds div with presentation-zone id, where all boxes and images will be placed
      var textBoxDiv = document.getElementById("presentation-zone");
      if (textBoxDiv)
      {
        textBoxDiv.innerHTML +=
            '<p style="border: 1px solid black; border-radius: 5px; height: ' + height + 'px; width: ' + width + 'px;">'
                + msg + '</p>';
      }
         }, msg.c_str(), width, height
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
                          const int &height,
                          const int &xLoc,
                          const int &yLoc) {
  EM_ASM({
             var msg = UTF8ToString($0);
      var width = $1;
      var height = $2;
      var xLoc = $3;
      var yLoc = $4;
      // Finds div with presentation-zone id, where all boxes and images will be placed
      var imageBoxDiv = document.getElementById("presentation-zone");
      if (imageBoxDiv)
      {
        imageBoxDiv.innerHTML +=
            "<img src='" + msg + "' style='object-fit: fill; width:" + width + "px; height:" + height + "; left: "
                + xLoc + "px; top: " + yLoc + "px;' />";
      }
         }, url.c_str(), width, height, xLoc, yLoc
  );
}

/**
 * Loads all text boxes and images on current web layout
 */
void WebLayout::LoadPage() {
  // Display text boxes
  for (std::vector<TextBox>::iterator it = textBoxes.begin(); it != textBoxes.end(); it++) {
    PushTextBox(it->text, it->width, it->height);
  }

  // Display images
  for (std::vector<Image>::iterator it = images.begin(); it != images.end(); it++) {
    PushImage(it->url, it->width, it->height, it->xLoc, it->yLoc);
  }
}
