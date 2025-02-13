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
};

class FileSerializable {
protected:
  virtual std::string GetTypeName() const = 0;
  virtual std::string GetId() const = 0;
  virtual void SetId(std::string) = 0;
  virtual std::map<std::string, SerializableProperty> GetPropertyMap() = 0;

public:
  virtual ~FileSerializable() = default;

  void FromFile(std::istream &f, size_t prefix_size) {
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
        throw std::runtime_error("Unknown property: " + key);
      }
      it->second.handler(value);
    }
  }

  void ToFile(std::ostream &s, std::string const &prefix) {
    s << prefix << GetTypeName() << ":" << GetId() << "\n";
    auto p = prefix + prefix;

    for (auto const &[key, property] : GetPropertyMap()) {
      s << p << key << ":";
      property.writer(s);
      s << "\n";
    }
  }
};
