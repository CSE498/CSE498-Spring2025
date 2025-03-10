/**
 * @file Datum.cpp
 *
 * @author Max Krawec
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "Datum.h"

namespace cse {

/// Epsilon used to compare doubles
static constexpr double kEpsilon = 0.0001;

/// Used to remove trailing zeros
static constexpr char kTrailingZero = '0';

/// Used to remove decimal point
static constexpr char kDecimalPoint = '.';

/**
 * Returns the string value of the Datum.
 * @return The string value of the Datum
 */
std::string Datum::GetString() const {
  if (!IsString()) {
    // CITE: Used https://www.geeksforgeeks.org/how-to-throw-an-exception-in-cpp/
    // to help with throwing an error.
    throw std::runtime_error("Attempted GetString() on a non-string Datum.");
  }

  assert(IsString());
  return std::get<std::string>(GetVariant());
}

/**
 * Returns the double value of the Datum.
 * @return The double value of the Datum
 */
double Datum::GetDouble() const {
  if (!IsDouble()) {
    throw std::runtime_error("Attempted GetDouble() on a non-double Datum.");
  }

  assert(IsDouble());
  return std::get<double>(GetVariant());
}

/**
 * Converts the Datum into a string.
 */
[[maybe_unused]] void Datum::AsString() {
  if (IsDouble()) {
    assert(IsDouble());
    if (!std::isnan(GetDouble())) {
      assert(!std::isnan(GetDouble()));
      std::string string_numeric_value = std::to_string(GetDouble());

      // CITE: https://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros.
      // Used the above link to help remove trailing 0s and . when a double converts into a string.
      string_numeric_value.erase(string_numeric_value.find_last_not_of(kTrailingZero) + 1,
                                 std::string::npos);
      string_numeric_value.erase(string_numeric_value.find_last_not_of(kDecimalPoint) + 1,
                                 std::string::npos);
      value_ = string_numeric_value;
    } else {
      assert(std::isnan(GetDouble()));
      value_ = "";
    }
  }
}

/**
 * Converts the Datum into a double.
 * @warning If the Datum is an invalid double, converts into NaN.
 */
[[maybe_unused]] void Datum::AsDouble() {
  if (IsString()) {
    assert(IsString());
    try {

      // CITE: Used ChatGPT to write this code. Fixed a bug where strings starting with
      // numbers (e.g., "123Hello") were partially converted instead of setting to NaN.
      std::size_t pos;
      double double_value = std::stod(GetString(), &pos);
      if (pos == GetString().length()) {
        assert(pos == GetString().length());
        value_ = double_value;
      } else {
        // CITE: Used https://stackoverflow.com/questions/16691207/c-c-nan-constant-literal for NaN
        value_ = std::numeric_limits<double>::quiet_NaN();
      }
    } catch (std::invalid_argument &e) {
      value_ = std::numeric_limits<double>::quiet_NaN();
    }
  }
}

// Used https://www.geeksforgeeks.org/operator-overloading-cpp/ to help with
// operator overloading
/**
 * Sums two Datums if they both contain doubles.
 * @param datum The other Datum.
 * @return If the Datums are doubles, returns the sum between them in a new Datum.
 */
Datum Datum::operator+(const Datum &datum) const {
  if ((IsString() && datum.IsDouble()) || (IsDouble() && datum.IsString())) {
    throw std::runtime_error("Can't add 1 string Datum and 1 double Datum");
  }

  if (IsDouble() && datum.IsDouble()) {
    assert(IsDouble() && datum.IsDouble());
    return Datum(GetDouble() + datum.GetDouble());
  }
  assert(IsString() && datum.IsString());
  return Datum(GetString() + datum.GetString());
}

/**
 * Subtracts two Datums if they both contain doubles.
 * @param datum The other Datum
 * @return If the Datums are doubles, returns the difference between them in a new Datum.
 */
Datum Datum::operator-(const Datum &datum) const {
  if (IsString() || datum.IsString()) {
    throw std::runtime_error("Can't subtract a string Datum.");
  }

  assert(IsDouble() && datum.IsDouble());
  return Datum(GetDouble() - datum.GetDouble());
}

/**
 * Multiplies two Datums if they both contain doubles.
 * @param datum The other Datum.
 * @return If the Datums are doubles, returns the product between them in a new Datum.
 */
Datum Datum::operator*(const Datum &datum) const {
  if (IsString() || datum.IsString()) {
    throw std::runtime_error("Can't multiply a string Datum.");
  }

  assert(IsDouble() && datum.IsDouble());
  return Datum(GetDouble() * datum.GetDouble());
}

/**
 * Divides two Datums if they both contain doubles.
 * @param datum The other Datum.
 * @return If the Datums are doubles, returns the quotient between them in a new Datum.
 */
Datum Datum::operator/(const Datum &datum) const {
  if (IsString() || datum.IsString()) {
    throw std::runtime_error("Can't divide a string Datum.");
  }

  if (datum.GetDouble() == 0) {
    throw std::runtime_error("Can't divide by 0.");
  }

  assert(IsDouble() && datum.IsDouble());
  return Datum(GetDouble() / datum.GetDouble());
}

/**
 * Checks if two double or string Datums are equal.
 * Otherwise, returns false if one Datum is a string and the other is a double.
 * @param datum The other Datum.
 * @return True if the Datums are the same type and equal each other. Otherwise false.
 */
bool Datum::operator==(const Datum &datum) const {
  if (IsDouble() && datum.IsDouble()) {
    return std::abs(GetDouble() - datum.GetDouble()) < kEpsilon;
  } else if (IsString() && datum.IsString()) {
    return GetString() == datum.GetString();
  } else {
    return false;
  }
}

// Used https://www.geeksforgeeks.org/cpp-assignment-operator-overloading/ to
// help with assignment overloading Used ChatGPT to help with the assignment
// comments
/**
 * Assigns a value from a different Datum into this Datum.
 * @param datum The Datum to copy from.
 * @return A reference to this Datum after assignment.
 */
Datum &Datum::operator=(const Datum &datum) {
  // Checks if the object is not assigned to itself (From GeeksForGeeks)
  if (this != &datum) {
    value_ = datum.value_;
  }
  return *this;
}

/**
 * Assigns a value from a double into this Datum.
 * @param double_value The double.
 * @return  A reference to this Datum after assignment.
 */
Datum &Datum::operator=(const double &double_value) {
  value_ = double_value;
  return *this;
}

/**
 * Assigns a value from a string into this Datum.
 * @param string_value The string.
 * @return  A reference to this Datum after assignment.
 */
Datum &Datum::operator=(const std::string &string_value) {
  value_ = string_value;
  return *this;
}
} // namespace cse