/**
 * @file Datum.cpp
 *
 * @author Max Krawec
 */

#include "Datum.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace cse {

// TODO - May need to change value, I just picked a semi-random one
static const double kEpsilon = 0.0001;

/**
 * Returns the string value of the Datum.
 * @return The string value of the Datum
 */
std::string Datum::GetString() const {
  assert(IsString());
  return std::get<std::string>(GetVariant());
}

/**
 * Returns the double value of the Datum.
 * @return The double value of the Datum
 */
double Datum::GetDouble() const {
  assert(IsDouble());
  return std::get<double>(GetVariant());
}

/**
 * Converts the Datum into a string.
 */
void Datum::AsString() {
  assert(IsDouble());
  assert(!std::isnan(GetDouble()));

  std::string string_numeric_value = std::to_string(GetDouble());

  // CITE: https://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros.
  // Used the above link to help remove trailing 0s and . when a double converts into a string.
  string_numeric_value.erase(string_numeric_value.find_last_not_of('0') + 1,
                             std::string::npos);
  string_numeric_value.erase(string_numeric_value.find_last_not_of('.') + 1,
                             std::string::npos);
  value_ = string_numeric_value;
}

/**
 * Converts the Datum into a double.
 * @warning If the Datum is an invalid double, converts into NaN.
 */
void Datum::AsDouble() {
  assert(IsString());
  try {
    // CITE: Used ChatGPT to write this code. Fixed a bug where strings starting with
    // numbers (e.g., "123Hello") were partially converted instead of throwing an exception.
    std::size_t pos;
    double double_value = std::stod(GetString(), &pos);
    assert(pos == GetString().length());
    value_ = double_value;
  } catch (std::invalid_argument &e) {
      // CITE: Used https://stackoverflow.com/questions/16691207/c-c-nan-constant-literal for NaN
      value_ = std::numeric_limits<double>::quiet_NaN();
      std::cout << "Warning: Attempted to convert a string with no numeric "
                   "value. Replaced the value with NaN."
                << std::endl;
      std::cout << e.what() << std::endl;
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
  assert((IsDouble() && datum.IsDouble())
    || (IsString() && datum.IsString()));
  if (IsDouble() && datum.IsDouble()) {
    return Datum(GetDouble() + datum.GetDouble());
  }
  return Datum(GetString() + datum.GetString());
}

/**
 * Subtracts two Datums if they both contain doubles.
 * @param datum The other Datum
 * @return If the Datums are doubles, returns the difference between them in a new Datum.
 */
Datum Datum::operator-(const Datum &datum) const {
  assert(IsDouble() && datum.IsDouble());
  return Datum(GetDouble() - datum.GetDouble());
}

/**
 * Multiplies two Datums if they both contain doubles.
 * @param datum The other Datum.
 * @return If the Datums are doubles, returns the product between them in a new Datum.
 */
Datum Datum::operator*(const Datum &datum) const {
  assert(IsDouble() && datum.IsDouble());
  return Datum(GetDouble() * datum.GetDouble());
}

/**
 * Divides two Datums if they both contain doubles.
 * @param datum The other Datum.
 * @return If the Datums are doubles, returns the quotient between them in a new Datum.
 */
Datum Datum::operator/(const Datum &datum) const {
  assert(IsDouble() && datum.IsDouble());
  assert(datum.IsDouble() != 0.0);
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