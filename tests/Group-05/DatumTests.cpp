/**
 * @file DatumTests.cpp
 *
 * @author Max Krawec
 *
 * Tests for the Datum class.
 */

#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include <string>

#include "../../Group-05/src/Datum.cpp"

// CITE: Used https://github.com/catchorg/Catch2/blob/devel/docs/comparing-floating-point-numbers.md
// to learn about REQUIRE_THAT (Used CHECK_THAT instead) and WithinAbs for testing doubles

static const double kEpsilon = 0.0001;

TEST_CASE("GetString() functionality", "[datum]") {
  SECTION("When Datum contains a string") {
    cse::Datum string_test("test");
    CHECK(string_test.GetString() == "test");
  }

  SECTION("When Datum contains a double") {
    cse::Datum double_test(123.123);
    CHECK_THROWS(double_test.GetString());
  }
}

TEST_CASE("GetDouble() functionality", "[datum]") {
  SECTION("When Datum contains a double") {
    cse::Datum double_test(999.777);
    CHECK_THAT(double_test.GetDouble(),
                 Catch::WithinAbs(999.777, kEpsilon));
  }

  SECTION("When Datum contains a string") {
    cse::Datum string_test("hello");
    CHECK_THROWS(string_test.GetDouble());
  }
}

TEST_CASE("AsString() functionality", "[datum]") {
  SECTION("When Datum contains a double") {

    SECTION("When the value is NOT NaN") {
      cse::Datum double_test(123.456);
      double_test.AsString();
      CHECK(double_test.GetString() == "123.456");
    }

    SECTION("When the value is NaN") {
      cse::Datum double_test(std::numeric_limits<double>::quiet_NaN());
      double_test.AsString();
      CHECK(double_test.GetString() == "");
    }
  }

  SECTION("When Datum contains a string") {
    cse::Datum string_test("hello");
    string_test.AsString();
    CHECK(string_test.GetString() == "hello");
  }
}

TEST_CASE("AsDouble() functionality", "[datum]") {
  SECTION("When the Datum is a string") {
    SECTION("The string contains all valid numbers") {
      cse::Datum string_test("987.654");
      string_test.AsDouble();
      CHECK_THAT(string_test.GetDouble(),
                 Catch::WithinAbs(987.654, kEpsilon));
    }

    SECTION("The string contains valid numbers at the start") {
      cse::Datum string_test("123Hello");
      string_test.AsDouble();
      CHECK(std::isnan(string_test.GetDouble()));
    }

    SECTION("The string contains invalid numbers") {
      cse::Datum string_test("test");
      string_test.AsDouble();
      CHECK(std::isnan(string_test.GetDouble()));
    }
  }

  SECTION("When the Datum is a double") {
    cse::Datum double_test(123.123);
    double_test.AsDouble();
    CHECK(double_test.GetDouble() == 123.123);
  }
}

TEST_CASE("Addition functionality", "[datum]") {
  cse::Datum datum_double1(43.26);
  cse::Datum datum_string1("123ABC");

  SECTION("Adding two doubles") {
    cse::Datum datum_double2(23.89);
    cse::Datum result = datum_double1 + datum_double2;
    CHECK_THAT(result.GetDouble(),
                 Catch::WithinAbs(67.15, kEpsilon));
  }

  SECTION("Adding two strings") {
    cse::Datum datum_string2("test");
    cse::Datum result = datum_string1 + datum_string2;
    CHECK(result.GetString() == "123ABCtest");
  }

  SECTION("Adding 1 double datum and 1 string datum") {
    CHECK_THROWS(datum_double1 + datum_string1);
  }

  SECTION("Adding 1 string datum and 1 double datum") {
    CHECK_THROWS(datum_string1 + datum_double1);
  }
}

