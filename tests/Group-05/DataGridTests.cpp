/**
 * @file DataGridTests.cpp
 * @author Shahaab Ali
 */

#include "../../Group-05/src/DataGrid.cpp"
#include "../../Group-05/src/DataGrid.h"
#include "../../Group-05/src/Datum.cpp"
#include "../../Group-05/src/Datum.h"
#include "../../Group-05/src/ReferenceVector.h"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream> //added this include

using cse::DataGrid;
using cse::Datum;

/**
 * @brief Test parameterized constructor
 */
TEST_CASE("DataGrid: Parameterized Constructor", "[constructor]") {
  DataGrid grid(3, 4);
  auto [rows, cols] = grid.shape();
  CHECK(rows == 3);
  CHECK(cols == 4);
}

/**
 * @brief Test copy and move constructors
 */
TEST_CASE("DataGrid: Copy and Move Constructors", "[constructor]") {
  DataGrid grid1(2, 3);
  DataGrid grid2(grid1);            // Copy constructor
  DataGrid grid3(std::move(grid1)); // Move constructor
  CHECK(grid2.shape() == std::make_tuple(2, 3));
  CHECK(grid3.shape() == std::make_tuple(2, 3));
}

/**
 * @brief Test inserting default rows
 */
TEST_CASE("DataGrid: Insert Row", "[insert]") {
  DataGrid grid(2, 3);
  grid.insertDefaultRow(1, 5.0);
  auto [rows, cols] = grid.shape();
  CHECK(rows == 3);
  CHECK(cols == 3);
}

/**
 * @brief Test inserting default columns
 */
TEST_CASE("DataGrid: Insert Column", "[insert]") {
  DataGrid grid(3, 2);
  grid.insertDefaultColumn(1, 7.5);
  auto [rows, cols] = grid.shape();
  CHECK(rows == 3);
  CHECK(cols == 3);
}

/**
 * @brief Test deleting rows
 */
TEST_CASE("DataGrid: Delete Row", "[delete]") {
  DataGrid grid(3, 3);
  grid.deleteRow(1);
  auto [rows, cols] = grid.shape();
  CHECK(rows == 2);
  CHECK(cols == 3);
}

/**
 * @brief Test deleting columns
 */
TEST_CASE("DataGrid: Delete Column", "[delete]") {
  DataGrid grid(3, 3);
  grid.deleteColumn(1);
  auto [rows, cols] = grid.shape();
  CHECK(rows == 3);
  CHECK(cols == 2);
}

/**
 * @brief Test accessing row
 */
TEST_CASE("DataGrid: Get Row", "[access]") {
  DataGrid grid(2, 2);
  auto &row = grid.getRow(1);
  CHECK(row.size() == 2);
}

/**
 * @brief Test accessing column
 */
TEST_CASE("DataGrid: Get Column", "[access]") {
  DataGrid grid(3, 3);
  auto column = grid.getColumn(1);
  CHECK(column.Size() == 3);
}

/**
 * @brief Test accessing a specific value
 */
TEST_CASE("DataGrid: Get Value", "[access]") {
  DataGrid grid(2, 2);
  Datum d(42.0);
  grid.at(1, 1) = d;
  CHECK(grid.getValue(1, 1).GetDouble() == 42.0);
}

/**
 * @brief Test resizing
 */
TEST_CASE("DataGrid: Resize", "[resize]") {
  DataGrid grid(1, 1);
  grid.resize(4, 5, 3.14);
  auto [rows, cols] = grid.shape();
  CHECK(rows == 4);
  CHECK(cols == 5);
}

/**
 * @brief Test clear function
 */
TEST_CASE("DataGrid: Clear", "[clear]") {
  DataGrid grid(3, 3);
  grid.clear();
  auto [rows, cols] = grid.shape();
  CHECK(rows == 0);
  CHECK(cols == 0);
}

/**
 * @brief Test stream output
 */
TEST_CASE("DataGrid: Stream Output", "[stream]") {
  DataGrid grid(2, 2);
  std::ostringstream os;
  os << grid;
  std::string output = os.str();
  CHECK(output.find("Grid Shape: 2 x 2") != std::string::npos);
}

/**
 * @brief Comprehensive test for DataGrid class under different conditions
 */
TEST_CASE("DataGrid: Comprehensive Test", "[comprehensive]") {
  DataGrid grid(5, 5, 1.0);
  grid.insertDefaultRow(2, 2.0);
  grid.insertDefaultColumn(3, "Water");
  grid.at(4, 4) = Datum(9.99);
  grid.deleteRow(0);
  grid.deleteColumn(1);
  grid.resize(3, 3, 0.0);
  CHECK(grid.shape() == std::make_tuple(3, 3));
  CHECK(grid.getValue(2, 2).GetString() == "Water");
}
