/**
 * @file DynamicStringTest.cpp
 * @author Hannah Seyfferth
 */

 #include "../../../../third-party/Catch/single_include/catch2/catch.hpp"
 #include "../../DynamicString/DynamicString.h"
 
 
 // Ensure that DynamicString is empty at time of initialization
 TEST_CASE("Default Constructor", "[DynamicStringTest]") {
     DynamicString ds;
     REQUIRE(ds.ToString() == "");  // Should be empty
 }
 
 // Test static string is initialized properly
 TEST_CASE("Static String Initialization", "[DynamicStringTest]") {
     DynamicString ds("Static");
     DynamicString ds1("Test static text phrase");
 
     CHECK(ds.ToString() == "Static"); // Try a simple string
     CHECK(ds1.ToString() == "Test static text phrase"); // Try a longer string
 }
 
 // Test dynamic function initialization
 TEST_CASE("Dynamic Function Initialization", "[DynamicStringTest]") {
     DynamicString ds([] { return "Dynamic"; });
     REQUIRE(ds.ToString() == "Dynamic");
 }
 
 // Test appending a static string
 TEST_CASE("Append Static String", "[DynamicStringTest]") {
     DynamicString ds("Test");
     ds.Append(" string");
     REQUIRE(ds.ToString() == "Test string");
 }
 
 // Test appending a dynamic function
 TEST_CASE("Append Dynamic Function", "[DynamicStringTest]") {
     DynamicString ds("Test");
     ds.Append([] { return " Dynamic"; });
     REQUIRE(ds.ToString() == "Test Dynamic");
 }
 
 // Test Operator+ with Static String
 TEST_CASE("Operator+ with Static String", "[DynamicStringTest]") {
     DynamicString ds = DynamicString("Hello") + " World";
     REQUIRE(ds.ToString() == "Hello World");
 }
 
 // Test Operator+ with Dynamic Function
 TEST_CASE("Operator+ with Dynamic Function", "[DynamicStringTest]") {
     DynamicString ds = DynamicString("Hello") + [] { return " Dynamic"; };
     REQUIRE(ds.ToString() == "Hello Dynamic");
 }
 
 // Test multiple appends
 TEST_CASE("Multiple Appends", "[DynamicStringTest]") {
     DynamicString ds;
     ds.Append("First ").Append([] { return "Second "; }).Append("Third");
     REQUIRE(ds.ToString() == "First Second Third");
 }
 
 // Test that DynamicString updates dynamically
 TEST_CASE("Dynamic Updates", "[DynamicStringTest]") {
     int counter = 0;
     DynamicString ds([] { return "Test "; });
     ds.Append([&counter] { return "Count: " + std::to_string(++counter); });
 
     REQUIRE(ds.ToString() == "Test Count: 1");
     REQUIRE(ds.ToString() == "Test Count: 2");  // Should increment on each call
 }