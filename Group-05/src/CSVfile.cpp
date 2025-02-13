/**
 * @file CSVfile.cpp
 * @author Muhammad Masood
 * @brief Implements CSV file interactions with DataGrid.
 *
 * Provides functions to load CSV data into a DataGrid and export
 * a DataGrid to a CSV file.
 */

#include "CSVfile.h"
#include "DataGrid.h"
#include "Datum.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <vector>

namespace cse {

/**
 * @brief Trims leading and trailing whitespace characters from a string.
 *
 * @param s The string to trim.
 * @return The trimmed string.
 */
static std::string Trim(const std::string &s) {
  size_t start = s.find_first_not_of(" \t\r\n");
  size_t end = s.find_last_not_of(" \t\r\n");
  return (start == std::string::npos || end == std::string::npos)
             ? ""
             : s.substr(start, end - start + 1);
}

/**
 * @brief Checks if a string represents a numeric value.
 *
 * @param s The string to check.
 * @return True if the string is numeric, false otherwise.
 */
static bool IsNumeric(const std::string &s) {
  std::istringstream iss(s);
  double d;
  iss >> d;
  return iss.eof() && !iss.fail();
}

/**
 * @brief Sanitizes a string for CSV format, escaping quotes and handling
 * delimiters.
 *
 * @param s The string to sanitize.
 * @param delimiter The delimiter character used in the CSV.
 * @return The sanitized string.
 */
static std::string Sanitize(const std::string &s, char delimiter) {
  if (s.find(delimiter) != std::string::npos ||
      s.find('"') != std::string::npos) {
    std::string result = "\"";
    for (char c : s) {
      result += (c == '"') ? "\"\"" : std::string(1, c);
    }
    result += "\"";
    return result;
  }
  return s;
}

/**
 * @brief Loads data from a CSV file into a DataGrid.
 *
 * Reads the CSV file, parses each line, and converts the tokens into Datum
 * objects, inserting them into the DataGrid.
 *
 * @param file_name The name of the CSV file to load.
 * @param delimiter The delimiter used in the CSV file.
 * @return A DataGrid populated with the CSV data.
 * @throws std::runtime_error If the file cannot be opened.
 */
DataGrid CSVFile::LoadCsv(const std::string &file_name, char delimiter) {
  std::ifstream file(file_name);
  // First, check if the file stream is open.
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + file_name);
  }
  // Assert that the file stream is open (for debug builds).
  assert(file.is_open() && "File must be open for reading.");

  std::vector<std::vector<cse::Datum>> data;
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream line_stream(line);
    std::string token;
    std::vector<Datum> row;
    while (std::getline(line_stream, token, delimiter)) {
      token = Trim(token);
      if (!token.empty() && IsNumeric(token)) {
        try {
          double value = std::stod(token);
          // Assert that the converted value is not NaN.
          assert(!std::isnan(value) &&
                 "Converted numeric value should not be NaN.");
          row.emplace_back(value);
        } catch (...) {
          row.emplace_back(token);
        }
      } else {
        row.emplace_back(token);
      }
    }

    data.push_back(row);
  }

  cse::DataGrid grid(data);

  file.close();
  return grid;
}

/**
 * @brief Exports data from a DataGrid to a CSV file.
 *
 * Iterates through the DataGrid, sanitizes each value, and writes it to a CSV
 * file.
 *
 * @param file_name The name of the CSV file to write.
 * @param grid The DataGrid to export.
 * @param delimiter The delimiter used in the CSV file.
 * @return True if the export was successful.
 * @throws std::runtime_error If the file cannot be written.
 */
bool CSVFile::ExportCsv(const std::string &file_name, const DataGrid &grid,
                        char delimiter) {
  std::ofstream out_file(file_name);
  // Assert that the output file stream is open.
  assert(out_file.is_open() && "Output file must be open for writing.");
  if (!out_file.is_open()) {
    throw std::runtime_error("Cannot write to file: " + file_name);
  }

  std::tuple<const std::size_t, const std::size_t> shape = grid.shape();
  std::size_t num_rows = std::get<0>(shape);
  std::size_t num_cols = std::get<1>(shape);
  for (std::size_t i = 0; i < num_rows; ++i) {
    const std::vector<Datum> &row = grid.getRow(i);
    // Assert that each row has the expected number of columns.
    assert(row.size() == num_cols &&
           "Row does not have the expected number of columns.");
    for (std::size_t j = 0; j < num_cols; ++j) {
      std::string out_value;
      std::optional<std::string> opt_str = row[j].GetString();
      if (opt_str.has_value()) {
        out_value = opt_str.value();
      } else {
        std::optional<double> opt_double = row[j].GetDouble();
        out_value =
            (opt_double.has_value()) ? std::to_string(opt_double.value()) : "";
      }
      out_file << Sanitize(out_value, delimiter);
      if (j < num_cols - 1) {
        out_file << delimiter;
      }
    }
    out_file << "\n";
  }
  out_file.close();
  return true;
}

} // namespace cse
