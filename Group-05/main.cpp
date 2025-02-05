#include "src/DataGrid.h"
#include "src/Datum.h"
#include <iostream>
#include <typeinfo>

// TODO - Improve and move test cases. Will need a testing framework (Probably
// Catch2?). However, I wanted to test
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
  std::cout << "Should output the new string value (newTest)"
            << d2.GetString().value() << std::endl;
  d1.SetDoubleValue(987.987);
  std::cout << "Should output the new double value (987.987)"
            << d1.GetDouble().value() << std::endl;

  std::cout << "===" << std::endl;

  // Convert double --> string
  cse::Datum d3(987);
  std::cout << "Type should be an double (1) --> Calls AsString() --> End as "
               "an string (0)"
            << std::endl;
  std::cout << d3.GetDouble().has_value() << std::endl;
  d3.AsString();
  std::cout << d3.GetDouble().has_value() << std::endl;
  std::cout << d3.GetString().value() << std::endl;

  std::cout << "===" << std::endl;

  // Convert string --> double
  cse::Datum d4("8.12341");
  std::cout << "Type should be an string (1) --> Calls AsDouble() --> End as "
               "an double(0)"
            << std::endl;
  std::cout << d4.GetString().has_value() << std::endl;
  d4.AsDouble();
  std::cout << d4.GetString().has_value() << std::endl;
  std::cout << d4.GetDouble().value() << std::endl;

  std::cout << "===" << std::endl;

  // Convert invalid string to double --> Return NaN:
  cse::Datum d5("helloWorld");
  std::cout << "Invalid string to double --> Return NaN. Should output 1"
            << std::endl;
  d5.AsDouble();
  std::cout << isnan(d5.GetDouble().value()) << std::endl;

  std::cout << "===" << std::endl;

  // Convert NaN to String --> return empty string
  cse::Datum d6(NAN);
  d6.AsString();
  std::cout << "NaN to String: Should have an empty string: "
            << d6.GetString().value() << std::endl;


  cse::Datum d_add(28.421);
  cse::Datum d_add1(38.32);
  cse::Datum d_add2("test");
  cse::Datum d_add3("test2");
  cse::Datum equal_datum(28.421);
  cse::Datum equal_datum1("test");

  cse::Datum double_test = d_add + d_add1;
  std::cout << "Adding two double Datums: " << double_test.GetDouble().value() << std::endl;

  cse::Datum datum_string_test = d_add1 + d_add2;
  std::cout << "Adding one double and one string Datum: " << datum_string_test.GetDouble().value() << std::endl;

  cse::Datum string_test = d_add2 + d_add3;
  std::cout << "Adding two string Datums: " << string_test.GetDouble().value() << std::endl;

  std::cout << "Equal Check (1): " << (d_add == equal_datum) << std::endl;
  std::cout << "Equal Check (0): " << (d_add == d_add1) << std::endl;
  std::cout << "Equal Check (0): " << (d_add == d_add2) << std::endl;
  std::cout << "Equal Check (0): " << (d_add2 == d_add3) << std::endl;
  std::cout << "Equal Check (1): " << (d_add2 == equal_datum1) << std::endl;


  std::cout << "=== DataGrid Tests ===\n";
  cse::DataGrid grid;

  std::cout << "\n[1] Insert Rows\n";
  grid.InsertRow(0);
  grid.InsertRow(1);
  std::cout << grid;

  std::cout << "\n[2] Insert Columns\n";
  grid.InsertColumn(0);
  grid.InsertColumn(1);
  std::cout << grid;

  std::cout << "\n[3] Modify Values (String and Double)\n";
  grid[0][0] = cse::Datum("Hello");
  grid[0][1] = cse::Datum(3.14);
  grid[1][0] = cse::Datum(42);
  grid[1][1] = cse::Datum("World");
  std::cout << grid;

  std::cout << "\n[4] Convert Values (String to Double and Vice Versa)\n";
  grid[0][1].AsString();
  grid[1][0].AsString();
  grid[0][0].AsDouble();
  grid[1][1].AsDouble();
  std::cout << grid;

  std::cout << "\n[5] Get Row 1\n";
  auto row = grid.GetRow(1);
  for (const auto &datum : row) {
    if (datum.IsString()) {
      std::cout << datum.GetString().value() << " ";
    } else if (datum.IsDouble()) {
      std::cout << datum.GetDouble().value() << " ";
    }
  }
  std::cout << "\n";

  std::cout << "\n[6] Get Column 0\n";
  auto col = grid.GetColumn(0);
  for (const auto &datum : col) {
    if (datum.IsString()) {
      std::cout << datum.GetString().value() << " ";
    } else if (datum.IsDouble()) {
      std::cout << datum.GetDouble().value() << " ";
    }
  }
  std::cout << "\n";

  std::cout << "\n[7] Delete Row 0\n";
  grid.DeleteRow(0);
  std::cout << grid;

  std::cout << "\n[8] Delete Column 0\n";
  grid.DeleteColumn(0);
  std::cout << grid;

  return 0;
}
