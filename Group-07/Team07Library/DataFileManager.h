#ifndef DATAFILEMANAGER_H
#define DATAFILEMANAGER_H

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::function;
using std::ofstream;
using std::string;
using std::unordered_map;
using std::vector;

namespace cse {

/**
 * @class DataFileManager
 * @brief Manages data file operations, particularly CSV files.
 */
class DataFileManager {
 private:
  // https://stackoverflow.com/questions/55520876/creating-an-unordered-map-of-stdfunctions-with-any-arguments
  unordered_map<string, function<int()>> functionMap{};  ///< Stores functions for data generation.
  string fileLocation{};  ///< Path to the CSV file.
  vector<vector<string>> fileData{};  ///< Data read from the CSV file.
  bool updateMade{};  ///< Flag indicating if an update has been made to the data.
  void writeRowsToFile(ofstream &file, const vector<vector<string>> &data);

 public:
  /**
   * @brief Default constructor.
   */
  DataFileManager() = default;

  /**
   * @brief Parameterized constructor initializes file location and opens the
   * file.
   * @param path The file path of the CSV to open.
   */
  DataFileManager(const string &path) : fileLocation(path), updateMade(false) {
    openFile(path);
  }

  /**
   * @brief Destructor.
   */
  ~DataFileManager() = default;

  /**
   * @brief Returns the file location.
   * @return The file location as a string.
   */
  const string &getFile() const { return fileLocation; }

  /**
   * @brief Sets the file location.
   * @param path The new file location.
   */
  void setFile(const string &path) { fileLocation = path; }

  /**
   * @brief Checks if an update has been made.
   * @return True if an update has been made, otherwise false.
   */
  bool checkUpdate() const { return updateMade; }

  /**
   * @brief Sets the update flag.
   * @param status The new update status.
   */
  void setUpdate(bool status) { updateMade = status; }

  /**
   * @brief Sets the data read from the file.
   * @param data The data read from the file.
   */
  void setData(const vector<vector<string>> &data) { fileData = data; }

  /**
   * @brief Returns data read from the current file.
   * @return The data read from the current file.
   */
  vector<vector<string>> getData() const { return fileData; }

  /**
   * @brief Clears all stored functions.
   */
  void clearFunctions() { functionMap.clear(); }

  /**
   * @brief Adds a function to the map.
   * @param name The name of the function.
   * @param lambda The function to add.
   */
  void addFunction(const string &name, const function<int()> &lambda) {
    functionMap[name] = lambda;
  }

  /**
   * @brief Deletes a function from the map.
   * @param name The name of the function to delete.
   */
  void deleteFunction(const string &name) {
    // https://cplusplus.com/reference/unordered_map/unordered_map/erase/
    functionMap.erase(name);
  }

  /**
   * @brief Lists all stored functions.
   */
  void listFunctions() const {
    // https://stackoverflow.com/questions/22880431/iterate-through-unordered-map-c
    for (const auto &[key, value] : functionMap) {
      std::cout << key << std::endl;
    }
  }

  /**
   * @brief Opens a CSV file to read its contents.
   * @param path The file path of the CSV to open.
   */
  void openFile(const string &path);

  /**
   * @brief Updates the CSV file with new data generated from functions.
   */
  void updateFile();

  /**
   * @brief Closes the file and writes any updates made to the data.
   */
  void closeFile();
};

}  // namespace cse

#endif
