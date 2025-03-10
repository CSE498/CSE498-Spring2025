/**
 * @file CSVfile.h
 * @author Muhammad Masood
 * @brief Manages CSV file interactions with DataGrid.
 *
 * This class loads CSV data into a DataGrid and exports a DataGrid to CSV,
 * handling the parsing and errors.
 */

#pragma once

#include "DataGrid.h"
#include <string>

namespace cse {

/**
 * @class CSVFile
 * @brief Handles CSV file operations like loading and exporting the data.
 *
 * Loads data from a CSV file into a DataGrid and then
 * exports the DataGrid content into a CSV file, with proper handling
 * of data types and error cases.
 */
class CSVFile {
public:
  static DataGrid LoadCsv(const std::string &file_name, char delimiter = ',');
  static bool ExportCsv(const std::string &file_name, const DataGrid &grid,
                        char delimiter = ',');

private:
// These are helper functions for internal use in CSV class
  static std::string TrimWhitespaces(const std::string &s);
  static bool IsNumeric(const std::string &s);
  static std::string SanitizeCsvField(const std::string &s, char delimiter);

};

} // namespace cse
