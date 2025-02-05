/**
 * @file Datum.h
 *
 * @author Max Krawec
 *
 * A data class that can be either a string or double.
 */

#pragma once

#include <optional>
#include <string>
#include <variant>

namespace cse {

/**
 * A data class that can be either a string or double.
 */
class Datum {
 private:
  /// Stores the string or double value.
  std::variant<std::string, double> mValue;

 public:
  /**
   * Constructor for a string value.
   *
   * @param value The string value
   */
  Datum(std::string value) { mValue = value; }

  /**
   * Constructor for a double value.
   *
   * @param value The double value
   */
  Datum(double value) { mValue = value; }

  /**
   * Checks if the current type of the Datum is a string.
   *
   * @return true if the type is a string, false otherwise.
   */
  bool IsString() const { return std::holds_alternative<std::string>(mValue); }

  /**
   * Checks if the current type of the Datum is a double.
   *
   * @return true if the type is a double, false otherwise.
   */
  bool IsDouble() const { return std::holds_alternative<double>(mValue); }

  /**
   * Sets the Datum to a new string value.
   *
   * @param value The new string value.
   */
  void SetStringValue(std::string value) { mValue = value; }

  /**
   * Sets the Datum to a new double value.
   *
   * @param value The new double value.
   */
  void SetDoubleValue(double value) { mValue = value; }

  /**
   * Returns the Datum as a variant.
   *
   * @return the variant value.
   */
  std::variant<std::string, double> GetVariant() const { return mValue; };

  std::optional<std::string> GetString() const;

  std::optional<double> GetDouble() const;

  void AsString();

  void AsDouble();
};

}  // namespace cse
