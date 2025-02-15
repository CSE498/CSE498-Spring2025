/**
 * @file ParserTests.cpp
 *
 * @author Max Krawec
 *
 * ExpressionParser tests
 */

#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../Group-05/src/ExpressionParser.cpp"
#include "../../Group-05/src/ExpressionParser.h"

// TODO - May need to change value, I just picked a random one
static const double kEpsilon = 0.0001;

TEST_CASE("Parser Evaluations", "[parser]") {
  cse::ExpressionParser<int> parser_int;
  std::vector<int> values_int {25, 200, -50, -100, 250};

  cse::ExpressionParser<double> parser_double;
  std::vector<double> values_double {2.5, -3.33, -.9, -10, 1.28};

  SECTION("Addition") {
    REQUIRE(parser_int.Evaluate(values_int, "{0} + {1}") == 225);
    REQUIRE(parser_int.Evaluate(values_int, "{2} + {3}") == -150);
    REQUIRE(parser_int.Evaluate(values_int, "{3} + {4}") == 150);

    REQUIRE_THAT(parser_double.Evaluate(values_double, "{0} + {1}"),
                 Catch::WithinAbs(-0.83, kEpsilon));
    REQUIRE_THAT(parser_double.Evaluate(values_double, "{2} + {3}"),
                 Catch::WithinAbs(-10.9, kEpsilon));
    REQUIRE_THAT(parser_double.Evaluate(values_double, "{3} + {4}"),
                 Catch::WithinAbs(-8.72, kEpsilon));


  }

  SECTION("Subtraction") {
    REQUIRE(parser_int.Evaluate(values_int, "{0} - {1}") == -175);
    REQUIRE(parser_int.Evaluate(values_int, "{2} - {3}") == 50);
    REQUIRE(parser_int.Evaluate(values_int, "{3} - {4}") == -350);

    REQUIRE_THAT(parser_double.Evaluate(values_double, "{0} - {1}"),
                 Catch::WithinAbs(5.83, kEpsilon));
    REQUIRE_THAT(parser_double.Evaluate(values_double, "{2} - {3}"),
                 Catch::WithinAbs(9.1, kEpsilon));
    REQUIRE_THAT(parser_double.Evaluate(values_double, "{3} - {4}"),
                 Catch::WithinAbs(-11.28, kEpsilon));
  }

  SECTION("Multiplication") {
    REQUIRE(parser_int.Evaluate(values_int, "{0} * {1}") == 5000);
    REQUIRE(parser_int.Evaluate(values_int, "{2} * {3}") == 5000);
    REQUIRE(parser_int.Evaluate(values_int, "{3} * {4}") == -25000);

    REQUIRE_THAT(parser_double.Evaluate(values_double, "{0} * {1}"),
                 Catch::WithinAbs(-8.325, kEpsilon));
    REQUIRE_THAT(parser_double.Evaluate(values_double, "{2} * {3}"),
                 Catch::WithinAbs(9, kEpsilon));
    REQUIRE_THAT(parser_double.Evaluate(values_double, "{3} * {4}"),
                 Catch::WithinAbs(-12.8, kEpsilon));
  }

  SECTION("Division") {
    REQUIRE(parser_int.Evaluate(values_int, "{0} / {1}") == 0);
    REQUIRE(parser_int.Evaluate(values_int, "{2} / {3}") == 0);
    REQUIRE(parser_int.Evaluate(values_int, "{4} / {3}") == -2);


    REQUIRE_THAT(parser_double.Evaluate(values_double, "{0} / {1}"),
                 Catch::WithinAbs(-0.750750750, kEpsilon));
    REQUIRE_THAT(parser_double.Evaluate(values_double, "{2} / {3}"),
                 Catch::WithinAbs(0.09, kEpsilon));
    REQUIRE_THAT(parser_double.Evaluate(values_double, "{3} / {4}"),
                 Catch::WithinAbs(-7.8125, kEpsilon));
  }
}