/**
 * @file CSVFileTests.cpp
 *
 * @author Muhammad Masood
 *
 * Tests for the CSV class.
 */

#include "../../Group-05/src/CSVfile.cpp"
#include "../../Group-05/src/CSVfile.h"
#include "../../Group-05/src/DataGrid.cpp"
#include "../../Group-05/src/DataGrid.h"
#include "../../Group-05/src/Datum.cpp"
#include "../../Group-05/src/Datum.h"
#include "../../Group-05/src/ReferenceVector.h"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

using cse::DataGrid;
using cse::Datum;

TEST_CASE("CSVFile LoadCsv - Valid File", "[CSVFile]") {
  // Create a temporary CSV file for testing
  std::string test_file_name = "test_csv_input.csv";
  {
    std::ofstream out_file(test_file_name);
    REQUIRE(out_file.is_open());
    // Write CSV content with a header and two data rows
    out_file << "Name,Age,Score\n";
    out_file << "Alice,30,95.5\n";
    out_file << "Bob,25,88.0\n";
    out_file.close();
  }

  // Load the CSV file into a DataGrid
  cse::DataGrid data_grid;
  try {
    data_grid = cse::CSVFile::LoadCsv(test_file_name);
  } catch (const std::exception &e) {
    FAIL("Exception thrown during LoadCsv: " << e.what());
  }

  // Check that the grid has 3 rows and 3 columns
  std::tuple<const std::size_t, const std::size_t> grid_shape =
      data_grid.shape();
  REQUIRE(std::get<0>(grid_shape) == 3);
  REQUIRE(std::get<1>(grid_shape) == 3);

  // Validate header row
  {
    std::vector<cse::Datum> row0 = data_grid.getRow(0);
    REQUIRE(row0.size() == 3);
    CHECK(row0[0].GetString() == "Name");
    CHECK(row0[1].GetString() == "Age");
    CHECK(row0[2].GetString() == "Score");
  }
  // Validate first data row
  {
    std::vector<cse::Datum> row1 = data_grid.getRow(1);
    REQUIRE(row1.size() == 3);
    CHECK(row1[0].GetString() == "Alice");
    CHECK(row1[1].GetDouble() == Approx(30.0));
    CHECK(row1[2].GetDouble() == Approx(95.5));
  }
  // Validate second data row
  {
    std::vector<cse::Datum> row2 = data_grid.getRow(2);
    REQUIRE(row2.size() == 3);
    CHECK(row2[0].GetString() == "Bob");
    CHECK(row2[1].GetDouble() == Approx(25.0));
    CHECK(row2[2].GetDouble() == Approx(88.0));
  }

  // Cleanup temporary file
  std::remove(test_file_name.c_str());
}

TEST_CASE("CSVFile ExportCsv - Valid DataGrid", "[CSVFile]") {
  // Create a DataGrid with known content
  cse::DataGrid data_grid(3, 3);

  // Fill header row
  data_grid.at(0, 0) = cse::Datum("Name");
  data_grid.at(0, 1) = cse::Datum("Age");
  data_grid.at(0, 2) = cse::Datum("Score");

  // Fill first data row
  data_grid.at(1, 0) = cse::Datum("Charlie");
  data_grid.at(1, 1) = cse::Datum(28);
  data_grid.at(1, 2) = cse::Datum(91.0);

  // Fill second data row
  data_grid.at(2, 0) = cse::Datum("Diana");
  data_grid.at(2, 1) = cse::Datum(32);
  data_grid.at(2, 2) = cse::Datum(85.5);

  // Export the DataGrid to a temporary CSV file
  std::string test_file_name = "test_csv_output.csv";
  try {
    bool export_success = cse::CSVFile::ExportCsv(test_file_name, data_grid);
    REQUIRE(export_success);
  } catch (const std::exception &e) {
    FAIL("Exception thrown during ExportCsv: " << e.what());
  }

  // Read back the exported file and check its content
  std::ifstream in_file(test_file_name);
  REQUIRE(in_file.is_open());
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(in_file, line)) {
    lines.push_back(line);
  }
  in_file.close();

  // The CSV file should have 3 lines corresponding to 3 rows
  REQUIRE(lines.size() == 3);
  // Check header row (no sanitization needed if there are no delimiters or
  // quotes)
  CHECK(lines[0] == "Name,Age,Score");
  // Note: std::to_string produces six decimals for doubles by default
  CHECK(lines[1] == "Charlie,28.000000,91.000000");
  CHECK(lines[2] == "Diana,32.000000,85.500000");

  // Cleanup temporary file
  std::remove(test_file_name.c_str());
}

