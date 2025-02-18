/**
 * @file ArgManager.cpp
 * @author By Will Crawford
 * @brief Implementation of the ArgManager class
 */

#include <iostream>
#include <vector>

#include "ArgManager.h"

/**
 * @brief Constructor for ArgManager
 * @param argc the amount of arguments
 * @param argv the list of arguments
 */
cse::ArgManager::ArgManager(int argc, char* argv[]) {
  // Load in all the command line options
  LoadArgManager();

  // pass argc and argv
  mArgc = argc;
  for (int i = 0; i < argc; i++) {
    mArgv.push_back(argv[i]);
  }
}

/**
 * @brief Loads in all of the command line options
 */
void cse::ArgManager::LoadArgManager() {}

/**
 * @brief Checks if a string is present in the input arguments
 * @param argv the string to check for
 * @return if the string is present in the input arguments
 */
bool cse::ArgManager::Has(std::string argv) {
  // Search through each given arg in argv to check if it has the arg value
  for (int i = 0; i < mArgc; i++) {
    if (mArgv[i] == argv) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Find a string and return the next string as the value of the option
 * @param argv the string to find
 * @return the next string as the value of the option
 */
std::string cse::ArgManager::GetOption(std::string argv) {
  // Search through each given arg in argv
  for (int i = 0; i < mArgc; i++) {
    if (mArgv[i] == argv) {
      // Check if the arg given is the last argument in the argv list, with no
      // valid string after
      if (i + 1 >= mArgc) {
        std::cout << "Invalid output provided for: " << argv << std::endl;
        return "";
      } else {
        return mArgv[i + 1];
      }
    }
  }
  std::cout << "This arg does not exist: " << argv << std::endl;
  // Return a blank string if no arg has been found
  return "";
}

/**
 * @brief Find an option, then get the number after it to determine the size of
 * the list, then return the next values in a list as the value of the option
 * @param argv the string to find
 * @return the next strings in a list as the value of the option
 */
std::vector<std::string> cse::ArgManager::GetOptions(std::string argv) {
  int count = -1;
  int startingIndex = -1;
  std::vector<std::string> toReturn = {};

  // Search through each given arg in argv
  for (int i = 0; i < mArgc; i++) {
    if (mArgv[i] == argv) {
      // Check if the argv given is the last argument in the arg list, with no
      // valid string after
      if (i + 1 >= mArgc) {
        std::cout << "Invalid output provided for: " << argv << std::endl;
        return {""};
      } else if (count == -1) {
        // Check the first value after the arg given, which should be the size
        // of the list

        // Remember the starting position of the list
        startingIndex = i + 1;

        // Try and convert the value into an into
        try {
          count = std::stoi(mArgv[i + 1]);
        } catch (const std::exception& caughtError) {
          std::cerr << "\"" << mArgv[i + 1] << "\" is not an integer"
                    << std::endl;

          // Return a list with an empty string
          return {""};
        }

        // There are not enough arg given after the size provided
        if (startingIndex + count >= mArgc) {
          // Return a list with an empty string
          std::cout << "Not enough options provided for: " << argv << std::endl;
          return {""};
        }
      }
    } else if (i > startingIndex && i <= startingIndex + count) {
      // Add the string to the list
      toReturn.push_back(mArgv[i]);
    }
  }

  // If the arg does not exist
  if (count == -1) {
    std::cout << "This arg does not exist: " << argv << std::endl;

    // Return an empty string
    return {""};
  }

  // Return the list created
  return toReturn;
}

/**
 * @brief Prints help info for ArgManager
 */
void cse::ArgManager::PrintHelp() {
  std::cout << "--help has been triggered\n";
  std::cout << "arguments available:\n";
  std::cout << "-h | The help command" << std::endl;
  std::cout << "-o | Gets the string name after it" << std::endl;
  std::cout
      << "-l | The integer given after determines the list size, every string "
         "after it will be added to the list until it reaches capacity"
      << std::endl;
}