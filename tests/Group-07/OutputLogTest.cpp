/**
 * @file OutputLogTest.cpp
 * @author trang
 */
#include <sstream>

#include "../../Group-07/Team07Library/OutputLog.h"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
// Test construction of the logger object.
TEST_CASE("OutputLogTest Construction", "[OutputLog]") {
  cse::OutputLog logger(cse::LogLevel::NORMAL, "test_log.txt");
}

// Test Normal Log Writing
TEST_CASE("OutputLogTest Normal Logging", "[OutputLog]") {
  cse::OutputLog logger(cse::LogLevel::NORMAL, "test_log.txt");
  logger.log("This is a NORMAL log message.", cse::LogLevel::NORMAL);

  std::ifstream logFile("test_log.txt");
  std::string line;
  bool found = false;

  while (getline(logFile, line)) {
    // Since each line now starts with a timestamp, we check if the expected
    // message is a substring.
    if (line.find("This is a NORMAL log message.") != std::string::npos) {
      found = true;
      break;
    }
  }
  REQUIRE(found == true);
}

// Test Debug Logging (Allowed when LogLevel is DEBUG)
TEST_CASE("OutputLogTest Debug Logging", "[OutputLog]") {
  cse::OutputLog logger(cse::LogLevel::DEBUG, "test_log.txt");
  logger.log("This is a DEBUG log message.", cse::LogLevel::DEBUG);

  std::ifstream logFile("test_log.txt");
  std::string line;
  bool found = false;

  while (getline(logFile, line)) {
    if (line.find("This is a DEBUG log message.") != std::string::npos) {
      found = true;
      break;
    }
  }
  REQUIRE(found == true);
}

// Test File Opening Failure (Invalid Filename)

// Test Destructor Properly Closes File
TEST_CASE("OutputLogTest Destructor", "[OutputLog]") {
  std::string filename = "test_log.txt";
  {
    cse::OutputLog logger(cse::LogLevel::NORMAL, filename);
  }
  std::ifstream testFile(filename);
  REQUIRE(testFile.good() ==
          true);  // File should be accessible after logger destruction
}

// Test Output to Console
TEST_CASE("OutputLogTest Console", "[OutputLog]") {
  cse::OutputLog logger(cse::LogLevel::NORMAL, "test_log.txt");

  std::stringstream buffer;
  std::streambuf* oldCout =
      std::cout.rdbuf(buffer.rdbuf());  // Redirect std::cout

  logger.log("Console message", cse::LogLevel::NORMAL);

  std::cout.rdbuf(oldCout);  // Restore std::cout

  std::string output = buffer.str();
  // Check that the output contains the message (timestamp will precede it)
  REQUIRE(output.find("Console message") != std::string::npos);
}
// Test that SILENT logging mode results in no output (neither to file nor to
// console)
TEST_CASE("OutputLogTest Silent Logging", "[OutputLog]") {
  std::string filename = "silent_test_log.txt";
  cse::OutputLog logger(cse::LogLevel::SILENT, filename);

  // Redirect console output
  std::stringstream consoleBuffer;
  std::streambuf* oldCout = std::cout.rdbuf(consoleBuffer.rdbuf());

  logger.log("This message should not appear", cse::LogLevel::NORMAL);

  std::cout.rdbuf(oldCout);  // Restore std::cout

  // Verify that nothing was output to the console.
  REQUIRE(consoleBuffer.str().empty());

  // Verify that nothing was written to the file.
  std::ifstream logFile(filename);
  std::string fileLine;
  bool anyContent = false;
  while (getline(logFile, fileLine)) {
    if (!fileLine.empty()) {
      anyContent = true;
      break;
    }
  }
  REQUIRE(anyContent == false);
}

// Test VERBOSE logging: when log level is VERBOSE, NORMAL and VERBOSE messages
// should be logged, but DEBUG messages should be omitted.
TEST_CASE("OutputLogTest Verbose Logging", "[OutputLog]") {
  std::string filename = "verbose_test_log.txt";
  cse::OutputLog logger(cse::LogLevel::VERBOSE, filename);

  logger.log("Normal message", cse::LogLevel::NORMAL);    // Expected to log.
  logger.log("Verbose message", cse::LogLevel::VERBOSE);  // Expected to log.
  logger.log("Debug message", cse::LogLevel::DEBUG);  // Expected NOT to log.

  std::ifstream logFile(filename);
  std::string line;
  bool foundNormal = false;
  bool foundVerbose = false;
  bool foundDebug = false;

  while (getline(logFile, line)) {
    if (line.find("Normal message") != std::string::npos) foundNormal = true;
    if (line.find("Verbose message") != std::string::npos) foundVerbose = true;
    if (line.find("Debug message") != std::string::npos) foundDebug = true;
  }

  REQUIRE(foundNormal == true);
  REQUIRE(foundVerbose == true);
  REQUIRE(foundDebug == false);
}

// Test that a timestamp is correctly prepended to the log message.
TEST_CASE("OutputLogTest Timestamp", "[OutputLog]") {
  std::string filename = "timestamp_test_log.txt";
  cse::OutputLog logger(cse::LogLevel::NORMAL, filename);

  logger.log("Timestamp test message", cse::LogLevel::NORMAL);

  std::ifstream logFile(filename);
  std::string line;
  bool validTimestamp = false;

  if (getline(logFile, line)) {
    // Check that the line starts with '['.
    if (!line.empty() && line.front() == '[') {
      // Find the closing bracket of the timestamp.
      size_t closingBracketPos = line.find(']');
      if (closingBracketPos != std::string::npos && closingBracketPos > 0) {
        // Verify that after the timestamp the expected message is present.
        if (line.find("Timestamp test message", closingBracketPos) !=
            std::string::npos) {
          validTimestamp = true;
        }
      }
    }
  }
  REQUIRE(validTimestamp == true);
}