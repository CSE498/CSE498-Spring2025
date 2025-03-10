/**
 * @file DataGrid.cpp
 * @author Shahaab Ali
 */

#include "DataGrid.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "Datum.h"
#include "ReferenceVector.h"

namespace cse {

/**
 * @brief Index a row of the DataGrid
 * @param row_index_ Index of the row
 * @return Indexed vector row from DataGrid
 */
DataGrid::row_t &DataGrid::operator[](const std::size_t row_index_) {
  return this->at(row_index_);
}

/**
 * @brief Index a row of the DataGrid
 * @param row_index_ Index of the row
 * @return Indexed vector row from DataGrid
 */
DataGrid::row_t &DataGrid::getRow(const std::size_t row_index_) {
  return this->at(row_index_);
}

/**
 * @brief Retrieves a row from the DataGrid in a read-only manner.
 *
 * Allows access to a specific row without modifying the DataGrid.
 *
 * @param row_index_ Index of the row to retrieve.
 * @return A const reference to the indexed vector row from the DataGrid.
 */
const DataGrid::row_t &DataGrid::getRow(const std::size_t row_index_) const {
  assert(!grid_.empty());
  assert(row_index_ < grid_.size());

  if (grid_.empty() || row_index_ >= grid_.size()) {
    throw std::out_of_range("Row index out of bounds");
  }

  return grid_.at(row_index_);
}

/**
 * @brief Get Datum value from DataGrid
 * @param row_index_ Index of the row
 * @param column_index_ Index of the column
 * @return The Datum at the given index
 */
Datum &DataGrid::getValue(const std::size_t row_index_,
                          const std::size_t column_index_) {
  assert(!grid_.empty());
  assert(row_index_ < grid_.size());
  assert(column_index_ < grid_[0].size());

  if (grid_.empty() || row_index_ >= grid_.size() ||
      column_index_ >= grid_[0].size()) {
    throw std::out_of_range("Index out of bounds");
  }

  return grid_.at(row_index_).at(column_index_);
}

/**
 * @brief Get const Datum value from DataGrid (used for stream output printing)
 * @param row_index_ Index of the row
 * @param column_index_ Index of the column
 * @return The Datum at the given index
 */
const Datum &DataGrid::getValue(const std::size_t row_index_,
                                const std::size_t column_index_) const {
  assert(!grid_.empty());
  assert(row_index_ < grid_.size());
  assert(column_index_ < grid_[0].size());

  if (grid_.empty() || row_index_ >= grid_.size() ||
      column_index_ >= grid_[0].size()) {
    throw std::out_of_range("Index out of bounds");
  }

  return grid_.at(row_index_).at(column_index_);
}

/**
 * @brief Returns the shape of the DataGrid
 * @return tuple of (# of rows, # of columns)
 */
std::tuple<std::size_t, std::size_t> DataGrid::shape() const {
  size_t rows = grid_.size();
  size_t columns = rows == 0 ? 0 : grid_[0].size();
  return std::make_tuple(rows, columns);
}

/**
 * @brief Index a column from DataGrid
 * @param column_index_ Column index to retrieve
 * @return Indexed vector column from DataGrid
 */
cse::ReferenceVector<Datum> DataGrid::getColumn(const std::size_t column_index_) {
  assert(!grid_.empty());
  assert(column_index_ < grid_[0].size());

  if (grid_.empty() || column_index_ >= grid_.front().size()) {
    throw std::out_of_range("Column index out of bounds");
  }

  ReferenceVector<Datum> column;

  for (auto &row : grid_) {
    column.PushBack(row.at(column_index_));
  }
  return column;
}

/**
 * @brief Inserts a row at given index
 * @param row_index_ Index at which to insert the row
 * @param default_value_ of row values
 */
void DataGrid::insertDefaultRow(std::size_t row_index_, double default_value_) {
  assert(row_index_ <= grid_.size());

  if (row_index_ > grid_.size()) {
    throw std::out_of_range("Row index out of bounds");
  }

  // If row_index_ is not given, update row_index_ to insert to the end of grid
  if (row_index_ == std::numeric_limits<std::size_t>::max()) {
    row_index_ = grid_.size();
  }

  std::size_t num_columns = std::get<1>(this->shape());

  // Source ChatGPT
  // Inserts row at row_index_
  grid_.insert(grid_.begin() + static_cast<std::ptrdiff_t>(row_index_),
               std::vector<Datum>(num_columns, Datum(default_value_)));
}

/**
 * @brief Inserts a row at given index
 * @param row_index_ Index at which to insert the row
 * @param default_value_ of row
 */
void DataGrid::insertDefaultRow(std::size_t row_index_,
                                std::string default_value_) {
  assert(row_index_ <= grid_.size());

  if (row_index_ > grid_.size()) {
    throw std::out_of_range("Row index out of bounds");
  }

  // If row_index_ is not given, update row_index_ to insert to the end of grid
  if (row_index_ == std::numeric_limits<std::size_t>::max()) {
    row_index_ = grid_.size();
  }

  std::size_t num_columns = std::get<1>(this->shape());

  // Source ChatGPT
  // Inserts row at row_index_
  grid_.insert(grid_.begin() + static_cast<std::ptrdiff_t>(row_index_),
               std::vector<Datum>(num_columns, Datum(std::move(default_value_))));
}

/**
 * @brief Inserts a column at given index
 * @param column_index_ Index at which to insert the column
 * @param default_value_ of column
 */
void DataGrid::insertDefaultColumn(std::size_t column_index_,
                                   double default_value_) {
  assert(!grid_.empty());
  assert(column_index_ <= grid_[0].size());

  if (grid_.empty() || column_index_ > grid_.front().size()) {
    throw std::out_of_range("Column index out of bounds");
  }

  // If column_index_ is not given, update column_index_ to insert to the end of grid
  if (column_index_ == std::numeric_limits<std::size_t>::max()) {
    column_index_ = grid_[0].size();
  }

  // Append values to each row
  for (auto &row : grid_) {
    row.insert(row.begin() + static_cast<std::ptrdiff_t>(column_index_), Datum(default_value_));
  }
}

/**
 * @brief Inserts a column at given index
 * @param column_index_ Index at which to insert the column
 * @param default_value_ of column
 */
void DataGrid::insertDefaultColumn(std::size_t column_index_,
                                   const std::string &default_value_) {
  assert(!grid_.empty());
  assert(column_index_ <= grid_[0].size());

  if (grid_.empty() || column_index_ > grid_.front().size()) {
    throw std::out_of_range("Column index out of bounds");
  }

  // If column_index_ is not given, update column_index_ to insert to the end of grid
  if (column_index_ == std::numeric_limits<std::size_t>::max()) {
    column_index_ = grid_[0].size();
  }

  // Append values to each row
  for (auto &row : grid_) {
    row.insert(row.begin() + static_cast<std::ptrdiff_t>(column_index_), Datum(default_value_));
  }
}

/**
 * @brief Deletes a row at given index
 * @param row_index_ Index of the row to delete
 */
void DataGrid::deleteRow(const std::size_t row_index_) {
  assert(!grid_.empty());
  assert(row_index_ < grid_.size());

  if (row_index_ >= grid_.size()) {
    throw std::out_of_range("Row index out of bounds");
  }

  grid_.erase(grid_.begin() + static_cast<std::ptrdiff_t>(row_index_));
}

/**
 * @brief Deletes a column at given index
 * @param column_index_ Index of the column to delete
 */
void DataGrid::deleteColumn(const std::size_t column_index_) {
  assert(!grid_.empty());
  assert(column_index_ < grid_[0].size());

  if (grid_.empty() || column_index_ >= grid_.front().size()) {
    throw std::out_of_range("Column index out of bounds");
  }

  for (auto &row : grid_) {
    row.erase(row.begin() + static_cast<std::ptrdiff_t>(column_index_));
  }
}

/**
 * @brief Resizes datagrid to any rectangular size with default_value_
 * @param num_rows_
 * @param num_columns_
 * @param default_value_
 */
void DataGrid::resize(std::size_t num_rows_, std::size_t num_columns_,
                      double default_value_) {
  grid_.resize(num_rows_,
               std::vector<Datum>(num_columns_, Datum(default_value_)));

  for (auto &row : grid_) {
    if (row.size() < num_columns_) {
      row.insert(row.end(), num_columns_ - row.size(), Datum(default_value_));
    } else if (row.size() > num_columns_) {
      row.resize(num_columns_);
    }
  }
}

/**
 * @brief Resizes datagrid to any rectangular size with default_value_
 * @param num_rows_
 * @param num_columns_
 * @param default_value_
 */
void DataGrid::resize(std::size_t num_rows_, std::size_t num_columns_,
                      const std::string& default_value_) {
  grid_.resize(num_rows_,
               std::vector<Datum>(num_columns_, Datum(default_value_)));
}

/**
 * @brief Outputs DataGrid values to output stream for clear visualization
 * @param os_
 * @return Modified output stream
 */
std::ostream &DataGrid::print(std::ostream &os_) const {
  auto [rows, columns] = this->shape();
  os_ << "Grid Shape: " << rows << " x " << columns << "\n";

  for (std::size_t i = 0; i < rows; ++i) {
    for (std::size_t j = 0; j < columns; ++j) {
      auto value = this->getValue(i, j);
      if (value.IsString()) {
        os_ << value.GetString() << " ";
      } else if (value.IsDouble()) {
        os_ << value.GetDouble() << " ";
      }
    }
    os_ << "\n";
  }
  return os_;
}

/**
 * @brief Access a datum in the datagrid
 * @param row_index_
 * @param column_index_
 * @return Reference to the Datum at the given index
 */
Datum &DataGrid::at(std::size_t row_index_, std::size_t column_index_) {
  assert(row_index_ < grid_.size());
  assert(column_index_ < grid_[0].size());
  return grid_[row_index_][column_index_];
}

/**
 * @brief Access a datum in the datagrid (const version)
 * @param row_index_
 * @param column_index_
 * @return Const reference to the Datum at the given index
 */
const Datum &DataGrid::at(std::size_t row_index_,
                          std::size_t column_index_) const {
  assert(row_index_ < grid_.size());
  assert(column_index_ < grid_[0].size());
  return grid_[row_index_][column_index_];
}

/**
 * @brief Access a row in the datagrid
 * @param row_index_
 * @return Reference to the row at the given index
 */
DataGrid::row_t &DataGrid::at(std::size_t row_index_) {
  assert(row_index_ < grid_.size());

  if (grid_.empty() || row_index_ >= grid_.size()) {
    throw std::out_of_range("Row index out of bounds");
  }

  return grid_[row_index_];
}

/**
 * @brief Access a row in the datagrid (const version)
 * @param row_index_
 * @return Const reference to the row at the given index
 */
const DataGrid::row_t &DataGrid::at(std::size_t row_index_) const {
  assert(row_index_ < grid_.size());

  if (grid_.empty() || row_index_ >= grid_.size()) {
    throw std::out_of_range("Row index out of bounds");
  }

  return grid_[row_index_];
}

} // namespace cse
