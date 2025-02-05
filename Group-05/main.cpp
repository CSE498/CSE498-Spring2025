#include "src/Datum.h"
#include "src/ReferenceVector.h"
#include <iostream>
#include <cmath>
#include <typeinfo>

// TODO - Improve and move test cases. Will need a testing framework (Probably Catch2?). However, I wanted to test
//  my code before pushing, so I wrote some basic tests in main.

int main() {
  // Constructors
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  std::cout << "Should be True(1): " << d1.IsDouble() << std::endl;
  std::cout << "Should be False(0): " << d1.IsString() << std::endl;

  std::cout << "===" << std::endl;

  // IsDouble()/IsString()
  std::cout << "Should be False(0): " << d2.IsDouble() << std::endl;
  std::cout << "Should be True(1): " << d2.IsString() << std::endl;

  std::cout << "===" << std::endl;

  // Update values
  d2.SetStringValue("newTest");
  std::cout << "Should output the new string value (newTest): " 
            << d2.GetString().value() << std::endl;
  d1.SetDoubleValue(987.987);
  std::cout << "Should output the new double value (987.987): " 
            << d1.GetDouble().value() << std::endl;

  std::cout << "===" << std::endl;

  // Convert double --> string
  cse::Datum d3(987);
  std::cout << "Type should be an double (1) --> Calls AsString() --> End as an string (0)" << std::endl;
  std::cout << d3.GetDouble().has_value() << std::endl;
  d3.AsString();
  std::cout << d3.GetDouble().has_value() << std::endl;
  std::cout << d3.GetString().value() << std::endl;

  std::cout << "===" << std::endl;

  // Convert string --> double
  cse::Datum d4("8.12341");
  std::cout << "Type should be an string (1) --> Calls AsDouble() --> End as an double(0)" << std::endl;
  std::cout << d4.GetString().has_value() << std::endl;
  d4.AsDouble();
  std::cout << d4.GetString().has_value() << std::endl;
  std::cout << d4.GetDouble().value() << std::endl;

  std::cout << "===" << std::endl;

  // Convert invalid string to double --> Return NaN:
  cse::Datum d5("helloWorld");
  std::cout << "Invalid string to double --> Return NaN. Should output 1" << std::endl;
  d5.AsDouble();
  std::cout << std::isnan(d5.GetDouble().value()) << std::endl;

  std::cout << "===" << std::endl;

  // Convert NaN to String --> return empty string
  cse::Datum d6(NAN);
  d6.AsString();
  std::cout << "NaN to String: Should have an empty string: " << d6.GetString().value() << std::endl;

  std::cout << "===" << std::endl;

  // ReferenceVector Tests
  cse::ReferenceVector refVec;
  refVec.push_back(d1);
  refVec.push_back(d2);
  refVec.push_back(d3);

  std::cout << "ReferenceVector size should be 3: " << refVec.size() << std::endl;
  std::cout << "First element should be 987.987: " << refVec.front().GetDouble().value() << std::endl;
  std::cout << "Access to element at will, should be string newTest: " << refVec.at(1).GetString().value() << std::endl;
  std::cout << "Last element should be the string 987: " << refVec.back().GetString().value() << std::endl;

  refVec.pop_back();
  std::cout << "ReferenceVector size after pop_back should be 2: " << refVec.size() << std::endl;

  refVec.clear();
  std::cout << "ReferenceVector size after clear should be 0: " << refVec.size() << std::endl;
  std::cout << "ReferenceVector empty check should be 1: " << refVec.empty() << std::endl;

  return 0;
}