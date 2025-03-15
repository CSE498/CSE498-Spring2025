// OutputLog.hpp
// Author: Bao Tran
// Description: A logging system with multiple verbosity levels
// Created for the Euler Group Project (CSE498-Spring2025)
//
// Some parts of this implementation were generated with the assistance of
// ChatGPT (OpenAI). Date of ChatGPT Assistance: 2/3/2025
#ifndef OUTPUT_LOG_HPP
#define OUTPUT_LOG_HPP

#include <cassert>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Namespace for the CSE logging utilities.
 */
namespace cse {

/**
 * @brief Log levels for controlling message verbosity.
 */
enum class LogLevel {
  SILENT,  /**< No logging output */
  NORMAL,  /**< Standard logging output */
  VERBOSE, /**< Detailed logging output */
  DEBUG    /**< Debug-level logging output */
};

/**
 * @brief A logging system that writes messages to both console and a file.
 *
 * This class handles logging messages with a timestamp. It supports different
 * verbosity levels and writes log messages to a file (opened in append mode).
 */
class OutputLog {
 private:
  LogLevel level;        /**< Current logging verbosity level */
  std::ofstream logFile; /**< Output file stream for logging */

  bool consoleOutput = true; /**< Flag to enable or disable console logging */

  /**
   * @brief Retrieves the current time as a formatted string.
   *
   * @return A string representing the current time in the format "[YYYY-MM-DD
   * HH:MM:SS] ".
   */
  std::string getCurrentTime() const {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time), "[%Y-%m-%d %H:%M:%S] ");
    return oss.str();
  }

 public:
  /**
   * @brief Constructs an OutputLog object and opens the specified log file.
   *
   * The log file is opened in append mode. An assertion ensures that the file
   * is opened successfully.
   *
   * @param logLevel The initial log verbosity level.
   * @param filename The name of the log file.
   */
  OutputLog(LogLevel logLevel, const std::string& filename) : level(logLevel) {
    logFile.open(filename, std::ios::app);  // Open file in append mode
    assert(logFile.is_open() && "Error: Could not open log file!");
  }

  /**
   * @brief Destructor that closes the log file if it is open.
   */
  ~OutputLog() {
    if (logFile.is_open()) {
      logFile.close();
    }
  }

  /**
   * @brief Logs a message if its log level is within the allowed verbosity.
   *
   * The message is prefixed with the current time. Depending on the
   * configuration, the message is output to both the console and the log file.
   *
   * @tparam T The type of the message (should support stream insertion).
   * @param message The message to log.
   * @param msgLevel The verbosity level of the message.
   */
  template <typename T>
  void log(const T& message, LogLevel msgLevel) {
    if (level == LogLevel::SILENT) {
      return;
    }

    if (static_cast<int>(msgLevel) > static_cast<int>(level)) {
      return;  // Ignore messages above the current log level
    }

    std::ostringstream oss;
    oss << getCurrentTime() << message;
    std::string logMessage = oss.str();

    if (consoleOutput) {
      std::cout << logMessage << std::endl;
    }

    if (logFile.is_open()) {
      logFile << logMessage << std::endl;
      assert(logFile.good() && "Error: Failed to write to log file!");
    }
  }

  /**
   * @brief Sets a new logging verbosity level.
   *
   * @param newLevel The new log verbosity level.
   */
  void setLogLevel(LogLevel newLevel) { level = newLevel; }

  /**
   * @brief Enables or disables console output for log messages.
   *
   * @param enable Set to true to enable console output; false to disable.
   */
  void enableConsoleOutput(bool enable) { consoleOutput = enable; }
};

}  // namespace cse

#endif  // OUTPUT_LOG_HPP