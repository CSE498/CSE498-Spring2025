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
      25,
      25);
  ImageLayout il(*testImage, 20, 30);
  sampleWebLayout->addImage(il);

  // Setup test textbox
  TextBoxConfig tbc;
  tbc.height = 10;
  tbc.width = 45;
  tbc.text = "Yay a Text Box!";
  TextBox *testTextBox = new TextBox(tbc);
  TextBoxLayout tbl(*testTextBox, 40, 30);
  sampleWebLayout->addTextBox(tbl);

  // Setup test textbox2 (exceed barriers test)
  TextBoxConfig tbc2;
  tbc2.height = 15;
  tbc2.width = 20;
  tbc2.text = "Yay another Text Box!!!";
  TextBox *testTextBox2 = new TextBox(tbc2);
  TextBoxLayout tbl2(*testTextBox2, 500, 500);
  sampleWebLayout->addTextBox(tbl2);

  // Load Page
  sampleWebLayout->LoadPage();
}