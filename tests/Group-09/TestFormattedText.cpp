#include "../../Group-09/TextBox/FormattedText.cpp"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

using namespace cse;

TEST_CASE("FormattedText default state", "[FormattedText]") {
  FormattedText ft;
  // By default, the text should be empty and the type should be Raw.
  CHECK(ft.getText() == "");
  CHECK(ft.getType() == FormattedText::TextType::Raw);
}

TEST_CASE("FormattedText constructor initializes correctly",
          "[FormattedText]") {
  // When initialized with specific text and type, they should be stored
  // correctly.
  FormattedText ft("Hello, world!", FormattedText::TextType::HTML);
  CHECK(ft.getText() == "Hello, world!");
  CHECK(ft.getType() == FormattedText::TextType::HTML);
}

TEST_CASE("FormattedText setting raw text", "[FormattedText]") {
  FormattedText ft;
  ft.setText("Plain text");
  ft.setType(FormattedText::TextType::Raw);
  CHECK(ft.getText() == "Plain text");
  CHECK(ft.getType() == FormattedText::TextType::Raw);
}

TEST_CASE("FormattedText setting HTML text", "[FormattedText]") {
  FormattedText ft;
  ft.setText("<b>Bold</b>");
  ft.setType(FormattedText::TextType::HTML);
  // For HTML text, we do not want to escape the tags. Text should be returned
  // as-is.
  CHECK(ft.getText() == "<b>Bold</b>");
  CHECK(ft.getType() == FormattedText::TextType::HTML);
}

TEST_CASE("FormattedText escapes special characters in raw text",
          "[FormattedText]") {
  FormattedText ft;
  ft.setText("5 < 10 & 20 > 15");
  ft.setType(FormattedText::TextType::Raw);
  // We expect that for raw text, special characters are escaped.
  // For example, "<" becomes "&lt;", "&" becomes "&amp;", and ">" becomes
  // "&gt;".
  CHECK(ft.getEscapedText() == "5 &lt; 10 &amp; 20 &gt; 15");
}

TEST_CASE("FormattedText preserves special characters in HTML text",
          "[FormattedText]") {
  FormattedText ft;
  ft.setText("5 < 10 & 20 > 15");
  ft.setType(FormattedText::TextType::HTML);
  // When the type is HTML, the content should be returned unmodified
  // (or processed as HTML rather than escaped).
  CHECK(ft.getFormattedOutput() == "5 < 10 & 20 > 15");
}

TEST_CASE("FormattedText identifies and formats bold HTML tag",
          "[FormattedText]") {
  FormattedText ft;
  ft.setText("Normal <b>Bold</b> Normal");
  ft.setType(FormattedText::TextType::HTML);
  // The <b> tag is preserved.
  CHECK(ft.getFormattedOutput() == "Normal <b>Bold</b> Normal");
}

TEST_CASE("FormattedText preserves italic HTML tag in HTML mode",
          "[FormattedText]") {
  FormattedText ft;
  ft.setText("Normal <i>Italic</i> Normal");
  ft.setType(FormattedText::TextType::HTML);
  // The <i> tag is preserved.
  CHECK(ft.getFormattedOutput() == "Normal <i>Italic</i> Normal");
}

TEST_CASE("FormattedText preserves nested HTML formatting in HTML mode",
          "[FormattedText]") {
  FormattedText ft;
  ft.setText("Start <b>Bold and <i>Italic</i></b> End");
  ft.setType(FormattedText::TextType::HTML);
  // Nested HTML is preserved without conversion.
  CHECK(ft.getFormattedOutput() == "Start <b>Bold and <i>Italic</i></b> End");
}
