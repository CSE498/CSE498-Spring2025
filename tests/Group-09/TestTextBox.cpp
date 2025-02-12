#include "../../Group-09/TextBox/TextBox.hpp"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

using namespace cse;

TEST_CASE("Textbox default state", "[TextBox]") {
  TextBox tb;

  CHECK(tb.getFormattedText().getText() == "");
  CHECK(tb.getWidth() == 0);
  CHECK(tb.getHeight() == 0);
}

TEST_CASE("TextBox get and set text", "[TextBox]") {
  TextBox tb;
  FormattedText ft;
  ft.setText("Hello, World!");
  tb.setFormattedText(ft);

  CHECK(tb.getFormattedText().getText() == "Hello, World!");
}

TEST_CASE("TextBox resizing", "[TextBox]") {
  TextBox tb;

  tb.resize(200, 100);
  CHECK(tb.getWidth() == 200);
  CHECK(tb.getHeight() == 100);
}

TEST_CASE("TextBox auto-generates ID when empty", "[TextBox]") {
  TextBoxConfig config;
  TextBox tb("", config);  // No ID provided → auto-generated

  std::string id = tb.getID();
  REQUIRE(id.find("textbox-") == 0);  // ID should start with "textbox-"
}

TEST_CASE("TextBox uses manual ID", "[TextBox]") {
  TextBoxConfig config;
  TextBox tb("custom-box-42", config);

  CHECK(tb.getID() == "custom-box-42");
}

TEST_CASE("TextBox configuration", "[TextBox]") {
  // Create a FormattedText object to use in the configuration.
  FormattedText ft;
  ft.setText("Configured text");

  // Create a configuration for the TextBox.
  TextBoxConfig config = {ft, 300, 150};

  // Construct the TextBox using the configuration and a manual ID.
  TextBox tb("configured-box", config);

  // Verify that the TextBox has been initialized with the config values and
  // manual ID.
  CHECK(tb.getID() == "configured-box");
  CHECK(tb.getFormattedText() == ft);
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
  FormattedText ft;
  ft.setText("");
  tb.setFormattedText(ft);

  CHECK(tb.getFormattedText().getText() == "");

  ft.setText("   ");
  // Should trim whitespace, so we expect an empty string.
  CHECK(tb.getFormattedText().getText() == "");
}

TEST_CASE("TextBox clear text", "[TextBox]") {
  TextBox tb;
  FormattedText ft;
  ft.setText("Some text");
  tb.setFormattedText(ft);

  tb.clearText();
  CHECK(tb.getFormattedText().getText() == "");
}

TEST_CASE("TextBox append text", "[TextBox]") {
  TextBox tb;
  FormattedText ft;
  ft.setText("Hello");
  tb.setFormattedText(ft);

  tb.appendText(", World!");
  CHECK(tb.getFormattedText().getText() == "Hello, World!");
}

TEST_CASE("TextBox copy constructor", "[TextBox]") {
  TextBox tb;
  FormattedText ft;
  ft.setText("Copy me");
  tb.setFormattedText(ft);

  TextBox tbCopy(tb);  // Calls copy constructor

  // Check that copied text is the same
  CHECK(tbCopy.getFormattedText().getText() == "Copy me");

  // Check that modifying tbCopy does NOT affect the original
  tbCopy.appendText("!!!");
  CHECK(tbCopy.getFormattedText().getText() == "Copy me!!!");
  CHECK(tb.getFormattedText().getText() == "Copy me");  // Original unchanged
}

TEST_CASE("TextBox move constructor", "[TextBox]") {
  TextBox tb;
  FormattedText ft;
  ft.setText("Move me");
  tb.setFormattedText(ft);

  // Move construct a new TextBox from tb.
  TextBox tbMoved(std::move(tb));

  // Check if move constructor transfers ownership correctly.
  CHECK(tbMoved.getFormattedText().getText() == "Move me");
  CHECK(tb.getFormattedText().getText() ==
        "");  // Check if move leaves the original empty.
}