TEST_CASE("CSVFile LoadCsv - File Not Found", "[CSVFile]") {
  // Attempt to load a non-existent CSV file and expect an exception
  std::string non_existent_file = "non_existent_file.csv";
  CHECK_THROWS_AS(cse::CSVFile::LoadCsv(non_existent_file), std::runtime_error);
  
}

TEST_CASE("CSVFile LoadCsv - Empty CSV", "[CSVFile][edge]") {
  // Create an empty CSV file.
  std::string test_file = "empty.csv";
  {
    std::ofstream out_file(test_file);
    REQUIRE(out_file.is_open());
    // Write nothing to simulate an empty file.
    out_file.close();
  }

  // Load the empty CSV file.
  cse::DataGrid grid = cse::CSVFile::LoadCsv(test_file);
  auto shape = grid.shape();
  // Expect the grid to be empty.
  REQUIRE(std::get<0>(shape) == 0);
  REQUIRE(std::get<1>(shape) == 0);

  std::remove(test_file.c_str());
}

TEST_CASE("CSVFile LoadCsv - Header Only", "[CSVFile][edge]") {
  // Create a CSV file with only a header row.
  std::string test_file = "header_only.csv";
  {
    std::ofstream out_file(test_file);
    REQUIRE(out_file.is_open());
    out_file << "Name,Age,Score\n";
    out_file.close();
  }

  // Load the CSV file.
  cse::DataGrid grid = cse::CSVFile::LoadCsv(test_file);
  auto shape = grid.shape();
  // Expect 1 row (the header) and 3 columns.
  REQUIRE(std::get<0>(shape) == 1);
  REQUIRE(std::get<1>(shape) == 3);

  std::remove(test_file.c_str());
}

TEST_CASE("CSVFile LoadCsv - Special Characters", "[CSVFile][edge]") {
  // Create a CSV file with special characters in fields.
  std::string test_file = "special_chars.csv";
  {
    std::ofstream out_file(test_file);
    REQUIRE(out_file.is_open());
    out_file << "\"Name\",\"Age\",\"Comment\"\n";
    out_file << "\"Alice\",\"30\",\"Hello, world!\"\n";
    // Here, newlines inside a field might not be fully supported by our parser as of now.
    //This might need some adjustment in near-future updates.
    out_file << "\"Bob\",\"25\",\"Line1\\nLine2\"\n";
    out_file.close();
  }

  // Load the CSV file.
  cse::DataGrid grid = cse::CSVFile::LoadCsv(test_file);
  auto shape = grid.shape();
  // Expect 3 rows, 3 columns.
  REQUIRE(std::get<0>(shape) == 3);
  REQUIRE(std::get<1>(shape) == 3);
  
  // Check that special characters are preserved or handled as intended.
  std::vector<cse::Datum> row1 = grid.getRow(1);
  CHECK(row1[2].GetString() == "Hello, world!");

  std::remove(test_file.c_str());
}

TEST_CASE("CSVFile ExportCsv - Zero Value Preservation", "[CSVFile][edge]") {
  // Create a DataGrid with a 0.0 value.
  cse::DataGrid data_grid(1, 1);
  data_grid.at(0, 0) = cse::Datum(0.0);
  std::string test_file = "zero_value.csv";
  bool export_success = cse::CSVFile::ExportCsv(test_file, data_grid);
  REQUIRE(export_success);

  // Read the exported CSV file.
  std::ifstream in_file(test_file);
  REQUIRE(in_file.is_open());
  std::string content;
  std::getline(in_file, content);
  // Check that the 0.0 value is present (std::to_string typically outputs "0.000000").
  CHECK(content.find("0.000000") != std::string::npos);

  in_file.close();
  std::remove(test_file.c_str());
}