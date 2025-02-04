/**
 * @file CSVfile.cpp
 * @author Muhammad Masood
 * @brief Implements CSV file interactions with DataGrid.
 *
 * Provides functions to load CSV data into a DataGrid and export
 * a DataGrid to a CSV file.
 */

#include "CSVfile.h"
#include "Datum.h"
#include "DataGrid.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <vector>

namespace cse {

/**
 * @brief Trims whitespace from the start and end of a string.
 */
static std::string Trim(const std::string &s) {
  size_t start = s.find_first_not_of(" \t\r\n");
  size_t end = s.find_last_not_of(" \t\r\n");
  return (start == std::string::npos || end == std::string::npos)
             ? ""
             : s.substr(start, end - start + 1);
}

/**
 * @brief Checks if a string can be parsed as a valid double.
 */
static bool IsNumeric(const std::string &s) {
  std::istringstream iss(s);
  double d;
  iss >> d;
  return iss.eof() && !iss.fail();
}

/**
 * @brief Encloses the string in quotes if needed, escaping internal quotes.
 */
static std::string Sanitize(const std::string &s, char delimiter) {
  if (s.find(delimiter) != std::string::npos || s.find('"') != std::string::npos) {
    std::string result = "\"";
    for (char c : s) {
      result += (c == '"') ? std::string("\"\"") : std::string(1, c);
    }
    result += "\"";
    return result;
  }
  return s;
}

/**
 * @brief Reads CSV data and populates a DataGrid.
 */
DataGrid CSVfile::LoadCSV(const std::string &file_name, char delimiter) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + file_name);
  }

  DataGrid grid;
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream line_stream(line);
    std::string token;
    std::vector<Datum> row;

    while (std::getline(line_stream, token, delimiter)) {
      token = Trim(token);
      if (!token.empty() && IsNumeric(token)) {
        try {
          row.push_back(Datum(std::stod(token)));
        } catch (...) {
          row.push_back(Datum(token));
        }
      } else {
        row.push_back(Datum(token));
      }
    }

    // Insert a new row and copy the parsed data
    auto shape = grid.Shape();
    std::size_t num_rows = std::get<0>(shape);
    grid.InsertRow(num_rows);
    std::vector<Datum> &new_row = grid.GetRow(num_rows);
    new_row = row;
  }

  file.close();
  return grid;
}

/**
 * @brief Exports the contents of a DataGrid to a CSV file.
 */
bool CSVfile::ExportCSV(const std::string &file_name,
                        const DataGrid &grid,
                        char delimiter) {
  std::ofstream out_file(file_name);
  if (!out_file.is_open()) {
    throw std::runtime_error("Cannot write to file: " + file_name);
  }

  auto shape = grid.Shape();
  std::size_t num_rows = std::get<0>(shape);
  std::size_t num_cols = std::get<1>(shape);

  for (std::size_t i = 0; i < num_rows; ++i) {
    std::vector<Datum> row = grid.GetRow(i);
    for (std::size_t j = 0; j < num_cols; ++j) {
      std::string out_value;
      auto opt_str = row[j].GetString();
      if (opt_str.has_value()) {
        out_value = opt_str.value();
      } else {
        auto opt_double = row[j].GetDouble();
        out_value = (opt_double.has_value())
                        ? std::to_string(opt_double.value())
                        : "";
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

}  // namespace cse
