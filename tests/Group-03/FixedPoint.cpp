
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../Group-03/src/FixedPoint.h"
#include <vector>
#include <sstream>
#define CATCH_CONFIG_MAIN
//using Ratio1 = std::ratio<100>;
//using Fixed1 = cse::FixedPoint<Ratio1>;
//
//// Constructor Tests
//TEST_CASE("FixedPoint Default Constructor", "[FixedPoint]") {
//    Fixed1 fp;
//    CHECK(static_cast<double>(fp) == 0.0);
//}
//
//TEST_CASE("FixedPoint Int Constructor", "[FixedPoint]") {
//    Fixed1 fp(static_cast<int64_t>(5));
//    CHECK(static_cast<double>(fp) == 5.0);
//}
//
//TEST_CASE("FixedPoint Double Constructor", "[FixedPoint]") {
//    Fixed1 fp(3.14);
//    CHECK(static_cast<double>(fp) == Approx(3.14).epsilon(1e-6));
//}
//
//// Type Conversion Tests
//TEST_CASE("FixedPoint Conversion to Double", "[FixedPoint]") {
//    Fixed1 fp(7.5);
//    CHECK(static_cast<double>(fp) == Approx(7.5).epsilon(1e-6));
//}
//
//TEST_CASE("FixedPoint Conversion to Int", "[FixedPoint]") {
//    Fixed1 fp(4.9);
//    CHECK(static_cast<int>(fp) == 4);
//}
//
//TEST_CASE("FixedPoint Conversion to Float", "[FixedPoint]") {
//    Fixed1 fp(2.75);
//    CHECK(static_cast<float>(fp) == Approx(2.75f).epsilon(1e-6));
//}
//
//// Arithmetic Operator Tests
//TEST_CASE("FixedPoint Addition", "[FixedPoint]") {
//    Fixed1 a(1.5), b(2.5);
//    Fixed1 result = a + b;
//    CHECK(static_cast<double>(result) == Approx(4.0).epsilon(1e-6));
//}
//
//TEST_CASE("FixedPoint Subtraction", "[FixedPoint]") {
//    Fixed1 a(5.5), b(3.0);
//    Fixed1 result = a - b;
//    CHECK(static_cast<double>(result) == Approx(2.5).epsilon(1e-6));
//}
//
//TEST_CASE("FixedPoint Multiplication", "[FixedPoint]") {
//    Fixed1 a(2.0), b(3.0);
//    Fixed1 result = a * b;
//    CHECK(static_cast<double>(result) == Approx(6.0).epsilon(1e-6));
//}
//
//TEST_CASE("FixedPoint Division", "[FixedPoint]") {
//    Fixed1 a(9.0), b(3.0);
//    Fixed1 result = a / b;
//    CHECK(static_cast<double>(result) == Approx(3.0).epsilon(1e-6));
//}
//
//TEST_CASE("FixedPoint Division by Zero", "[FixedPoint]") {
//    Fixed1 a(5.0), b(0.0);
//    CHECK_THROWS_AS(a / b, std::runtime_error);
//}
//
//// Increment & Decrement Operators
//TEST_CASE("FixedPoint Pre-Increment", "[FixedPoint]") {
//    Fixed1 a(4.0);
//    ++a;
//    CHECK(static_cast<double>(a) == Approx(5.0).epsilon(1e-6));
//}
//
//TEST_CASE("FixedPoint Post-Increment", "[FixedPoint]") {
//    Fixed1 a(4.0);
//    Fixed1 b = a++;
//    CHECK(static_cast<double>(b) == Approx(4.0).epsilon(1e-6));
//    CHECK(static_cast<double>(a) == Approx(5.0).epsilon(1e-6));
//}
//
//TEST_CASE("FixedPoint Pre-Decrement", "[FixedPoint]") {
//    Fixed1 a(4.0);
//    --a;
//    CHECK(static_cast<double>(a) == Approx(3.0).epsilon(1e-6));
//}
//
//TEST_CASE("FixedPoint Post-Decrement", "[FixedPoint]") {
//    Fixed1 a(4.0);
//    Fixed1 b = a--;
//    CHECK(static_cast<double>(b) == Approx(4.0).epsilon(1e-6));
//    CHECK(static_cast<double>(a) == Approx(3.0).epsilon(1e-6));
//}
//
//// Comparison Operator Tests
//TEST_CASE("FixedPoint Equality", "[FixedPoint]") {
//    Fixed1 a(3.0), b(3.0);
//    CHECK(a == b);
//}
//
//TEST_CASE("FixedPoint Inequality", "[FixedPoint]") {
//    Fixed1 a(3.0), b(4.0);
//    CHECK(a != b);
//}
//
//TEST_CASE("FixedPoint Less Than", "[FixedPoint]") {
//    Fixed1 a(2.0), b(3.0);
//    CHECK(a < b);
//}
//
//TEST_CASE("FixedPoint Greater Than", "[FixedPoint]") {
//    Fixed1 a(4.0), b(3.0);
//    CHECK(a > b);
//}
//
//TEST_CASE("FixedPoint Less Than or Equal", "[FixedPoint]") {
//    Fixed1 a(3.0), b(3.0);
//    CHECK(a <= b);
//    CHECK(Fixed1(2.0) <= b);
//}
//
//TEST_CASE("FixedPoint Greater Than or Equal", "[FixedPoint]") {
//    Fixed1 a(3.0), b(3.0);
//    CHECK(a >= b);
//    CHECK(Fixed1(4.0) >= b);
//}
//
//// Stream Output Test
//TEST_CASE("FixedPoint Stream Output", "[FixedPoint]") {
//    Fixed1 a(2.5);
//    std::ostringstream os;
//    os << a;
//    CHECK(os.str() == "2.5");
//}
