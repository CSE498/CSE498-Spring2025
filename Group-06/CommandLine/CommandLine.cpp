/**
 * @file CommandLine.cpp
 * @brief CommandLine Class implementation file.
 * @author Emil Rahn-Siegel
 * @version 0.1
 * @date 2025-02-17
 *
 */

#ifndef CSE_COMMAND_LINE_CPP_
#define CSE_COMMAND_LINE_CPP_

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
 
namespace cse {

/**
 * @brief A class for users to create their own command line interface
 *
 */
class CommandLine {
public:
  CommandLine() {
    // Add a default help command
    addCommand("help", [this]() { printHelp(); }, "Displays this help message");
  }
  
  /**
  * @brief Adds a command to the command map
  *
  * @param command The command string
  * @param func The function to be executed for the command
  * @param description The description of the command
  */
  void addCommand(const std::string& command, std::function<void()> func,
                  const std::string& description = "") {
    // Add command to the map
    mCommands[command] = func;
    mDescriptions[command] = description;
  }
  
  /**
  * @brief Executes a command if it exists in the command map
  *
  * @param command The command string to be executed
  */
  void executeCommand(const std::string& command) {
    // Execute the command if it exists
    if (mCommands.find(command) != mCommands.end()) {
      try {
        mCommands[command]();
        trackHistory(command);
      } catch (const std::exception& e) {
        std::cerr << "Error executing command: " << e.what() << std::endl;
      }
    } else {
      std::cout << "Unknown command: " << command << std::endl;
    }
  }
  
  /**
  * @brief Tracks the history of executed commands
  *
  * @param command The command string to be tracked
  */
  void trackHistory(const std::string& command) {
    // Track command history
    mHistory.push_back(command);
  }
  
  /**
  * @brief Prints the history of executed commands
  *
  */
  void printHistory() const {
    // Print command history
    for (const auto& cmd : mHistory) {
      std::cout << cmd << std::endl;
    }
  }
  
  /**
  * @brief Clears the history of executed commands
  *
  */
  void clearHistory() { mHistory.clear(); }
  
  /**
  * @brief Tracks the current state
  *
  * @param state The state string to be tracked
  */
  void trackState(const std::string& state) {
    // Track state
    mCurrentState = state;
  }
  
  /**
  * @brief Gets the current state
  *
  * @return std::string The current state
  */
  std::string getState() const {
    // Get current state
    return mCurrentState;
  }
  
  /**
  * @brief Prints the help message with all available commands
  *
  */
  void printHelp() const {
    std::cout << "Available commands:" << std::endl;

    // Create a vector of command names and sort it
    std::vector<std::string> sortedCommands;
    for (const auto& cmd : mDescriptions) {
      sortedCommands.push_back(cmd.first);
    }

    std::sort(sortedCommands.begin(), sortedCommands.end());

    // Print the sorted commands with their descriptions
    for (const auto& cmd : sortedCommands) {
      std::cout << cmd << " - " << mDescriptions.at(cmd) << std::endl;
    }
  }

private:
  /// Map of commands to functions
  std::unordered_map<std::string, std::function<void()>> mCommands;
  /// Map of commands to descriptions
  std::unordered_map<std::string, std::string> mDescriptions;
  /// Vector of command history
  std::vector<std::string> mHistory;
  /// Current state
  std::string mCurrentState;
};

}  // namespace cse

#endif   // CSE_COMMAND_LINE_CPP_