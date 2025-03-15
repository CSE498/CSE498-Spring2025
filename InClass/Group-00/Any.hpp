#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

namespace cse {

  class Any {
  private:
    struct ObjectBase {      
      virtual ~ObjectBase() = default;

      [[nodiscard]] virtual ObjectBase * Clone() = 0;
      [[nodiscard]] virtual std::string AsString() = 0;
    };

    template <typename T>
    struct ObjectValue : ObjectBase {
      T value;

      ObjectValue(T value) : value(value) { }
      ObjectBase * Clone() override {
        return new ObjectValue<T>(value);
      };
      std::string AsString() override {
        std::stringstream ss;
        ss << value;
        return ss.str();
      }
    };

    ObjectBase * value_ptr = nullptr;

  public:
    Any(const Any & in) {
      value_ptr = in.value_ptr->Clone();
    }
    Any(Any && in) {
      value_ptr = in.value_ptr;
      in.value_ptr = nullptr;
    }
    template <typename T>
    Any(T value) {
      value_ptr = new ObjectValue(value);
    }
    ~Any() {
      delete value_ptr;
    }
    Any & operator=(const Any & in) {
      delete value_ptr;
      value_ptr = in.value_ptr->Clone();
      std::cout << "COPY!" << std::endl;
      return *this;
    }
    Any & operator=(Any && in) {
      delete value_ptr;
      value_ptr = in.value_ptr;
      in.value_ptr = nullptr;
      std::cout << "MOVE!" << std::endl;
      return *this;
    }

    template <typename T>
    Any & operator=(T value) {
      delete value_ptr;
      value_ptr = new ObjectValue(value);
      return *this;
    }

    template <typename T>
    bool Is() {
      using derive_t = ObjectValue<T>;
      derive_t * derive_ptr = dynamic_cast<derive_t*>(value_ptr);
      return derive_ptr;
    }

    template <typename T>
    [[nodiscard]] const T & Get() const {
      using derive_t = ObjectValue<T>;
      derive_t * derive_ptr = dynamic_cast<derive_t*>(value_ptr);
      assert(derive_ptr != nullptr);
      return derive_ptr->value;
    }

    std::string AsString() const {
      return value_ptr->AsString();
    }
  };

}