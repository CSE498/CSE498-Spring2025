// Anand
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../Group-07/Team07Library/DataFileManager.cpp"
#include "../../Group-07/Team07Library/DataFileManager.h"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

using std::cerr;
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;

void resetFile(const string &filePath) {
  ofstream file(filePath, std::ios::trunc);  // Open truncated file to help clear it
  file.close();
}

string getProjectRoot() {
  std::filesystem::path currentPath = std::filesystem::current_path();
  while (!currentPath.empty() &&
         currentPath.filename() != "CSE498-Spring2025") {
    currentPath = currentPath.parent_path();
  }
  return currentPath.string();
}

TEST_CASE("DataFileManager Construct and Destruct", "[DataFileManager]") {
  cse::DataFileManager dfm;
  REQUIRE_NOTHROW(cse::DataFileManager());
}

TEST_CASE("File Operations", "[DataFileManager]") {
  string projectRoot = getProjectRoot();
  string filePath = projectRoot + "/Group-07/Data/sample.csv";
  resetFile(filePath);  // Clear our file before running the test

  cse::DataFileManager dfm;
  dfm.openFile(filePath);

  REQUIRE(dfm.getFile() == filePath);
  REQUIRE(dfm.getData().size() == 0);  // Ensure file is initially empty

  dfm.closeFile();
  ifstream file(filePath);
  REQUIRE(file.is_open());

  // Ensure the file is empty after the test
  string line;
  REQUIRE(!getline(file, line));

  resetFile(filePath);
}

TEST_CASE("Function Management", "[DataFileManager]") {
  string projectRoot = getProjectRoot();
  string filePath = projectRoot + "/Group-07/Data/sample.csv";
  resetFile(filePath);  // Clear the file before running the test

  cse::DataFileManager dfm;
  dfm.openFile(filePath);

  // Add functions
  int x = 5;
  int y = 10;
  dfm.addFunction("X Value", [&x]() { return x; });
  dfm.addFunction("Y Value", [&y]() { return y; });

  REQUIRE_NOTHROW(dfm.listFunctions());
  REQUIRE(dfm.getData().size() == 0);  // File is initially empty

  // Update CSV file with functions
  dfm.updateFile();
  REQUIRE(dfm.checkUpdate() == false);  // Update made, flag reset to false
  x++;
  dfm.updateFile();
  y++;
  dfm.updateFile();

  // Read the file to check the updates
  ifstream file(filePath);
  string line;
  vector<vector<string>> data;

  while (getline(file, line)) {
    vector<string> row;
    stringstream lineStream(line);
    string cell;
    while (getline(lineStream, cell, ',')) {
      row.push_back(cell);
    }
    data.push_back(row);
  }

  REQUIRE(data.size() == 4);  // 1 header row + 3 rows of updated data
  REQUIRE(data[0][0] == "Y Value");
  REQUIRE(data[0][1] == "X Value");
  REQUIRE(data[1][0] == "10");  // Initial y value
  REQUIRE(data[1][1] == "5");   // Initial x value
  REQUIRE(data[2][0] == "10");  // y remains 10
  REQUIRE(data[2][1] == "6");   // x incremented to 6
  REQUIRE(data[3][0] == "11");  // y incremented to 11
  REQUIRE(data[3][1] == "6");   // x remains 6

  resetFile(filePath);
}

TEST_CASE("File and Data Management", "[DataFileManager]") {
  string projectRoot = getProjectRoot();
  string filePath = projectRoot + "/Group-07/Data/sample.csv";
  resetFile(filePath);

  cse::DataFileManager dfm;
  dfm.openFile(filePath);

  // Add dummy data
  int dummy = 42;
  dfm.addFunction("Dummy", [&dummy]() { return dummy; });

  // Update CSV file with dummy data
  dfm.updateFile();

  // Read the file to check the updates
  ifstream file(filePath);
  string line;
  vector<vector<string>> data;

  while (getline(file, line)) {
    vector<string> row;
    stringstream lineStream(line);
    string cell;
    while (getline(lineStream, cell, ',')) {
      row.push_back(cell);
    }
    data.push_back(row);
  }

  // Ensure file is updated correctly
  REQUIRE(data.size() == 2);  // 1 header row + 1 row of dummy data
  REQUIRE(data[0][0] == "Dummy");
  REQUIRE(data[1][0] == "42");  // Dummy data

  resetFile(filePath);
}

TEST_CASE("Setters and Getters", "[DataFileManager]") {
  string projectRoot = getProjectRoot();
  string filePath = projectRoot + "/Group-07/Data/sample.csv";
  resetFile(filePath);

  cse::DataFileManager dfm;
  dfm.setFile(filePath);

  // Test setFile and getFile
  REQUIRE(dfm.getFile() == filePath);

  // Test setUpdate and checkUpdate
  dfm.setUpdate(true);
  REQUIRE(dfm.checkUpdate() == true);
  dfm.setUpdate(false);
  REQUIRE(dfm.checkUpdate() == false);

  // Test setData and getData
  vector<vector<string>> testData = {{"Header1", "Header2"}, {"Data1", "Data2"}};
  dfm.setData(testData);
  REQUIRE(dfm.getData() == testData);
}

TEST_CASE("Function Management Edge Cases", "[DataFileManager]") {
  string projectRoot = getProjectRoot();
  string filePath = projectRoot + "/Group-07/Data/sample.csv";
  resetFile(filePath);

  cse::DataFileManager dfm;
  dfm.openFile(filePath);

  // Add a function and then a duplicate
  int x = 5;
  dfm.addFunction("X Value", [&x]() { return x; });
  dfm.addFunction("X Value", [&x]() { return x + 1; });  // Duplicate

  // Update CSV file with functions
  dfm.updateFile();

  // Read the file to check the updates
  ifstream file(filePath);
  string line;
  vector<vector<string>> data;

  while (getline(file, line)) {
    vector<string> row;
    stringstream lineStream(line);
    string cell;
    while (getline(lineStream, cell, ',')) {
      row.push_back(cell);
    }
    data.push_back(row);
  }

  // Ensure file has only one function's data
  REQUIRE(data.size() == 2);  // 1 header row + 1 row of data
  REQUIRE(data[1][0] == "6");  // Function result of x + 1

  resetFile(filePath);
}

TEST_CASE("Invalid File Operations", "[DataFileManager]") {
  cse::DataFileManager dfm;
  string invalidPath = "/invalid/path/to/sample.csv";

  // Attempt to open an invalid file path
  dfm.openFile(invalidPath);

  // Ensure file location is not set
  REQUIRE(dfm.getFile().empty());
}

TEST_CASE("Clear and Delete Functions", "[DataFileManager]") {
  cse::DataFileManager dfm;

  // Add functions
  int x = 5;
  dfm.addFunction("X Value", [&x]() { return x; });

  // Delete function and check
  dfm.deleteFunction("X Value");
  REQUIRE_NOTHROW(dfm.listFunctions());

  // Add functions again
  dfm.addFunction("X Value", [&x]() { return x; });

  // Clear all functions and check
  dfm.clearFunctions();
  REQUIRE_NOTHROW(dfm.listFunctions());
}
