/**
 * @file RichText.h
 * @author Grant
 *
 */

#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "IndexSet.hpp"

namespace cse {
class RichText {
 public:
  struct Format {
    std::string name;
    std::variant<std::string, int32_t, std::monostate> metadata;

    Format(std::string name,
           std::variant<std::string, int32_t, std::monostate> metadata)
        : name(std::move(name)), metadata(std::move(metadata)) {}
    Format(std::string name)
        : name(std::move(name)), metadata(std::monostate()) {}

    bool operator<(const RichText::Format& r) const {
      if (name == r.name) return metadata < r.metadata;
      return name < r.name;
    }
    bool operator==(const RichText::Format& r) const {
      return name == r.name && metadata == r.metadata;
    }
  };

 private:
  std::string text;
  std::map<Format, cse::IndexSet> formatting;

 public:
  RichText() = default;
  RichText(const RichText&) = default;
  RichText(RichText&&) = default;
  RichText& operator=(const RichText&) = default;
  RichText& operator=(RichText&&) = default;
  ~RichText() = default;

  explicit RichText(std::string text) : text(std::move(text)) {}
  explicit RichText(const char* text) : text(text) {}

  size_t size() const noexcept { return text.size(); }

  const char& char_at(size_t pos) const { return text.at(pos); }

  std::unique_ptr<std::vector<Format>> formats_at(size_t pos) const {
    auto result = std::make_unique<std::vector<Format>>();
    for (const auto& [format, index] : formatting) {
      if (index.contains(pos)) result->push_back(format);
    }
    return result;
  }

  RichText& append(const RichText& str) {
    auto left = formatting.begin();
    auto const left_end = formatting.end();
    auto right = str.formatting.begin();
    auto const right_end = str.formatting.end();
    while (left != left_end && right != right_end) {
      if (left->first == right->first) {
        left->second.appendAt(right->second, text.size());
        ++left;
        ++right;
        continue;
      }
      if (left->first < right->first) {
        ++left;
        continue;
      }

      formatting.insert({right->first, right->second})
          .first->second.offset(text.size());
      ++right;
    }
    text += str.text;
    return *this;
  }

  void applyFormatToRange(const Format& format, const size_t begin,
                          const size_t end) {
    auto [item, inserted] = formatting.insert({format, IndexSet(begin, end)});
    if (!inserted) {
      item->second.insertRange(begin, end);
    }
  }

  RichText& operator+=(const RichText& str) { return append(str); }

  std::optional<IndexSet> getFormatRange(const Format& format) const {
    auto iter = formatting.find(format);
    if (iter == formatting.end()) return {};
    return {iter->second};
  }
};

}  // namespace cse
