/**
 * @file DataGrid.cpp
 *
 * @author Shahaab Ali
 */

#include <optional>
#include <vector>

#include "DataGrid.h"
#include "Datum.h"

namespace cse {

/**
 * Returns the shape of the DataGrid
 * @return tuple of (# of rows, # of columns)
 */
std::tuple<const std::size_t, const std::size_t> DataGrid::Shape() const {

  const std::size_t num_of_rows = mGrid.size();

  // Source: ChatGPT
  const std::size_t num_of_col =
      num_of_rows == 0
          ? 0
          : std::max_element(mGrid.begin(), mGrid.end(),
                             [](const auto &row1, const auto &row2) {
                               return row1.size() < row2.size();
                             })
                ->size();

  return std::make_tuple(num_of_rows, num_of_col);
}

/**
 * Index a column from DataGrid
 * @param columnIndex
 * @return indexed vector column from DataGrid
 */
std::vector<Datum> DataGrid::GetColumn(const std::size_t columnIndex) const {

  std::vector<Datum> column;

  for (auto &row : mGrid) {
    if (columnIndex < row.size()) {
      column.push_back(row[columnIndex]);
    }
  }

  return column;
}

/**
 * Inserts row at given index
 * @param rowIndex
 */
void DataGrid::insertRow(const std::size_t rowIndex) {
  if (rowIndex > mGrid.size()) {
    throw std::out_of_range("Row index out of bounds");
  }

  mGrid.insert(mGrid.begin() + rowIndex, std::vector<Datum>());
}

/**
 * Inserts column at given index
 * @param columnIndex
 */
void DataGrid::insertColumn(const std::size_t columnIndex) {
  if (!mGrid.empty() && columnIndex > mGrid[0].size()) {
    throw std::out_of_range("Column index out of bounds");
  }

  for (auto &row : mGrid) {
    row.insert(row.begin() + columnIndex, Datum(""));
  }
}

/**
 * Deletes row at given index
 * @param rowIndex
 */
void DataGrid::deleteRow(const std::size_t rowIndex) {
  if (rowIndex >= mGrid.size()) {
    throw std::out_of_range("Row index out of bounds");
  }

  mGrid.erase(mGrid.begin() + rowIndex);
}

/**
 * Deletes column at given index
 * @param columnIndex
 */
void DataGrid::deleteColumn(const std::size_t columnIndex) {
  if (mGrid.empty() || columnIndex >= mGrid[0].size()) {
    throw std::out_of_range("Column index out of bounds");
  }

  for (auto &row : mGrid) {
    row.erase(row.begin() + columnIndex);
  }
}

/**
 * Outputs DataGrid values to output stream for clear visualization
 * @param os
 * @return os
 */
std::ostream &DataGrid::Print(std::ostream &os) const {
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
      } catch (const std::out_of_range &) {
        os << "- ";
      }
    }
    os << "\n";
  }
  return os;
}

} // namespace cse