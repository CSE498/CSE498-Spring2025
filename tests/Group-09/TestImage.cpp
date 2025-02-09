/**
* @file TestImage.cpp
 *
 * @author Mia Bodenhorn
 */

#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-09/Image/image.hpp"

using namespace cse;

TEST_CASE("Valid Image", "[Image]") {
 Image img("https://cse498.github.io/assets/img/logo.png", 400, 300, "Test Image");

 CHECK(img.getURL() == "https://cse498.github.io/assets/img/logo.png");
 CHECK(img.getWidth() == 400);
 CHECK(img.getHeight() == 300);
 CHECK(img.getAltText() == "Test Image");
}