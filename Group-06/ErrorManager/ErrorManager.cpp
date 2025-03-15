/**
 * @file ErrorManager.cpp
 * @author Ivan Bega
 * @brief 
 * @version 0.1
 * @date 2025-02-17
 * 
 */

#ifndef CSE_ERROR_MANAGER_CPP_
#define CSE_ERROR_MANAGER_CPP_

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <array>
#include <regex>

namespace cse {
/**
 * @brief A class for convenient management and output of different types of
 * errors
 *
 *
 */
class ErrorManager {
 public:
  /**
   * @brief Possible levels of errors
   *
   */
  enum class ErrorLevel { Info = 0, Warning = 1, Fatal = 2 };

  /**
   * @brief Executes a function and displays an error if function throws during
   * execution
   *
   * @param function Function to be executed
   * @param message Error message to be displayed if a function fails
   * @param level Error level of a message
   */
  void executeAndHandleError(const std::function<void()>& function,
                             const std::string& message,
                             ErrorLevel level = ErrorLevel::Info) {
    // assert(function);

    try {
      function();
    } catch (const std::exception& e) {
      printError(message, level);
    }
  }
  /**
   * @brief Writes a message to console with a message type at the start of a
   * line
   *
   * @param message Message to be sent to user
   * @param level Error level of a message. Defaults to "Info" if not specified
   */
  void printError(const std::string& message,
                  ErrorLevel level = ErrorLevel::Info) {
    printError(0, message, level);
  }

  /**
   * @brief Writes a message to console with a message type at line number
   *
   * @param line Line number where error occured
   * @param message Message to be sent to user
   * @param level Error level of a message. Defaults to "Info"
   */
  void printError(int32_t line, const std::string& message,
                  ErrorLevel level = ErrorLevel::Info) {
    assert(!message.empty());
    assert(static_cast<std::size_t>(level) < mStringColorCodes.size());
    assert(static_cast<std::size_t>(level) < mTerminationEnabled.size());
    std::stringstream ss;
    ss << "[";
    if (mColorsEnabled) {
      ss << mStringColorCodes[static_cast<int>(level)];
    }
    ss << errorLevelToString(level);
    if (mColorsEnabled) {
      ss << COLOR_RESET;
    }
    ss << "]";

    assert(line >= 0);

    if (line > 0) {
      ss << " (line " << line << ")";
    }
    ss << ": " << message << "\n";

    std::string output = ss.str();
    std::cout << output;  // output error to the console

    // Format for logging into a file
    if (mLogFile.is_open()) {
      if (mColorsEnabled) {
        // Remove ANSI color codes for output in the file
        // Tried to use RegEx, as suggested by a reviewer,
        // but it was too difficult to implement

        size_t pos = 0;
        while ((pos = output.find("\033[")) != std::string::npos) {
          size_t endPos = output.find('m', pos);
          if (endPos != std::string::npos) {
            output.erase(pos, endPos - pos + 1);  // erase color code
          }
        }

        mLogFile << output;
        mLogFile.flush();
      }
    }

    if (mActions[static_cast<int>(level)]) {
      mActions[static_cast<int>(level)]();
    }

    int code = mTerminationEnabled[static_cast<int>(level)];
    if (code > 0) {
      exit(code);
    }
  }

  /**
   * @brief Set the Action that will be invoked when an error of a certain
   * ErrorType occurs
   *
   * @param level Error Level to which action will be assigned
   * @param action Function that will be called. Does not accept arguments and
   * returns void
   */
  void setAction(ErrorLevel level, const std::function<void()>& action) {
    assert(action);

    mActions[static_cast<int>(level)] = action;
  }

  /**
   * @brief Constructs a new Error Manager object
   *
   * @param filePath Optional parameter for a file path where errors will be
   * logged
   */
  ErrorManager(const std::optional<std::string>& filePath = std::nullopt) {
    if (filePath.has_value()) {
      mLogFile.open(filePath.value(), std::ios::app);
      if (!mLogFile.is_open()) {
        std::cerr << "Unable to open log file: " << filePath.value()
                  << std::endl;
      }
    }
  }

  /**
   * @brief Destroy the Error Manager object and close logging file if it was
   * opened
   *
   */
  ~ErrorManager() {
    if (mLogFile.is_open()) {
      mLogFile.close();
    }
  }

  /**
   * @brief Allows to enable or disable coloring for ErrorLevel tag in console
   * output
   *
   * @param enabled Specifies whether to enable or disable coloring
   */
  void enableColors(bool enabled) { this->mColorsEnabled = enabled; }

  /**
   * @brief Allows to enable termination via exit() if an error of a specified
   * type occurs
   *
   * @param level The error level for which termination will be enabled or
   * disabled
   * @param enabled Enables or disables termination of the program
   * @param statusCode optional parameter: specifies which status code to use
   * for exit()
   */
  void enableTermination(ErrorLevel level, bool enabled,
                         int32_t statusCode = 1) {
    assert(statusCode >= 0);

    if (enabled) {
      mTerminationEnabled[static_cast<int>(level)] = statusCode;
    } else {
      mTerminationEnabled[static_cast<int>(level)] = 0;
    }
  }

 private:
 
  /// @brief Green ANSI color code for Info
  static constexpr const char* COLOR_GREEN = "\033[32m";

  /// @brief Yellow ANSI color code for Warning
  static constexpr const char* COLOR_YELLOW = "\033[33m";

  /// @brief Red ANSI color code for Fatal
  static constexpr const char* COLOR_RED = "\033[31m";

  /// @brief Reset color code
  static constexpr const char* COLOR_RESET = "\033[0m";

  /// @brief Info string constant
  static constexpr const char* INFO_STRING = "Info";

  /// @brief Warning string constant
  static constexpr const char* WARNING_STRING = "Warning";
  
  /// @brief Fatal string constant
  static constexpr const char* FATAL_STRING = "Fatal";

  /// @brief Tracks whether color messages are enabled

  bool mColorsEnabled = true;

  /// @brief File for logging errors
  std::ofstream mLogFile;

  /// @brief Array that matches ErrorLevel to the corresponding ANSI color code
  std::array<std::string, 3> mStringColorCodes = {
      COLOR_GREEN, COLOR_YELLOW, COLOR_RED};

  /// @brief Tracks whether termination of a program upon invoking an error is
  /// enabled
  std::array<int32_t, 3> mTerminationEnabled = {0, 0, 0};
  /// @brief Array of actions to be invoked when a corresponding ErrorLevel is
  /// invoked
  std::array<std::function<void()>, 3> mActions;

  /// @brief Returns string representation of ErrorLevel
  /// @param level Corresponding ErrorLevel enum
  /// @return String representation of ErrorLevel
  std::string errorLevelToString(ErrorLevel level) const {
    switch (level) {
      case ErrorLevel::Info:
        return INFO_STRING;
        break;
      case ErrorLevel::Warning:
        return WARNING_STRING;
        break;
      case ErrorLevel::Fatal:
        return FATAL_STRING;
        break;
      default:
        assert(false &&
               "Encountered an unknown ErrorLevel in errorLevelToString");
        return "Unknown";  // to prevent compiler warnings
        break;
    }
  }
};
}  // namespace cse

#endif  // CSE_ERROR_MANAGER_CPP_