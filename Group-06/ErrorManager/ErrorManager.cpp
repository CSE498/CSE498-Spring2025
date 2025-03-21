/**
 * @file ErrorManager.cpp
 * @author Ivan Bega
 * @brief 
 * @version 0.1
 * @date 2025-02-17
 * 
 */

#include "ErrorManager.hpp"

namespace cse {


  void ErrorManager::executeAndHandleError(const std::function<void()>& function,
                             const std::string& message,
                             ErrorLevel level) {

    try {
      function();
    } catch (const std::exception& e) {
      printMessage(message, level);
    }
  }
  
  void ErrorManager::printMessage(const std::string& message,
                  ErrorLevel level) {
    printMessage(0, message, level);
  }

  void ErrorManager::printInfo(const std::string& message, int32_t line) {
    printMessage(line, message, ErrorLevel::Info);
  }

  void ErrorManager::printWarning(const std::string& message, int32_t line) {
    printMessage(line, message, ErrorLevel::Warning);
  }

  void ErrorManager::printError(const std::string& message, int32_t line) {
    printMessage(line, message, ErrorLevel::Fatal);
  }

  void ErrorManager::setAction(ErrorLevel level, const std::function<void()>& action) {
    assert(action);

    mActions[static_cast<int>(level)] = action;
  }

  
  ErrorManager::ErrorManager(const std::optional<std::string>& filePath) {
    mStringColorCodes = {COLOR_GREEN, COLOR_YELLOW, COLOR_RED};
    mTerminationEnabled = {0, 0, 0};
    mColorsEnabled = true;

    if (filePath.has_value()) {
      mLogFile.open(filePath.value(), std::ios::app);
      if (!mLogFile.is_open()) {
        std::cerr << "Unable to open log file: " << filePath.value()
                  << std::endl;
      }
    }
  }

 
  ErrorManager::~ErrorManager() {
    if (mLogFile.is_open()) {
      mLogFile.close();
    }
  }


  void ErrorManager::enableColors(bool enabled) { this->mColorsEnabled = enabled; }

  void ErrorManager::enableTermination(ErrorLevel level, bool enabled,
                         int32_t statusCode) {
    assert(statusCode >= 0);

    if (enabled) {
      mTerminationEnabled[static_cast<int>(level)] = statusCode;
    } else {
      mTerminationEnabled[static_cast<int>(level)] = 0;
    }
  }

 
  std::string ErrorManager::errorLevelToString(ErrorLevel level) const {
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

  void ErrorManager::logToFile(std::string& output) {
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
  }

 
  void ErrorManager::formatConsoleOutput(std::stringstream& ss, 
    int32_t line, const std::string& message,
                  ErrorLevel level) {
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
  }

}  // namespace cse