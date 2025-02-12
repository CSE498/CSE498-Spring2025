#pragma once

#include <stdexcept>
#include <string>

namespace cse {
class String : public std::string {
 public:
  String() : std::string() {}
  String(const std::string &other) : std::string(other) {}

  String &operator=(const std::string &other) {
    std::string::operator=(other);
    return *this;
  }

  char &operator[](std::size_t pos) {
#ifndef NDEBUG
    if (pos >= size()) {
      throw std::out_of_range("cse::String index out of range");
    }
#endif
    return std::string::operator[](pos);
  }

  const char &operator[](std::size_t pos) const {
#ifndef NDEBUG
    if (pos >= size()) {
      throw std::out_of_range("cse::String index out of range");
    }
#endif
    return std::string::operator[](pos);
  }
};
}  // namespace cse
