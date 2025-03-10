#include <format>

#include "catch.hpp"

// Mocks
namespace cse {
template <typename T>
class RichText;
template <typename T>
class TextSerializer;
template <typename T>
class OutputBackend;
}  // namespace cse

using RichString = cse::RichText<std::string>;

// Example of what a backend would look like
template <typename T>
class HtmlBackend : cse::OutputBackend<T> {
 public:
  // TODO: should metadata be optional for properties like Bold?
  T Bold(T const &src) override {
    return std::format("<strong>{}</strong>", src);
  }

  T Italic(T const &src) override { return std::format("<em>{}</em>", src); }

  // color string automatically extracted from metadata variant
  T Color(T const &src, std::string const &color) override {
    return std::format("<span class={}>{}</span>", color, src);
  }
};

TEST_CASE("TextSerializer", "[TextSerializer]") {
  RichString::Format bold("bold");
  RichString text{"hello"};
  text.apply_to_range(bold, 0, text.size() - 1);

  HtmlBackend<std::string> html;
  cse::TextSerializer<std::string> serializer{&html};

  std::string output = serializer.serialize();
  REQUIRE(output == "<strong>hello</strong>");
}

TEST_CASE("TextSerializer header and footer", "[TextSerializer]") {
  std::string header = R"(
<style>
.red {
  color: #ff0000
}
.blue{
  color: #0000ff
}
</style>
<body>)";

  std::string footer = "\n</body>";

  RichString::Format red("color", "red");
  RichString::Format blue("color", "blue");

  RichString text{"hello world"};
  text.apply_format_to_range(red, 0, 4);
  text.apply_format_to_range(blue, 6, text.size() - 1);

  HtmlBackend<std::string> html;
  cse::TextSerializer<std::string> serializer{&html, header, footer};

  std::string output = serializer.serialize(text);

  REQUIRE(output ==
          (header +
           "<span class=red>hello</span> <span class=blue>world</span>" +
           footer));
}