TEST_CASE("Subtraction functionality", "[datum]") {
  cse::Datum datum_double1(43.26);
  cse::Datum datum_string1("hello");

  SECTION("Subtracting two doubles") {
    cse::Datum datum_double2(23.89);
    cse::Datum result = datum_double1 - datum_double2;
    CHECK_THAT(result.GetDouble(),
                 Catch::WithinAbs(19.37, kEpsilon));
  }

  SECTION("Subtracting 1 double datum and 1 string datum") {
    CHECK_THROWS(datum_double1 - datum_string1);
  }

  SECTION("Subtracting 1 string datum and 1 double datum") {
    CHECK_THROWS(datum_string1 - datum_double1);
  }

  SECTION("Subtracting 2 string datums") {
    cse::Datum datum_string2("test");
    CHECK_THROWS(datum_string1 - datum_string2);
  }
}

TEST_CASE("Multiplication functionality", "[datum]") {
  cse::Datum datum_double1(43.26);
  cse::Datum datum_string1("123ABC");

  SECTION("Multiplying two doubles") {
    cse::Datum datum_double2(23.89);
    cse::Datum result = datum_double1 * datum_double2;
    CHECK_THAT(result.GetDouble(),
                 Catch::WithinAbs(1033.4814, kEpsilon));
  }

  SECTION("Multiplying 1 double datum and 1 string datum") {
    CHECK_THROWS(datum_double1 * datum_string1);
  }

  SECTION("Multiplying 1 string datum and 1 double datum") {
    CHECK_THROWS(datum_string1 * datum_double1);
  }

  SECTION("Multiplying 2 string datums") {
    cse::Datum datum_string2("test");
    CHECK_THROWS(datum_string1 * datum_string2);
  }
}

TEST_CASE("Division functionality", "[datum]") {
  cse::Datum datum_double1(43.26);
  cse::Datum datum_string1("123ABC");

  SECTION("Dividing two doubles") {

    SECTION("Denominator is NOT 0") {
      cse::Datum datum_double2(23.8874);
      cse::Datum result = datum_double1 / datum_double2;
      CHECK_THAT(result.GetDouble(),
                   Catch::WithinAbs(1.811, kEpsilon));
    }

    SECTION("Denominator IS 0") {
      cse::Datum datum_double2(0.000);
      CHECK_THROWS(datum_double1 / datum_double2);
    }
  }

  SECTION("Dividing 1 double datum and 1 string datum") {
    CHECK_THROWS(datum_double1 / datum_string1);
  }

  SECTION("Dividing 1 string datum and 1 double datum") {
    CHECK_THROWS(datum_string1 / datum_double1);
  }

  SECTION("Dividing 2 string datums") {
    cse::Datum datum_string2("test");
    CHECK_THROWS(datum_string1 / datum_string2);
  }
}

TEST_CASE("Equal Functionality", "[datum]") {
  SECTION("Testing two strings") {
    cse::Datum datum_string("test");
    cse::Datum datum_string1("test");
    cse::Datum datum_string2("test2");

    CHECK(datum_string == datum_string1);
    CHECK(datum_string != datum_string2);
  }

  SECTION("Testing two doubles") {
    cse::Datum datum_double(123.123);
    cse::Datum datum_double1(123.123);
    cse::Datum datum_double2(123.12369);

    CHECK(datum_double == datum_double1);
    CHECK(datum_double != datum_double2);
  }

  SECTION("Testing one double and one string") {
    cse::Datum datum_double(123.123);
    cse::Datum datum_string("test");
    CHECK(datum_double != datum_string);
  }
}

TEST_CASE("Assignment functionality", "[datum]") {

  SECTION("Datum assignment") {

    SECTION("Datum assignment") {
      cse::Datum datum_double(123.123);
      cse::Datum datum_double1 = datum_double;
      CHECK_THAT(datum_double.GetDouble(),
                 Catch::WithinAbs(123.123, kEpsilon));
    }
  }

  SECTION("Double assignment") {
    cse::Datum datum_double(123.123);
    datum_double = 420.420;
    CHECK_THAT(datum_double.GetDouble(),
                 Catch::WithinAbs(420.420, kEpsilon));
  }

  SECTION("String assignment") {
    cse::Datum datum_string("test");
    datum_string = "testUpdate";
    CHECK(datum_string.GetString() == "testUpdate");
  }
 }