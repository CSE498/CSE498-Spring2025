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
        EM_ASM_({
            var img = document.createElement('img');
            img.src = UTF8ToString($0);
            img.width = $1;
            img.height = $2;
            img.alt = UTF8ToString($3);
            document.body.appendChild(img);
        }, url, width, height, altText);
    }
}

int main() {
    EM_ASM({
        InjectImage = Module.cwrap('InjectImage', null, ['string', 'number', 'number', 'string']);
        InjectImage("https://i.pinimg.com/originals/36/82/13/368213faa3efdfeffa5da9f5b493c9e7.jpg", 700, 500, "Sparty!");
    });

    return 0;
}