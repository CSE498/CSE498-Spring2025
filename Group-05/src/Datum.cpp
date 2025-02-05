/**
 * @file Datum.cpp
 *
 * @author Max Krawec
 */

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "Datum.h"

namespace cse {

/**
 * Returns the string value of the Datum if it contains a string.
 *
 * @return An optional if the Datum contains a string, otherwise an empty
 * optional.
 */
std::optional<std::string> Datum::GetString() const {
  if (IsString()) {
    return std::get<std::string>(GetVariant());
  }
  return {};
}

/**
 * Returns the double value of the Datum if it contains a double.
 *
 * @return An optional if the Datum contains a double, otherwise an empty
 * optional.
 */
std::optional<double> Datum::GetDouble() const {
  if (IsDouble()) {
    return std::get<double>(GetVariant());
  }
  return {};
}

/**
 * Converts the Datum into a string.
 *
 * @warning If Datum is NaN, it converts into an empty string.
 */
void Datum::AsString() {
  if (GetDouble()) {
    if (std::isnan(GetDouble().value())) {
      SetStringValue("");
    } else {
      SetStringValue(std::to_string(GetDouble().value()));
    }
  }
}

/**
 * Converts the Datum into a double
 *
 * @warning If the Datum is an invalid double, it converts into NaN
 */
void Datum::AsDouble() {
  if (GetString()) {
    try {
      SetDoubleValue(std::stod(GetString().value()));
    } catch (std::invalid_argument &e) {
      // Citation: Used
      // https://stackoverflow.com/questions/16691207/c-c-nan-constant-literal
      // for NaN
      SetDoubleValue(std::numeric_limits<double>::quiet_NaN());
      std::cout << "Warning: Attempted to convert a string with no numeric "
                   "value. Replaced value with NaN."
                << std::endl;
      std::cout << e.what() << std::endl;
    }
  }
}

}  // namespace cse