/**
 * @file DataGrid.h
 *
 * @author Shahaab Ali
 *
 * A 2D data table providing a simple and efficient tabular interface.
 */

#pragma once

#include <iomanip>
#include <vector>

#include "Datum.h"

namespace cse {

/**
 * A 2D data table providing a simple and efficient tabular interface.
 */
class DataGrid {
private:
  /// A 2D vector holding datums
  std::vector<std::vector<Datum>> mGrid;

public:
  /**
   * Default Constructor
   */
  DataGrid() {}

  /**
   * Default Destructor
   */
  ~DataGrid() {}

  std::tuple<const std::size_t, const std::size_t> Shape() const;

  /**
   * Index a row of the DataGrid
   * @param rowIndex
   * @return indexed vector row from DataGrid
   */
  std::vector<Datum> &operator[](const std::size_t rowIndex) {
    return mGrid.at(rowIndex);
  }

  /**
   * Index a row of the DataGrid
   * @param rowIndex
   * @return indexed vector row from DataGrid
   */
  std::vector<Datum> &GetRow(const std::size_t rowIndex) {
    return mGrid.at(rowIndex);
  }

  std::vector<Datum> GetColumn(std::size_t columnIndex) const;

  /**
   * Get Datum value from DataGrid
   * @param rowIndex
   * @param columnIndex
   * @return the Datum at the given index
   */
  Datum &GetValue(const std::size_t rowIndex, const std::size_t columnIndex) {
    return mGrid.at(rowIndex).at(columnIndex);
  }

  const Datum &GetValue(std::size_t rowIndex, std::size_t columnIndex) const {
    return mGrid.at(rowIndex).at(columnIndex);
  }

  void insertRow(std::size_t rowIndex);
  void insertColumn(std::size_t columnIndex);
  void deleteRow(std::size_t rowIndex);
  void deleteColumn(std::size_t columnIndex);
  std::ostream &Print(std::ostream &os) const;
};

inline std::ostream &operator<<(std::ostream &os, const DataGrid &grid) {
  return grid.Print(os);
}

} // namespace cse
