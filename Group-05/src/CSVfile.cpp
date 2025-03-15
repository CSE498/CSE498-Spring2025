/**
 * @file CSVfile.cpp
 * @author Muhammad Masood
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
#include <iostream>
#include <algorithm>

namespace cse {

/**
 * @brief Trims the whitespaces from both ends of a string.
 *
 * @param input The string to trim.
 * @return The trimmed string.
 */
std::string CSVFile::TrimWhitespaces(const std::string &input) {
  static const std::string WHITESPACE = " \t\r\n";
  // Finds the first character that is not a whitespace.
  auto start = std::find_if(input.begin(), input.end(), [&](char character) {
    return WHITESPACE.find(character) == std::string::npos;
  });
  // Finds the last character that is not a whitespace (using reverse iterator).
  auto end = std::find_if(input.rbegin(), input.rend(), [&](char character) {
    return WHITESPACE.find(character) == std::string::npos;
  });
  // If no non-whitespace character is found, return an empty string; otherwise, return the trimmed substring.
  return (start == input.end()) ? "" : std::string(start, end.base());
}

/**
 * @brief Checks if a string represents a numeric value.
 *
 * @param input The string to check.
 * @return True if the string is numeric, false otherwise.
 */
bool CSVFile::IsNumeric(const std::string &input) {
  std::istringstream iss(input);
  double d;
  iss >> d;

  // Returns true if the entire string is parsed successfully as a number
  return iss.eof() && !iss.fail();
}

/**
 * @brief Prepares a string for CSV format, escaping quotes and handling delimiters.
 *
 * @param input The string to sanitize.
 * @param delimiter The delimiter character used in the CSV.
 * @return The sanitized string.
 */
std::string CSVFile::SanitizeCsvField(const std::string &input, char delimiter) {
  if (input.find(delimiter) != std::string::npos ||
      input.find('"') != std::string::npos) {
    std::string result = "\"";
    for (char character : input) {
      // CITE: Used ChatGPT to help develop this logic for escaping double quotes in CSV fields.
      result += (character == '"') ? "\"\"" : std::string(1, character);
    }
    result += "\"";
    return result;
  }
  return input;
}

/**
 * @brief Loads data from a CSV file into a DataGrid.
 *
 * It reads the CSV file, parses each line, and converts the tokens into Datum
 * objects, by inserting them into the DataGrid.
 *
 * @param file_name The name of the CSV file to load.
 * @param delimiter The delimiter used in the CSV file.
 * @return A DataGrid populated with the CSV data.
 * @throws std::runtime_error If the file cannot be opened.
 */
DataGrid CSVFile::LoadCsv(const std::string &file_name, char delimiter) {
  std::ifstream file(file_name);

  // First, it checks if the file stream is open.
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + file_name);
  }
  // Assert that the file stream is open (which is for debug builds).
  assert(file.is_open() && "File must be open for reading.");

  std::vector<std::vector<cse::Datum>> data;
  std::string line;

  // CITE: Used ChatGPT to help design this block to split each CSV line into tokens using the delimiter.
  while (std::getline(file, line)) {
    std::istringstream line_stream(line);
    std::string token;
    std::vector<Datum> row;

    // CITE: Used StackOverflow to learn how to tokenize each CSV line and trim whitespace effectively for the code below.
    while (std::getline(line_stream, token, delimiter)) {
      // Trim any leading/trailing whitespace from the token.
      token = TrimWhitespaces(token);
      // If the token starts with a quote but doesn't end with one,
      // it likely contains the delimiter as part of the field.
      // Continue reading and appending tokens until we find the closing quote.
      if (!token.empty() && token.front() == '"' && token.back() != '"') {
        std::string next_token;
        while (std::getline(line_stream, next_token, delimiter)) {
          // Append the delimiter and the next part without extra trimming
          // to preserve any spaces inside the quoted field.
          token += delimiter + next_token;
          // Once the token ends with a quote, we've captured the entire field.
          if (!token.empty() && token.back() == '"') {
            break;
          }
        }
      }
      // Remove surrounding quotes if they are present.
      if (!token.empty() && token.front() == '"' && token.back() == '"') {
        token = token.substr(1, token.size() - 2);
      }
      if (!token.empty() && IsNumeric(token)) {
        try {
          double value = std::stod(token);
          // Assert that the converted value is not NaN.
          assert(!std::isnan(value) &&
                 "Converted numeric value should not be NaN.");
          row.emplace_back(value);
        //This will make the error handling more clearer to understand
        } catch (const std::invalid_argument &conversion_error) {
          row.emplace_back(token);
        }
      } else {
        row.emplace_back(token);
      }
    }

    data.push_back(row);
  }
// If no data was read from the CSV, return an empty DataGrid.
  file.close();

if (data.empty()) {
  return DataGrid();
}

  //Initializing a Datagrid directly from the parsed 2D vector
  cse::DataGrid grid(data);
  return grid;
}

/**
 * @brief Exports data from a DataGrid to a CSV file.
 *
 * It iterates through the DataGrid, cleans each value, and writes it to a CSV
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

  // Checks proper error handling in the release builds                        
  if (!out_file.is_open()) {
    throw std::runtime_error("Cannot write to file: " + file_name);
  }

  // Assert that the output file stream is open and is active in debug mode.
  assert(out_file.is_open() && "Output file must be open for writing.");

  //CITE: Used GPT to think through and extract grid's dimensions (rows and columns) for further processing
  std::tuple<const std::size_t, const std::size_t> shape = grid.shape();
  std::size_t num_rows = std::get<0>(shape);
  std::size_t num_cols = std::get<1>(shape);

  //It loops over each row in the grid and gets a reference to the current row.
  for (std::size_t i = 0; i < num_rows; ++i) {
    const std::vector<Datum> &row = grid.getRow(i);
    // Assert that each row has the expected number of columns.
    assert(row.size() == num_cols &&
           "Row does not have the expected number of columns.");
    for (std::size_t j = 0; j < num_cols; ++j) {

      //CITE: Used GPT to help with this if/else statement to convert each datum into a string.
      std::string out_value;
      if (row[j].IsDouble()) {
        double val = row[j].GetDouble();
        // Convert the numeric value to a string—this ensures that even 0.0 is properly represented.
        out_value = std::to_string(val);
      } else {
        // Otherwise, use the string stored in the cell.
        out_value = row[j].GetString();
      }

      //This writes the sanitized cell value and if this isn't the last column, it will append the delimiter.
      out_file << SanitizeCsvField(out_value, delimiter);
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
