#ifndef CSE_ERROR_MANAGER_HPP_
#define CSE_ERROR_MANAGER_HPP_

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
                             ErrorLevel level = ErrorLevel::Info);
  /**
   * @brief Writes a message to console with a message type at the start of a
   * line
   *
   * @param message Message to be sent to user
   * @param level Error level of a message. Defaults to "Info" if not specified
   */
  void printMessage(const std::string& message,
                  ErrorLevel level = ErrorLevel::Info);
/**
 * @brief Prints an Info message
 * 
 * @param message message to be printed
 * @param line line number (optional)
 */
  void printInfo(const std::string& message, int32_t line = 0);
/**
 * @brief Prints a Warning message
 * 
 * @param message  message to be printed
 * @param line line number (optional)
 */
  void printWarning(const std::string& message, int32_t line = 0);
/**
 * @brief Prints a Fatal message
 * 
 * 
 * @param message message to be printed
 * @param line line number (optional)
 */
  
  void printError(const std::string& message, int32_t line = 0);

  /**
   * @brief Generic printMessage to print everything you pass in it
   * 
   * @tparam Ts Type pack
   * @param level ErrorLevel of a message
   * @param message list of parameters to be printer
   */
  template <typename... Ts>
  void printMessage(ErrorLevel level, Ts... message) {
    // this function was suggested by Dr. Ofria
    
    printMessage(0, level, std::forward<Ts>(message)...);
}

  /**
   * @brief Generic printMessage function to print everything you pass in it
   * 
   * @tparam Ts Parameter pack
   * @param line Line number in code
   * @param level ErrorLevel of a message
   * @param message Message (list of parameters) to be printer
   */
  template <typename... Ts>
  void printMessage(int32_t line, ErrorLevel level, Ts... message) {
    // this function was suggested by Dr. Ofria
    std::stringstream ss;
    (ss << ... << std::forward<Ts>(message));
    
    printMessage(line, ss.str(), level);
}
  /**
   * @brief Writes a message to console with a message type at line number
   *
   * @param line Line number where error occured
   * @param message Message to be sent to user
   * @param level Error level of a message. Defaults to "Info"
   */
  void printMessage(int32_t line, const std::string& message,
                  ErrorLevel level = ErrorLevel::Info) {
                    assert(!message.empty());
    
    /* This function is defined here because in
    tests I include .hpp, and redefine #exit
    for testing purposes */
    
    assert(static_cast<std::size_t>(level) < mStringColorCodes.size());
    assert(static_cast<std::size_t>(level) < mTerminationEnabled.size());

    std::stringstream ss;
    formatConsoleOutput(ss, line, message, level);

    std::string output = ss.str();
    std::cout << output;  // output error to the console

    // Format for logging into a file
    logToFile(output);

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
  void setAction(ErrorLevel level, const std::function<void()>& action);

  /**
   * @brief Constructs a new Error Manager object
   *
   * @param filePath Optional parameter for a file path where errors will be
   * logged
   */
  ErrorManager(const std::optional<std::string>& filePath = std::nullopt);

  /**
   * @brief Destroy the Error Manager object and close logging file if it was
   * opened
   *
   */
  ~ErrorManager();

  /**
   * @brief Allows to enable or disable coloring for ErrorLevel tag in console
   * output
   *
   * @param enabled Specifies whether to enable or disable coloring
   */
  void enableColors(bool enabled);

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
                         int32_t statusCode = 1);

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

  bool mColorsEnabled;

  /// @brief File for logging errors
  std::ofstream mLogFile;

  /// @brief Array that matches ErrorLevel to the corresponding ANSI color code
  std::array<std::string, 3> mStringColorCodes;

  /// @brief Tracks whether termination of a program upon invoking an error is
  /// enabled
  std::array<int32_t, 3> mTerminationEnabled;
  /// @brief Array of actions to be invoked when a corresponding ErrorLevel is
  /// invoked
  std::array<std::function<void()>, 3> mActions;

  /// @brief Returns string representation of ErrorLevel
  /// @param level Corresponding ErrorLevel enum
  /// @return String representation of ErrorLevel
  std::string errorLevelToString(ErrorLevel level) const;

  /**
   * @brief Helper function which logs output to a file
   * 
   * @param output String that will be logged
   */
  void logToFile(std::string& output);

  /**
   * @brief Helper function which formats console output into a stringstream
   * 
   * @param ss StringStream that the message will be written to
   * @param line Line number
   * @param message String message
   * @param level Error level of a message 
   */
  void formatConsoleOutput(std::stringstream& ss, 
    int32_t line, const std::string& message,
                  ErrorLevel level);
};

}  // namespace cse

#endif