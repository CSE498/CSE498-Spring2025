/**
 * @file DataGrid.h
 * @author Shahaab Ali
 *
 * @brief A 2D data table providing a simple and efficient tabular interface.
 */

#pragma once

#include <cassert>
#include <iomanip>
#include <limits>
#include <vector>

#include "Datum.h"
#include "ReferenceVector.h"

namespace cse {

/**
 * @class DataGrid
 * @brief A 2D data table providing a simple and efficient tabular interface.
 */
class DataGrid {
private:
  using row_t = std::vector<Datum>; // row_t is an alias for a vector of Datums

  /// A 2D vector holding datums
  std::vector<row_t> grid_;

public:
  explicit DataGrid(const std::vector<std::vector<Datum>> &data) {
    assert(!data.empty());
    assert(!data[0].empty());

    grid_ = data;
  }

  /**
   * @brief Create rectangular datagrid of desired size with default value
   * (double)
   * @param num_rows_
   * @param num_columns_
   * @param default_value_
   */
  explicit DataGrid(const std::size_t num_rows_ = 0, const std::size_t num_columns_ = 0,
           const double default_value_ = 0) {
    this->resize(num_rows_, num_columns_, default_value_);
  }

  /**
   * @brief Create rectangular datagrid of desired size with default value
   * (string)
   * @param num_rows_
   * @param num_columns_
   * @param default_value_
   */
  DataGrid(const std::size_t num_rows_, const std::size_t num_columns_,
           const std::string& default_value_) {
    this->resize(num_rows_, num_columns_, default_value_);
  }

  /**
   * @brief Default Copy Constructor
   */
  DataGrid(const DataGrid &) = default;

  /**
   * @brief Default Move Constructor
   */
  DataGrid(DataGrid &&) = default;

  /**
   * @brief Default Copy Assignment Operator
   */
  DataGrid &operator=(const DataGrid &) = default;

  /**
   * @brief Default Move Assignment Operator
   */
  DataGrid &operator=(DataGrid &&) = default;

  /**
   * @brief Default Destructor
   */
  ~DataGrid() = default;

  /**
   * @brief Delete all data in datagrid
   */
  void clear() { grid_.clear(); }

  row_t &operator[](std::size_t row_index_);
  row_t &getRow(std::size_t row_index_);
  [[nodiscard]] const row_t &getRow(std::size_t row_index_) const;
  Datum &getValue(std::size_t row_index_, std::size_t column_index_);
  [[nodiscard]] const Datum &getValue(std::size_t row_index_,
                        std::size_t column_index_) const;
  [[nodiscard]] std::tuple<std::size_t, std::size_t> shape() const;
  cse::ReferenceVector<Datum> getColumn(std::size_t column_index_);
  void insertDefaultRow(
      std::size_t row_index_ = std::numeric_limits<std::size_t>::max(),
      double default_value_ = 0);
  void insertDefaultRow(
      std::size_t row_index_ = std::numeric_limits<std::size_t>::max(),
      std::string default_value_ = "");
  void insertDefaultColumn(
      std::size_t column_index_ = std::numeric_limits<std::size_t>::max(),
      double default_value_ = 0);
  void insertDefaultColumn(
      std::size_t column_index_ = std::numeric_limits<std::size_t>::max(),
      const std::string &default_value_ = "");
  void deleteRow(std::size_t row_index_);
  void deleteColumn(std::size_t column_index_);
  void resize(std::size_t num_rows_, std::size_t num_columns_,
              double default_value_ = 0);
  void resize(std::size_t num_rows_, std::size_t num_columns_,
              const std::string& default_value_);
  std::ostream &print(std::ostream &os_) const;
  Datum &at(std::size_t row_index_, std::size_t column_index_);
  [[nodiscard]] const Datum &at(std::size_t row_index_, std::size_t column_index_) const;
  row_t &at(std::size_t row_index_);
  [[nodiscard]] const row_t &at(std::size_t row_index_) const;
};

/**
 * @brief Overloaded stream insertion operator for DataGrid
 * @param os Output stream
 * @param grid DataGrid to be printed
 * @return Output stream with DataGrid content
 */
inline std::ostream &operator<<(std::ostream &os, const DataGrid &grid) {
  return grid.print(os);
}

} // namespace cse
