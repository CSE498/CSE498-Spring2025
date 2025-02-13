/**
 * @file OutputLogTest.cpp
 * @author trang
 */
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-07/Team07Library/OutputLog.h"
#include <sstream>
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
        if (line == "This is a NORMAL log message.") {
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
        if (line == "This is a DEBUG log message.") {
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
    REQUIRE(testFile.good() == true);  // File should be accessible
}

// Test Output to Console
TEST_CASE("OutputLogTest Console", "[OutputLog]") {
  	cse::OutputLog logger(cse::LogLevel::NORMAL, "test_log.txt");

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf()); // Redirect std::cout

    logger.log("Console message", cse::LogLevel::NORMAL);

    std::cout.rdbuf(oldCout); // Restore std::cout

    REQUIRE(buffer.str()== "Console message\n"); // Compare output
}