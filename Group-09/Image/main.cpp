/**
* @file main.cpp
 *
 * @author Mia Bodenhorn
 */

#include "image.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <emscripten.h>
#include <cstdlib>

using namespace cse;

/**
 * @brief Exposed function to inject an image directly from JavaScript
 *
 * @param url The image URL
 * @param width The image width
 * @param height The image height
 * @param altText The alt text
 */
extern "C" {
    void InjectImage(const char* url, int width, int height, const char* altText) {
        try {
            Image img(url, width, height, altText);
            img.preview();
            img.injectJS();
        } catch (const std::exception& e) {
            Alert("Image creation failed: " + std::string(e.what()));
        }
    }
}

int main() {
  EM_ASM({
    InjectImage = Module.cwrap('InjectImage', null, ['string', 'number', 'number', 'string']);
    InjectImage("https://i.pinimg.com/originals/36/82/13/368213faa3efdfeffa5da9f5b493c9e7.jpg", 700, 500, "Sparty!");
  });

  return 0;
}
