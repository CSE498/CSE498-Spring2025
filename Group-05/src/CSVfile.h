/**
 * @file CSVfile.h
 * @author: Muhammad Masood
 * @brief Manages CSV file interactions with DataGrid.
 *
 * This class provides static functions to load CSV data into a DataGrid
 * and export a DataGrid to a CSV file. It handles basic parsing,
 * type differentiation, and error handling.
 */

#pragma once

#include <string>
#include "DataGrid.h"

namespace cse {

class CSVfile {
 public:
  /**
   * @brief Loads a CSV file into a DataGrid.
   *
   * Reads the CSV file line by line, splits each line using the specified
   * delimiter, and converts tokens to Datum objects.
   *
   * @param file_name The name of the CSV file to load.
   * @param delimiter The delimiter used in the CSV file (default is comma).
   * @return A DataGrid populated with the CSV data.
   * @throws std::runtime_error if the file cannot be opened.
   */
  static DataGrid LoadCSV(const std::string &file_name, char delimiter = ',');

  /**
   * @brief Exports a DataGrid to a CSV file.
   *
   * Iterates over the DataGrid, sanitizes tokens, and writes the data to a CSV file.
   *
   * @param file_name The name of the CSV file to write.
   * @param grid The DataGrid to export.
   * @return True if the export was successful.
   * @throws std::runtime_error if the file cannot be written.
   */
  static bool ExportCSV(const std::string &file_name, const DataGrid &grid, char delimiter = ',');
};

}  // namespace cse
