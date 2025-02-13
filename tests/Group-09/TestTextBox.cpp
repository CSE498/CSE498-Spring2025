#include "../../Group-09/TextBox/TextBox.hpp"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

using namespace cse;

TEST_CASE("Textbox default state", "[TextBox]") {
  TextBox tb;

  CHECK(tb.getText() == "");
  CHECK(tb.getWidth() == 0);
  CHECK(tb.getHeight() == 0);
}

TEST_CASE("Textbox get and set text", "[TextBox]") {
  TextBox tb;
  tb.setText("Hello, World!");

  CHECK(tb.getText() == "Hello, World!");
}

TEST_CASE("TextBox resizing", "[TextBox]") {
  TextBox tb;

  tb.resize(200, 100);
  CHECK(tb.getWidth() == 200);
  CHECK(tb.getHeight() == 100);
}

TEST_CASE("TextBox configuration", "[TextBox]") {
  // Create a configuration for the TextBox.
  TextBoxConfig config = {"Configured text", 300, 150};

  // Construct the TextBox using the configuration.
  TextBox tb(config);

  // Verify that the TextBox has been initialized with the config values.
  CHECK(tb.getText() == "Configured text");
  CHECK(tb.getWidth() == 300);
  CHECK(tb.getHeight() == 150);
}

TEST_CASE("TextBox resizing with negative values", "[TextBox]") {
  TextBox tb;
  // Our design will clamp to zero for negatives inputs.
  tb.resize(-50, -100);
  CHECK(tb.getWidth() == 0);
  CHECK(tb.getHeight() == 0);
}

TEST_CASE("TextBox handles empty and whitespace text", "[TextBox]") {
  TextBox tb;
  tb.setText("");
  CHECK(tb.getText() == "");

  tb.setText("   ");
  // If we decide to trim whitespace, test "" instead.
  CHECK(tb.getText() == "   ");  // Assuming we don't trim whitespace.
}

TEST_CASE("TextBox clear text", "[TextBox]") {
  TextBox tb;
  tb.setText("Some text");
  tb.clearText();
  CHECK(tb.getText() == "");
}

TEST_CASE("TextBox append text", "[TextBox]") {
  TextBox tb;
  tb.setText("Hello");
  tb.appendText(", World!");
  CHECK(tb.getText() == "Hello, World!");
}

TEST_CASE("TextBox copy constructor", "[TextBox]") {
  TextBox tb;
  tb.setText("Copy me");
  TextBox tbCopy(tb);
  // Check if copy constructor creates an independent copy.
  CHECK(tbCopy.getText() == "Copy me");
}

TEST_CASE("TextBox move constructor", "[TextBox]") {
  TextBox tb;
  tb.setText("Move me");
  TextBox tbMoved(std::move(tb));
  // Check if move constructor transfers ownership correctly.
  CHECK(tbMoved.getText() == "Move me");
  CHECK(tb.getText() == "");  // Check if move leaves the original empty.
}
