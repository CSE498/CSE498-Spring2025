/**
 * @file Datum.h
 *
 * @author Max Krawec
 *
 * A data class that can be either a string or double.
 * Can be useful for quick conversions between types and Excel functionality.
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
  std::variant<std::string, double> value_;

public:
  /**
   * Constructor for a string value.
   * @param value The string value
   */
  explicit Datum(std::string value) { value_ = value; }

  /**
   * Constructor for a double value.
   * @param value The double value
   */
  explicit Datum(double value = 0.0) { value_ = value; }

  // CITE: Used https://www.geeksforgeeks.org/rule-of-five-in-cpp/ for the
  // default constructors

  /**
   * Default copy constructor
   * @param datum The other Datum
   */
  Datum(const Datum &datum) = default;

  /**
   * Default destructor
   */
  ~Datum() = default;

  /**
   * Default move constructor
   */
  Datum(Datum &&) noexcept = default;

  /**
   * Default move assignment operator
   * @param datum The other Datum
   * @return A reference to this Datum
   */
  Datum &operator=(Datum &&datum) noexcept = default;

  /**
   * Checks if the current type of the Datum is a string.
   * @return true if the type is a string, false otherwise.
   */
  [[nodiscard]] bool IsString() const { return std::holds_alternative<std::string>(value_); }

  /**
   * Checks if the current type of the Datum is a double.
   * @return true if the type is a double, false otherwise.
   */
  [[nodiscard]] bool IsDouble() const { return std::holds_alternative<double>(value_); }

  /**
   * Returns the Datum as a variant.
   * @return the variant value.
   */
  [[nodiscard]] std::variant<std::string, double> GetVariant() const { return value_; };

  [[nodiscard]] std::string GetString() const;

  [[nodiscard]] double GetDouble() const;

  [[maybe_unused]] void AsString();

  [[maybe_unused]] void AsDouble();

  Datum &operator=(const Datum &datum);

  Datum &operator=(const double &double_value);

  Datum &operator=(const std::string &string_value);

  Datum operator+(const Datum &datum) const;

  Datum operator-(const Datum &datum) const;

  Datum operator*(const Datum &datum) const;

  Datum operator/(const Datum &datum) const;

  bool operator==(const Datum &datum) const;

  /**
   * Checks if two double or string Datums are not equal.
   * Otherwise, returns true if one Datum is a string and the other is a double.
   * @param datum The other Datum.
   * @return True if the Datums are the same type and not equal each other. Otherwise false.
   */
  bool operator!=(const Datum &datum) const { return !(*this == datum); }
};

} // namespace cse
