#include "DataFileManager.h"

#include <fstream>  // https://stackoverflow.com/questions/13035674/how-to-read-a-file-line-by-line-or-a-whole-text-file-at-include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::function;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

namespace cse {

/**
 * Writes data rows to the file.
 */
void DataFileManager::writeRowsToFile(ofstream &file, const vector<vector<string>> &data) {
  for (const auto &row : data) {
    for (size_t i = 0; i < row.size(); ++i) {
      file << row[i];
      if (i < row.size() - 1) {
        file << ",";
      }
    }
    file << "\n";
  }
}

/**
 * Opens a CSV file and reads its content into fileData.
 * @param path The file path of the CSV to open.
 */
void DataFileManager::openFile(const string &path) {
  // Check if a file is already open
  if (!fileLocation.empty()) {
    cerr << "Please close the current file before attempting to open a new one." << endl;
    return;
  }

  // Handles CSV Case,
  // https://en.cppreference.com/w/cpp/string/basic_string/find_last_of
  if (path.substr(path.find_last_of(".") + 1) != "csv") {
    // https://en.cppreference.com/w/cpp/io/cerr
    cerr << "File extension is not valid." << endl;
    return;
  }

  // Check if the file can be opened
  ifstream file(path);
  if (!file.is_open()) {
    cerr << "Error opening file: " << path << endl;
    return;
  }

  vector<vector<string>> data;
  string line, cell;

  // Read the file line by line
  while (getline(file, line)) {
    vector<string> row;
    stringstream lineStream(line);

    // Read each comma-separated cell
    while (getline(lineStream, cell, ',')) {
      row.push_back(cell);
    }
    data.push_back(row);
  }

  // Record the file location and read in data
  setFile(path);
  setData(data);
}

/**
 * Updates the CSV based on added functions.
 */
void DataFileManager::updateFile() {
  if (fileLocation.empty()) {
    cerr << "No file is currently open." << endl;
    return;
  }

  if (fileData.empty()) {
    // Add headers only if the fileData is empty
    vector<string> headers;
    for (const auto &pair : functionMap) {
      headers.push_back(pair.first);
    }
    fileData.push_back(headers);
  }

  vector<string> newRow;
  for (const auto &pair : functionMap) {
    newRow.push_back(std::to_string(pair.second()));
  }
  fileData.push_back(newRow);
  updateMade = true;

  // Saves the current state of fileData to the file
  ofstream file(fileLocation);
  if (file.is_open()) {
    writeRowsToFile(file, fileData);
    file.close();
  }
  updateMade = false;
}

/**
 * Closes the file and writes any updates made to the data.
 */
void DataFileManager::closeFile() {
  // No need to write if no updates have been made
  if (!updateMade) {
    return;
  }

  ofstream file(fileLocation, std::ios::trunc); // Open file in truncate mode to overwrite
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    return;
  }

  // Write header if functionMap is not empty
  if (!fileData.empty()) {
    for (const auto &pair : functionMap) {
      file << pair.first << ",";
    }
    file.seekp(-1, std::ios_base::end); // Remove the last comma
    file << "\n";
  }

  // Write each row of data to the file
  writeRowsToFile(file, fileData);

  // Clear the file data after writing
  fileData.clear();
}

}
