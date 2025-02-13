/**
* @file image.hpp
 *
 * @author Mia Bodenhorn
 */

#pragma once

#include <string>
#include <emscripten.h>

namespace cse {
/**
 * @brief A struct to represent an image
 */
class Image {
private:
    std::string url;
    int width;
    int height;
    std::string altText;

    // bool validateURL(const std::string& url) const; 

public:
    Image(const std::string& url, int width, int height, const std::string& altText = "");

  /**
  * @brief Compares two Image objects and determine if they are the same values
  * @param image to compare
  * @return true if same values
  */
    bool operator==(const Image &image) const {
       return ((image.url == url) && (image.width == width) && (image.height == height));
    }

  /** @return The url of the image */
    std::string getURL() const { return url; }
    /** @return The width of the image */
    int getWidth() const { return width; }
    /** @return The height of the image */
    int getHeight() const { return height; }
    /** @return The alternative text of the image */
    std::string getAltText() const { return altText; }

    void setURL(const std::string& newURL);
    void resize(int newWidth, int newHeight, bool maintainAspect = true);
    void updateAltText(const std::string& newAltText);

    std::string renderHTML() const;
    std::string generateJS() const;

    void injectJS() const;

    void preview() const;
};

}
