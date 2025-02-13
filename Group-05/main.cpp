#include "src/CSVfile.h"
#include "src/DataGrid.h"
#include "src/Datum.h"
#include "src/ReferenceVector.h"
#include <cmath>
#include <fstream>
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
  d2 = "newTest";
  std::cout << "Should output the new string value (newTest)"
            << d2.GetString().value() << std::endl;
  d1 = 987.987;
  std::cout << "Should output the new double value (987.987)"
            << d1.GetDouble().value() << std::endl;

  cse::Datum d_assignment_test(123);
  cse::Datum d_assignment_test1(345);

  std::cout << "Original Output (123)" << d_assignment_test.GetDouble().value()
            << std::endl;
  d_assignment_test = d_assignment_test1;
  std::cout << "Output of assignment (345)"
            << d_assignment_test.GetDouble().value() << std::endl;

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
  cse::Datum d5("123helloWorld");
  std::cout << "Invalid string to double --> Return NaN. Should output 1"
            << std::endl;
  d5.AsDouble();
  std::cout << std::isnan(d5.GetDouble().value()) << std::endl;

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
  std::cout << "Adding two double Datums: " << double_test.GetDouble().value()
            << std::endl;

  cse::Datum datum_string_test = d_add1 + d_add2;
  std::cout << "Adding one double and one string Datum: "
            << datum_string_test.GetDouble().value() << std::endl;

  cse::Datum string_test = d_add2 + d_add3;
  std::cout << "Adding two string Datums: " << string_test.GetDouble().value()
            << std::endl;

  std::cout << "Equal Check (1): " << (d_add == equal_datum) << std::endl;
  std::cout << "Equal Check (0): " << (d_add == d_add1) << std::endl;
  std::cout << "Equal Check (0): " << (d_add == d_add2) << std::endl;
  std::cout << "Equal Check (0): " << (d_add2 == d_add3) << std::endl;
  std::cout << "Equal Check (1): " << (d_add2 == equal_datum1) << std::endl;

  std::cout << "===" << std::endl;

  // ReferenceVector Tests
  cse::ReferenceVector refVec;
  refVec.push_back(d1);
  refVec.push_back(d2);
  refVec.push_back(d3);

  std::cout << "ReferenceVector size should be 3: " << refVec.size()
            << std::endl;
  std::cout << "First element should be 987.987: "
            << refVec.front().GetDouble().value() << std::endl;
  std::cout << "Access to element at will, should be string newTest: "
            << refVec.at(1).GetString().value() << std::endl;
  std::cout << "Last element should be the string 987: "
            << refVec.back().GetString().value() << std::endl;

  // Modify the second element using the Proxy operator=
  cse::Datum newDatum("UpdatedDatum");
  refVec[1] = newDatum;
  std::cout << "Updated second element: " << refVec.at(1).GetString().value()
            << std::endl;

  refVec.pop_back();
  std::cout << "ReferenceVector size after pop_back should be 2: "
            << refVec.size() << std::endl;

  refVec.clear();
  std::cout << "ReferenceVector size after clear should be 0: " << refVec.size()
            << std::endl;
  std::cout << "ReferenceVector empty check should be 1: " << refVec.empty()
            << std::endl;

  std::cout << "=== DataGrid Tests ===\n";
  cse::DataGrid grid;

  std::cout << "\n[1] Insert Rows\n";
  grid.insertDefaultRow(0, 0);
  grid.insertDefaultRow(1, 0);
  std::cout << grid;

  std::cout << "\n[2] Insert Columns\n";
  grid.insertDefaultColumn(0, 0);
  grid.insertDefaultColumn(1, 0);
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
  auto row = grid.getRow(1);
  for (const auto &datum : row) {
    if (datum.IsString()) {
      std::cout << datum.GetString().value() << " ";
    } else if (datum.IsDouble()) {
      std::cout << datum.GetDouble().value() << " ";
    }
  }
  std::cout << "\n";

  std::cout << "\n[6] Get Column 0\n";
  auto col = grid.getColumn(0);
  for (const auto &datum : col) {
    if (datum.IsString()) {
      std::cout << datum.GetString().value() << " ";
    } else if (datum.IsDouble()) {
      std::cout << datum.GetDouble().value() << " ";
    }
  }
  std::cout << "\n";

  std::cout << "\n[7] Delete Row 0\n";
  grid.deleteRow(0);
  std::cout << grid;

  std::cout << "\n[8] Delete Column 0\n";
  grid.deleteColumn(0);
  std::cout << grid;

  // Test: CSVFile::LoadCsv
  std::cout << "\n[9] Testing CSVFile::LoadCsv\n";

  // Create a test input CSV file
  std::ofstream test_input("test_input.csv");
  test_input << "Name,Age,Score\n";
  test_input << "Alice,30,95.5\n";
  test_input << "Bob,25,88.0\n";
  test_input.close();

  // Load the test CSV file into a DataGrid
  cse::DataGrid data_grid;
  try {
    data_grid = cse::CSVFile::LoadCsv("test_input.csv");
    std::cout << "Loaded DataGrid:\n";
    std::cout << data_grid;
  } catch (const std::exception &e) {
    std::cerr << "Failed to load CSV: " << e.what() << std::endl;
  }

  // Test: CSVFile::ExportCsv
  std::cout << "\n[10] Testing CSVFile::ExportCsv\n";

  // Modify the data_grid for export testing
  data_grid.getRow(0)[0] = "Charlie";
  data_grid.getRow(1)[2] = 91.0;

  // Export the modified data_grid to a new CSV file
  try {
    bool success = cse::CSVFile::ExportCsv("test_output.csv", data_grid);
    if (success) {
      std::cout << "Exported DataGrid to test_output.csv successfully.\n";

      // Print the exported CSV file content
      std::ifstream test_output("test_output.csv");
      std::string line;
      std::cout << "Exported CSV content:\n";
      while (std::getline(test_output, line)) {
        std::cout << line << "\n";
      }
      test_output.close();
    }
  } catch (const std::exception &e) {
    std::cerr << "Failed to export CSV: " << e.what() << std::endl;
  }

  return 0;
}
