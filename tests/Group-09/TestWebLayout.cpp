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
  ImageLayout il(i, 10, 10);
  wb.addImage(il);

  //Recheck size of images vector
  if (wb.getImages().size() != 1) { std::cout << "Image adding failure\n"; }

  //Check saved correctly
  if (wb.getImages().at(0).image.getURL() != "https://msu_logo.png") { std::cout << "Image adding failure\n"; }
  if (wb.getImages().at(0).image.getWidth() != 50) { std::cout << "Image adding failure\n"; }
  if (wb.getImages().at(0).image.getHeight() != 50) { std::cout << "Image adding failure\n"; }
  if (wb.getImages().at(0).x != 10) { std::cout << "Image adding failure\n"; }
  if (wb.getImages().at(0).y != 10) { std::cout << "Image adding failure\n"; }

  TextBoxConfig tbc;
  tbc.text = "CSE498";
  tbc.height = 100;
  tbc.width = 100;
  TextBox tb(tbc);
  TextBoxLayout tbl(tb, 12, 12);
  wb.addTextBox(tbl);

  //Recheck size of text boxes vector
  if (wb.getTextBoxes().size() != 1) { std::cout << "Text box adding failure\n"; }

  //Check saved correctly
  if (wb.getTextBoxes().at(0).textBox.getText() != "CSE498") { std::cout << "Text box adding failure\n"; }
  if (wb.getTextBoxes().at(0).textBox.getWidth() != 100) { std::cout << "Text box adding failure\n"; }
  if (wb.getTextBoxes().at(0).textBox.getHeight() != 100) { std::cout << "Text box adding failure\n"; }
  if (wb.getTextBoxes().at(0).x != 12) { std::cout << "Text box adding failure\n"; }
  if (wb.getTextBoxes().at(0).y != 12) { std::cout << "Text box adding failure\n"; }

  std::cout << "Successful Test Case 2\n";
}

void testCase3() {
  // Test Removing
  std::cout << "Beginning Test Case 3 (Valid Remove)\n";

  WebLayout wb;
  Image i("https://msu_logo.png", 50, 50);
  ImageLayout il(i, 10, 10);
  wb.addImage(il);

  //Check size of images vector
  if (wb.getImages().size() != 1) { std::cout << "Image adding failure\n"; }

  wb.removeImage(il);
  //Check size of images vector
  if (wb.getImages().size() != 0) { std::cout << "Image removing failure\n"; }

  TextBoxConfig tbc;
  tbc.text = "CSE498";
  tbc.height = 100;
  tbc.width = 100;
  TextBox tb(tbc);
  TextBoxLayout tbl(tb, 12, 12);
  wb.addTextBox(tbl);

  //Recheck size of text boxes vector
  if (wb.getTextBoxes().size() != 1) { std::cout << "Text box adding failure\n"; }

  wb.removeTextBox(tbl);

  //Recheck size of text boxes vector
  if (wb.getTextBoxes().size() != 0) { std::cout << "Text box removing failure\n"; }

  std::cout << "Successful Test Case 3\n";
}

void testCase4() {
  // Invalid Remove
  std::cout << "Beginning Test Case 4 (Invalid Remove)\n";

  WebLayout wb;
  Image i("https://msu_logo.png", 50, 50);
  ImageLayout il(i, 10, 10);
  wb.addImage(il);

  //Check size of images vector
  if (wb.getImages().size() != 1) { std::cout << "Image adding failure\n"; }

  Image ii("https://msu_logo_but_bigger.png", 150, 150);
  ImageLayout iil(ii, 10, 10);
  wb.removeImage(iil);
  //Check size of images vector
  if (wb.getImages().size() != 1) { std::cout << "Image Invalid Removal failure\n"; }

  TextBoxConfig tbc;
  tbc.text = "CSE498";
  tbc.height = 100;
  tbc.width = 100;
  TextBox tb(tbc);
  TextBoxLayout tbl(tb, 12, 12);
  wb.addTextBox(tbl);

  //Recheck size of text boxes vector
  if (wb.getTextBoxes().size() != 1) { std::cout << "Text box adding failure\n"; }

  TextBoxConfig tbc2;
  tbc2.text = "CSE498-Capstone";
  tbc2.height = 200;
  tbc2.width = 200;
  TextBox tbb(tbc2);
  TextBoxLayout tbl2(tbb, 14, 14);
  wb.removeTextBox(tbl2);
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
