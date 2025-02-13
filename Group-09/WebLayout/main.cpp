/**
 * @file main.cpp
 * @author merry
 */

#include <iostream>
#include "WebLayout.h"

// Compile with: emcc main.cpp ../Image/Image.cpp WebLayout.cpp -o output.js --shell-file index.html
using namespace cse;

int main() {
  // Create WebLayout
  WebLayout *sampleWebLayout = new WebLayout();

  // Setup test Image
  Image *testImage = new Image(
      "https://upload.wikimedia.org/wikipedia/en/thumb/a/a7/Michigan_State_Athletics_logo.svg/640px-Michigan_State_Athletics_logo.svg.png",
      250,
      250);
  sampleWebLayout->addImage(*testImage);

  // Setup test textbox
  TextBoxConfig tbc;
  tbc.height = 50;
  tbc.width = 400;
  tbc.text = "Yay a Text Box!";
  TextBox *testTextBox = new TextBox(tbc);
  sampleWebLayout->addTextBox(*testTextBox);

  // Setup test textbox2
  TextBoxConfig tbc2;
  tbc.height = 150;
  tbc.width = 200;
  tbc.text = "Yay another Text Box!!!";
  TextBox *testTextBox2 = new TextBox(tbc);
  sampleWebLayout->addTextBox(*testTextBox2);

  // Load Page
  sampleWebLayout->LoadPage();
  WebLayout *sampleWebLayout2 = new WebLayout();
}