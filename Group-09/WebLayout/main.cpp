/**
 * @file main.cpp
 * @author merry
 */

#include <emscripten.h>
#include <iostream>
#include "WebLayout.h"

// Compile with: emcc main.cpp WebLayout.cpp -o output.js --shell-file index.html

int main() {
  // Create WebLayout
  WebLayout *sampleWebLayout = new WebLayout();

  // Setup test Image
  Image *testImage = new Image();
  testImage->xLoc = 500;
  testImage->yLoc = 300;
  testImage->height = 250;
  testImage->width = 250;
  testImage->url =
      "https://upload.wikimedia.org/wikipedia/en/thumb/a/a7/Michigan_State_Athletics_logo.svg/640px-Michigan_State_Athletics_logo.svg.png";
  sampleWebLayout->addImage(*testImage);

  // Setup test textbox
  TextBox *testTextBox = new TextBox();
  testTextBox->height = 50;
  testTextBox->width = 400;
  testTextBox->text = "Yay a Text Box";
  sampleWebLayout->addTextBox(*testTextBox);

  // Setup test textbox2
  TextBox *testTextBox2 = new TextBox();
  testTextBox2->height = 150;
  testTextBox2->width = 200;
  testTextBox2->text = "Yay another Text Box";
  sampleWebLayout->addTextBox(*testTextBox2);

  // Load Page
  sampleWebLayout->LoadPage();
  WebLayout *sampleWebLayout2 = new WebLayout();
}