#pragma once
#include <assert.h>
#include <functional>
#include <iostream>
#include <istream>
#include <map>
#include <string>
#include <utility>

class FileUtil {
public:
  static std::string GetKey(std::istream &fs) {
    std::string line;
    FileUtil::PeekLine(fs, line);
    auto [key, value] = FileUtil::SeparateKeyValue(line);
    return key;
  }

  // TODO @lspecht: Handle edge case where there is an extra indentation level
  static bool CheckPrefixSize(std::istream &fs, size_t prefix_size) {
    std::string line;
    FileUtil::PeekLine(fs, line);
    auto it = std::find_if(line.begin(), line.end(), [](unsigned char ch) { return !std::isspace(ch); });
    return (static_cast<size_t>((it - line.begin())) == prefix_size);
  }

  static std::vector<std::pair<std::string, std::string>> GetProperties(std::istream &fs, size_t prefix_size) {
    std::vector<std::pair<std::string, std::string>> res;
    while (FileUtil::CheckPrefixSize(fs, prefix_size)) {
      std::string line;
      std::getline(fs, line);
      res.push_back(FileUtil::SeparateKeyValue(line));
    }
    return res;
  }

  static void PeekLine(std::istream &fs, std::string &l) {
    int len = fs.tellg();
    std::getline(fs, l);
    // Return buffer
    fs.seekg(len, std::ios_base::beg);
  };

  static void Trim(std::string &line) {
    line.erase(line.begin(),
               std::find_if(line.begin(), line.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
               line.end());
  }

  static std::pair<std::string, std::string> SeparateKeyValue(std::string line) {
    // Trim leading and trailing spaces
    FileUtil::Trim(line);

    // Find the first occurrence of ':'
    size_t pos = line.find(':');
    assert(pos != std::string::npos);

    // Split the string into key and value
    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);
    return std::make_pair(key, value);
  }
};

// Property handler function type
using PropertyHandler = std::function<void(const std::string &)>;
using PropertyWriter = std::function<void(std::ostream &)>;

struct SerializableProperty {
  PropertyHandler handler;
  PropertyWriter writer;

  SerializableProperty() = delete;
  ~SerializableProperty() {};
  SerializableProperty(std::function<void(std::ostream &)> w, std::function<void(const std::string &)> h)
      : handler(h), writer(w) {}
  SerializableProperty(std::function<void(const std::string &)> h, std::function<void(std::ostream &)> w)
      : handler(h), writer(w) {}
};

/**
 * There was some use of AI to write the types and maps
 * that map properties to handlers
 */
class FileSerializable {
protected:
  virtual std::string GetTypeName() const = 0;
  virtual std::string GetId() const = 0;
  virtual void SetId(std::string) = 0;
  virtual std::map<std::string, SerializableProperty> GetPropertyMap() = 0;

  static std::string GetIndent(size_t level, std::string const &indent_unit = "    ") {
    std::string result;
    for (size_t i = 0; i < level; ++i) {
      result += indent_unit;
    }
    return result;
  }

public:
  virtual ~FileSerializable() = default;

  virtual void FromFile(std::istream &f, size_t prefix_size) {
    std::string line;
    std::getline(f, line);
    auto [key, value] = FileUtil::SeparateKeyValue(line);
    if (key != GetTypeName()) {
      throw std::runtime_error("Invalid type: " + key);
    }
    SetId(value);

    auto properties = FileUtil::GetProperties(f, prefix_size + 2);
    auto propertyMap = GetPropertyMap();

    for (auto [key, value] : properties) {
      auto it = propertyMap.find(key);
      if (it == propertyMap.end()) {
        throw std::runtime_error("Unknown property on " + GetTypeName() + ": " + key);
      }
      it->second.handler(value);
    }
  }

  void ToFile(std::ostream &s, size_t indent_level = 0, std::string const &indent_unit = "  ") {
    std::string indent = GetIndent(indent_level, indent_unit);
    s << indent << GetTypeName() << ":" << GetId() << "\n";

    auto property_indent = GetIndent(indent_level + 1, indent_unit);
    for (auto const &[key, property] : GetPropertyMap()) {
      s << property_indent << key << ":";
      property.writer(s);
      s << "\n";
    }
  }
};
