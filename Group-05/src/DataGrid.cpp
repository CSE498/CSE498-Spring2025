/**
 * @file DataGrid.cpp
 * @author Shahaab Ali
 */

#include "DataGrid.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

#include "Datum.h"

namespace cse {

/**
 * @brief Returns the shape of the DataGrid
 * @return tuple of (# of rows, # of columns)
 */
std::tuple<const std::size_t, const std::size_t> DataGrid::Shape() const {
  const std::size_t num_of_rows = mGrid.size();

  // Source: ChatGPT
  const std::size_t num_of_col =
      num_of_rows == 0
          ? 0
          : std::max_element(mGrid.begin(), mGrid.end(),
                             [](const auto& row1, const auto& row2) {
                               return row1.size() < row2.size();
                             })
                ->size();

  return std::make_tuple(num_of_rows, num_of_col);
}

/**
 * @brief Index a column from DataGrid
 * @param column_index Column index to retrieve
 * @return Indexed vector column from DataGrid
 */
std::vector<Datum> DataGrid::GetColumn(const std::size_t column_index) const {
  std::vector<Datum> column;

  for (const auto& row : mGrid) {
    if (column_index < row.size()) {
      column.push_back(row[column_index]);
    }
  }
  return column;
}

/**
 * @brief Inserts a row at given index
 * @param row_index Index at which to insert the row
 */
void DataGrid::InsertRow(const std::size_t row_index) {
  if (row_index > mGrid.size()) {
    throw std::out_of_range("Row index out of bounds");
  }
  mGrid.insert(mGrid.begin() + row_index, std::vector<Datum>());
}

/**
 * @brief Inserts a column at given index
 * @param column_index Index at which to insert the column
 */
void DataGrid::InsertColumn(const std::size_t column_index) {
  if (!mGrid.empty() && column_index > mGrid[0].size()) {
    throw std::out_of_range("Column index out of bounds");
  }
  for (auto& row : mGrid) {
    row.insert(row.begin() + column_index, Datum(""));
  }
}

/**
 * @brief Deletes a row at given index
 * @param row_index Index of the row to delete
 */
void DataGrid::DeleteRow(const std::size_t row_index) {
  if (row_index >= mGrid.size()) {
    throw std::out_of_range("Row index out of bounds");
  }
  mGrid.erase(mGrid.begin() + row_index);
}

/**
 * @brief Deletes a column at given index
 * @param column_index Index of the column to delete
 */
void DataGrid::DeleteColumn(const std::size_t column_index) {
  if (mGrid.empty() || column_index >= mGrid[0].size()) {
    throw std::out_of_range("Column index out of bounds");
  }
  for (auto& row : mGrid) {
    row.erase(row.begin() + column_index);
  }
}

/**
 * @brief Outputs DataGrid values to output stream for clear visualization
 * @param os Output stream reference
 * @return Modified output stream
 */
std::ostream& DataGrid::Print(std::ostream& os) const {
  auto [rows, cols] = this->Shape();
  os << "Grid Shape: " << rows << " x " << cols << "\n";

  for (std::size_t i = 0; i < rows; ++i) {
    for (std::size_t j = 0; j < cols; ++j) {
      try {
        auto value = this->GetValue(i, j);
        if (value.IsString()) {
          os << value.GetString().value() << " ";
        } else if (value.IsDouble()) {
          os << value.GetDouble().value() << " ";
        }
      } catch (const std::out_of_range&) {
        os << "- ";
      }
    }
    os << "\n";
  }
  return os;
}

}  // namespace cse
