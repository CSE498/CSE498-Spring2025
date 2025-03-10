#include "ExpressionParser.h"

namespace cse {
/**
 * @brief Parses the next key in the equation, returning that number as a double
 * 
 * @param expression The string representing the equation
 * @param index The position of the parser in the string
 * @return The first key found
 */
std::string cse::ExpressionParser::ParseKey(const std::string &expression, size_t &index) {
  assert(index < expression.size());
  assert(std::any_of(expression.begin(), expression.end(), ::isdigit));

  while (index < expression.size() && expression[index]!='{') {
    index++; 
  }

  if (expression[index]=='{') {
    index++; 
    std::string result;

    
    while (expression[index]!='}') {
      assert(expression[index]!='{');
      assert(index<expression.size());
      result.push_back(expression[index]);
      index++;
    }

    if (expression[index]=='}') {
      index++; 
    }

    return result;
  }

  std::cerr << "Error: Expected string inside {}" << std::endl;
  return ""; 
}

/**
 * @brief Creates adding function that take a map with values to add
 *
 * @param key1 Key for first value
 * @param key2 Key for second value
 * @return auto
 */
auto cse::ExpressionParser::MakeAddFun(const std::string &key1, const std::string &key2) {
  using map_t = std::map<std::string, double>;
  return [key1, key2](map_t &m) {
    return m[key1] + m[key2];
  };
}

/**
 * @brief Creates subtracting function that take a map with values to add
 *
 * @param key1 Key for first value
 * @param key2 Key for second value
 * @return auto
 */
auto cse::ExpressionParser::MakeSubtractFun(const std::string &key1, const std::string &key2) {
  using map_t = std::map<std::string, double>;
  return [key1, key2](map_t &m) {
    return m[key1] - m[key2];
  };
}

/**
 * @brief Creates multiplication function that take a map with values to add
 *
 * @param key1 Key for first value
 * @param key2 Key for second value
 * @return auto
 */
auto cse::ExpressionParser::MakeMultiplyFun(const std::string &key1, const std::string &key2) {
  using map_t = std::map<std::string, double>;
  return [key1, key2](map_t &m) {
    return m[key1]*m[key2];
  };
}

/**
 * @brief Creates dividation function that take a map with values to add
 *
 * @param key1 Key for first value
 * @param key2 Key for second value
 * @return auto
 */
auto cse::ExpressionParser::MakeDivideFun(const std::string &key1, const std::string &key2) {
  using map_t = std::map<std::string, double>;
  return [key1, key2](map_t &m) {
    return m[key1]/m[key2];
  };
}

/**
 * @brief Evaluates equation represented by expression and returns simplified value as a double
 *
 * @param symbol_table_ Map with value and key that will be regerences in expression
 * @param expression Representing equation
 * @return double representing value of equation
 */
double cse::ExpressionParser::Evaluate( const std::string &expression) {
  assert(std::any_of(expression.begin(), expression.end(), ::isdigit));
  assert(std::any_of(expression.begin(), expression.end(), [](char c) {
    return c=='+' || c=='-' || c=='/' || c=='*';
  }));
  size_t index = 0;
  std::string first_key;
  std::string second_key;
  first_key = ParseKey(expression, index);  
  double result = 0;
  assert(symbol_table_.find(first_key)!=symbol_table_.end());

  while (index < expression.size()) {
    index++;
    char op = expression[index];  
    char comparison_char;
    if (op=='+' || op=='-' || op=='*' || op=='/') {
      index++;  
      second_key = ParseKey(expression, index);
      assert(symbol_table_.find(second_key)!=symbol_table_.end());
      addition(comparison_char);
      if (op==comparison_char) {
        auto fun = MakeAddFun(first_key, second_key); //Creates function
        result = fun(symbol_table_); 
        break;
      }
      subtraction(comparison_char);
      if (op==comparison_char) {
        auto fun = MakeSubtractFun(first_key, second_key);
        result = fun(symbol_table_);
        break;
      }
      multiplication(comparison_char);
      if (op==comparison_char) {
        auto fun = MakeMultiplyFun(first_key, second_key);
        result = fun(symbol_table_);
        break;
      } 
      division(comparison_char);
      if (op==comparison_char) {
        auto fun = MakeDivideFun(first_key, second_key);
        assert(symbol_table_[second_key]!=0);
        {
          result = fun(symbol_table_);
          break;
        }
      }
    }

  }
  return result;

}
} 
