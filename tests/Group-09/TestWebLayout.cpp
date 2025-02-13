/**
 * @file TestWebLayout.cpp]
 *
 * @author Mary Holt
 *
 * Compile with: emcc TestWebLayout.cpp ../../Group-09/Image/Image.cpp ../../Group-09/WebLayout/WebLayout.cpp -o TestWebLayout.html
 */

#include <iostream>
#include "../../Group-09/WebLayout/WebLayout.h"

using namespace cse;

void testCase1() {
  // Default constructor test
  std::cout << "Beginning Test Case 1 (Default)\n";

  WebLayout wb;

  if (wb.getImages().size() != 0) { std::cout << "Image Innit Fail\n"; }
  if (wb.getTextBoxes().size() != 0) { std::cout << "Text Boxes Init Fail\n"; }

  std::cout << "Successful Test Case 1\n";
}

void testCase2() {
  // Test Adding
  std::cout << "Beginning Test Case 2 (Add)\n";

  WebLayout wb;
  Image i("https://msu_logo.png", 50, 50);

  wb.addImage(i);

  //Recheck size of images vector
  if (wb.getImages().size() != 1) { std::cout << "Image adding failure\n"; }

  //Check saved correctly
  if (wb.getImages().at(0).getURL() != "https://msu_logo.png") { std::cout << "Image adding failure\n"; }
  if (wb.getImages().at(0).getWidth() != 50) { std::cout << "Image adding failure\n"; }
  if (wb.getImages().at(0).getHeight() != 50) { std::cout << "Image adding failure\n"; }

  TextBoxConfig tbc;
  tbc.text = "CSE498";
  tbc.height = 100;
  tbc.width = 100;
  TextBox tb(tbc);
  wb.addTextBox(tb);

  //Recheck size of text boxes vector
  if (wb.getTextBoxes().size() != 1) { std::cout << "Text box adding failure\n"; }

  //Check saved correctly
  if (wb.getTextBoxes().at(0).getText() != "CSE498") { std::cout << "Text box adding failure\n"; }

  std::cout << "Successful Test Case 2\n";

}

void testCase3() {
  // Test Removing
  std::cout << "Beginning Test Case 3 (Valid Remove)\n";

  WebLayout wb;
  Image i("https://msu_logo.png", 50, 50);
  wb.addImage(i);

  //Check size of images vector
  if (wb.getImages().size() != 1) { std::cout << "Image adding failure\n"; }

  wb.removeImage(i);
  //Check size of images vector
  if (wb.getImages().size() != 0) { std::cout << "Image removing failure\n"; }

  TextBoxConfig tbc;
  tbc.text = "CSE498";
  tbc.height = 100;
  tbc.width = 100;
  TextBox tb(tbc);
  wb.addTextBox(tb);

  //Recheck size of text boxes vector
  if (wb.getTextBoxes().size() != 1) { std::cout << "Text box adding failure\n"; }

  wb.removeTextBox(tb);

  //Recheck size of text boxes vector
  if (wb.getTextBoxes().size() != 0) { std::cout << "Text box removing failure\n"; }

  std::cout << "Successful Test Case 3\n";
}

void testCase4() {
  // Invalid Remove
  std::cout << "Beginning Test Case 4 (Invalid Remove)\n";

  WebLayout wb;
  Image i("https://msu_logo.png", 100, 100);
  wb.addImage(i);

  //Check size of images vector
  if (wb.getImages().size() != 1) { std::cout << "Image adding failure\n"; }

  Image ii("https://msu_logo_but_bigger.png", 150, 150);
  wb.removeImage(ii);
  //Check size of images vector
  if (wb.getImages().size() != 1) { std::cout << "Image Invalid Removal failure\n"; }

  TextBoxConfig tbc;
  tbc.text = "CSE498";
  tbc.height = 100;
  tbc.width = 100;
  TextBox tb(tbc);
  wb.addTextBox(tb);

  //Recheck size of text boxes vector
  if (wb.getTextBoxes().size() != 1) { std::cout << "Text box adding failure\n"; }

  TextBoxConfig tbc2;
  tbc2.text = "CSE498-Capstone";
  tbc2.height = 200;
  tbc2.width = 200;
  TextBox tbb(tbc2);
  wb.removeTextBox(tbb);
  //Check size of text boxes vector
  if (wb.getTextBoxes().size() != 1) { std::cout << "Text box Invalid Removal failure\n"; }

  std::cout << "Successful Test Case 4\n";
}

int main() {

  testCase1();
  testCase2();
  testCase3();
  testCase4();

  return 0;
}
