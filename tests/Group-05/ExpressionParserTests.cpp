#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../Group-05/src/ExpressionParser.cpp"
#include "../../Group-05/src/ExpressionParser.h"
#include <map>

TEST_CASE("Parser Evaluations", "[parser]") {
  cse::ExpressionParser parser;
  parser.SetSymbolTable("val1", -2);
  parser.SetSymbolTable("val2", 2);
  parser.SetSymbolTable("val3", -15);
  parser.SetSymbolTable("val4", 15);
  parser.SetSymbolTable("val5", 0);
  parser.SetSymbolTable("val6", 30);
  parser.SetSymbolTable("val7", 1);
 

  // Addition tests
  REQUIRE(parser.Evaluate("{val1} + {val2}") == 0);
  REQUIRE(parser.Evaluate("{val3} + {val3}") == -30);
  REQUIRE(parser.Evaluate("{val4} + {val4}") == 30);

  // Subtraction tests
  REQUIRE(parser.Evaluate("{val1} - {val5}") == -2);
  REQUIRE(parser.Evaluate("{val4} - {val3}") == 30);
  REQUIRE(parser.Evaluate("{val3} - {val4}") == -30);
  REQUIRE(parser.Evaluate("{val6} - {val4}") == 15);

  // Multiplication tests
  REQUIRE(parser.Evaluate("{val1} * {val4}") == -30);
  REQUIRE(parser.Evaluate("{val1} * {val1}") == 4);
  REQUIRE(parser.Evaluate("{val2} * {val2}") == 4);
  REQUIRE(parser.Evaluate("{val1} * {val2}") == -4);

  // Division tests
  REQUIRE(parser.Evaluate("{val5} / {val2}") == 0);
  REQUIRE(parser.Evaluate("{val1} / {val1}") == 1);
  REQUIRE(parser.Evaluate("{val2} / {val2}") == 1);
  REQUIRE(parser.Evaluate("{val1} / {val2}") == -1);
  REQUIRE(parser.Evaluate("{val7} / {val2}") == 0.5);
  
  }

  TEST_CASE("Advanced Parser Funcitonality", "[parser]") {
    cse::ExpressionParser parser;
    parser.SetSymbolTable("val1", -2);
    parser.SetSymbolTable("val2", 2);
    parser.SetSymbolTable("val3", -15);
    parser.SetSymbolTable("val4", 15);
    parser.SetSymbolTable("val5", 0);
    parser.SetSymbolTable("val6", 30);
    parser.SetSymbolTable("val7", 1);
    parser.SetSymbolTable("val8", M_PI);
    parser.SetSymbolTable("val9", 4);
    parser.SetSymbolTable("val10", M_PI/2);
    parser.SetSymbolTable("val11", M_PI/3);
    parser.SetSymbolTable("val12", 8);
    parser.SetSymbolTable("val13", 9);
    parser.SetSymbolTable("val14", 27);

  
    REQUIRE(parser.Evaluate("cos({val8})") == -1);
    REQUIRE(parser.Evaluate("sin({val8}))") == sin(M_PI));
    REQUIRE(parser.Evaluate("cos({val11})") == cos(M_PI/3));
    REQUIRE(parser.Evaluate("sin({val10})") == 1);

    REQUIRE(parser.Evaluate("pow({val2}, {val2})") == 4);
    REQUIRE(parser.Evaluate("pow({val1}, {val2})") == 4);
    REQUIRE(parser.Evaluate("pow({val2}, {val1})") == 0.25);

}
