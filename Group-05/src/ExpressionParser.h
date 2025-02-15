/**
 * @file ExpressionParser.h
 *
 * @authors Max Krawec and Pedro
 *
 * A class to read an equation from a string and calculate the result using a container.
 */

#pragma once

#include <cassert>
#include <string>
#include <vector>

namespace cse {

/**
 * A class to read an equation from a string and calculate the result using a container.
 */
template<typename template_type>
class ExpressionParser {
 private:
  /**
   * Helper method that determines what operator was used in the equation.
   * @param equation The string equation.
   * @return The operator of the equation.
   */
  char DetermineOperation(const std::string& equation) {
    char operation = ' ';
    for (char character : equation) {
      if (character == '+' || character == '-' || character == '*' || character == '/') {
        operation = character;
        break;
      }
    }
    assert(operation == '+' || operation == '-' || operation == '*' || operation == '/');
    return operation;
  }

  /**
   * Helper function that calculates the value based on the values in the container and of the operator.
   * @param values The container with values.
   * @param operation The operator to perform.
   * @param first_number The first index of the container.
   * @param second_number The second index of the container.
   * @return The calculation based on the operator and values in the container.
   */
   // TODO - maybe make this function a bit better
  template_type CalculateValue(std::vector<template_type> values, char operation, int first_number, int second_number) {
    if (operation == '+') {
      return values[first_number] + values[second_number];
    } else if (operation == '-') {
      return values[first_number] - values[second_number];
    } else if (operation == '*') {
      return values[first_number] * values[second_number];
    } else {
      assert(values[second_number] != 0.0);
      return values[first_number] / values[second_number];
    }
  }

 public:
  /**
   * Default constructor
   */
  ExpressionParser() = default;

  /**
   * Calculates a value based on the values in the container and equation string
   * @param values The container of values.
   * @param expression The equation string
   * @return The calculation based on the operator and values in the container.
   */
  template_type Evaluate(const std::vector<template_type> &values, const std::string &expression) {
    std::size_t first_left_bracket_index = expression.find('{');
    std::size_t first_right_bracket_index = expression.find('}');
    int first_number_index = std::stoi(expression.substr(
        first_left_bracket_index + 1, first_right_bracket_index - first_left_bracket_index - 1));

    assert(first_number_index < values.size());

    std::size_t second_left_bracket_index = expression.find('{', first_left_bracket_index + 1);
    std::size_t second_right_bracket_index = expression.find('}', first_right_bracket_index + 1);
    int second_number_index = std::stoi(expression.substr(
        second_left_bracket_index + 1, second_right_bracket_index - second_left_bracket_index - 1));

    assert(second_number_index < values.size());

    char operation = DetermineOperation(expression);

    return CalculateValue(values, operation, first_number_index, second_number_index);
  }
};

} // namespace cse