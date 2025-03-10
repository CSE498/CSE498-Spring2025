#pragma once

#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

namespace cse {

/**
 * @brief Class to parse string equations
 */
class ExpressionParser {
  private:

  /**
   * @brief set char to subtraction operator
   * 
   * @param sub_char comparison char
   */
  constexpr void subtraction(char& sub_char){
    sub_char='-';
  }

  /**
   * @brief set char to addition operator
   * 
   * @param add_char comparison char
   */
  constexpr void addition(char& add_char){
    add_char='+';
  }

  /**
   * @brief set char to division operator
   * 
   * @param div_char comparison char
   */
  constexpr void division(char& div_char){
    div_char='/';
  }

  /**
   * @brief set char to multiplication operator
   * 
   * @param mult_char comparison char
   */
  constexpr void multiplication(char& mult_char){
    mult_char='*';
  }

  std::map<std::string, double> symbol_table_;
  /**
   * @brief Parses the next key in the equation, returning that number as a double
   *
   * @param expression The string representing the equation
   * @param index The position of the parser in the string
   * @return The first key found
   */
   std::string ParseKey(const std::string &expression, size_t &index);

  /**
   * @brief Creates division function that take a map with values to add
   *
   * @param name1 Key for first value
   * @param name2 Key for second value
   * @return auto Lambda function to perform operation
   */
   auto MakeDivideFun(const std::string &name1, const std::string &name2);

  /**
   * @brief Creates adding function that take a map with values to add
   *
   * @param name1 Key for first value
   * @param name2 Key for second value
   * @return auto Lambda function to perform operation
   */
   auto MakeAddFun(const std::string &name1, const std::string &name2);

  /**
   * @brief Creates subtracting function that take a map with values to add
   *
   * @param name1 Key for first value
   * @param name2 Key for second value
   * @return auto Lambda function to perform operation
   */
   auto MakeSubtractFun(const std::string &name1, const std::string &name2);

  /**
   * @brief Creates multiplication function that take a map with values to add
   *
   * @param name1 Key for first value
   * @param name2 Key for second value
   * @return auto Lambda function to perform operation
   */
   auto MakeMultiplyFun(const std::string &name1, const std::string &name2);

 public:
  /**
   * @brief Default constructor for ExpressionParser object
   */
  ExpressionParser() = default;

  /**
   * @brief Evaluates equation represented by expression and returns simplified value as a double
   *
   * @param number_map Map with value and key that will be regerences in expression
   * @param expression Representing equation
   * @return double representing value of equation
   */
   double Evaluate(const std::string &expression);

   /**
    * @brief Get the Symbol Table object
    * 
    * @return std::map<std::string, double> symbol table
    */
   std::map<std::string, double>& GetSymbolTable(){
    return symbol_table_;
   }

   /**
    * @brief Set a pair in the Symbol Table object
    * 
    * @param key string key for symbol table
    * @param num double value for symbol table
    */
    void SetSymbolTable(const std::string &key, const double &num){
      symbol_table_[key] = num;
    }
  };
}




