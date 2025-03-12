/**
 * @file RichText.h
 * @author Grant
 *
 */

#pragma once

#include <cstdint>
#include <format>
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "CseAssert.hpp"
#include "IndexSet.hpp"

namespace cse {

/**
 * Stores Rich Text.
 * RichText stores and manipulates formatted rich text.
 * Provides tools to represent various formats.
 * Provides tools to serialize formatted text into various formats.
 */
class RichText {
 public:
  /**
   * A format in rich text.
   * The Format struct is specialized to represent various kinds of formats in
   * rich text. Can support simple formats like: bold, italic, strikethrough.
   * Can support more complex formats with metadata like: font size, web links.
   */
  struct Format {
    /**
     * The name of the format.
     */
    std::string name;
    /**
     * The metadata associated with the format.
     * It may be an int to represent the size of the font, a string to represent
     * the target of a hyperlink, etc.
     */
    std::variant<std::string, int32_t, std::monostate> metadata;

    /**
     * Constructs a format with metadata
     * @param name The name of the format
     * @param metadata The metadata of the format
     */
    Format(std::string name,
           std::variant<std::string, int32_t, std::monostate> metadata)
        : name(std::move(name)), metadata(std::move(metadata)) {}

    /**
     * Constructs a simple format without metadata
     * @param name The name of the format
     */
    explicit(false) Format(std::string name)
        : name(std::move(name)), metadata(std::monostate()) {}

    /**
     * Compares the name first then the metadata
     * @param r right hand side
     * @return True if this is less than the right hand side
     */
    bool operator<(const RichText::Format& r) const {
      if (name == r.name) return metadata < r.metadata;
      return name < r.name;
    }

    /**
     * Compares the name and the metadata
     * @param r right hand side
     * @return True if equivalent
     */
    bool operator==(const RichText::Format& r) const {
      return name == r.name && metadata == r.metadata;
    }
  };

 private:
  std::string m_text;
  std::map<Format, cse::IndexSet> m_formatting;

 public:
  RichText() = default;
  RichText(const RichText&) = default;
  RichText(RichText&&) = default;
  RichText& operator=(const RichText&) = default;
  RichText& operator=(RichText&&) = default;
  ~RichText() = default;

  explicit RichText(std::string text) : m_text(std::move(text)) {}
  explicit RichText(const char* text) : m_text(text) {}

  [[nodiscard]] size_t size() const noexcept { return m_text.size(); }

  [[nodiscard]] const char& char_at(size_t pos) const { return m_text.at(pos); }

  [[nodiscard]] std::string to_string() const { return m_text; }

  [[nodiscard]] std::vector<Format> formats_at(size_t pos) const {
    dbg_assert(pos < m_text.size(),
               std::format("Out of bounds access, idx: {} size: {}", pos,
                           m_text.size()));
    std::vector<Format> result;
    for (const auto& [format, index] : m_formatting) {
      if (index.contains(pos)) result.push_back(format);
    }
    return result;
  }

  RichText& append(const RichText& str) {
    auto left = m_formatting.begin();
    auto const left_end = m_formatting.end();
    auto right = str.m_formatting.begin();
    auto const right_end = str.m_formatting.end();
    while (left != left_end && right != right_end) {
      if (left->first == right->first) {
        left->second.append_at(right->second, m_text.size());
        ++left;
        ++right;
        continue;
      }
      if (left->first < right->first) {
        ++left;
        continue;
      }

      m_formatting.insert({right->first, right->second})
          .first->second.offset(m_text.size());
      ++right;
    }
    while (right != right_end) {
      m_formatting.insert({right->first, right->second})
          .first->second.offset(m_text.size());
      ++right;
    }
    m_text += str.m_text;
    return *this;
  }

  void apply_format_to_range(const Format& format, const size_t begin,
                             const size_t end) {
    dbg_assert(
        end >= begin,
        std::format("Format range ends after beginning, begin: {}, end: {}",
                    begin, end));

    auto [item, inserted] = m_formatting.insert({format, IndexSet(begin, end)});
    if (!inserted) {
      item->second.insert_range(begin, end);
    }
  }

  RichText& operator+=(const RichText& str) { return append(str); }

  [[nodiscard]] std::optional<IndexSet> get_format_range(const Format& format) const {
    const auto iter = m_formatting.find(format);
    if (iter == m_formatting.end()) return {};
    return {iter->second};
  }
};

}  // namespace cse
