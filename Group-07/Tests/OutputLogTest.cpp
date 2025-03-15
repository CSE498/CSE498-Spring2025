/*
* OutputLogTest.cpp
 */
//#include <gtest/gtest.h>
//#include "../Team07Library/OutputLog.h"
//#include <fstream>
//#include <cstdio>
//#include <cassert>
//#include <iostream>
//#include <string>
//
//// Test Constructor
//TEST(OutputLogTest, Construct) {
//    cse::OutputLog logger(cse::LogLevel::NORMAL, "test_log.txt");
//}
//
//// Test Normal Log Writing
//TEST(OutputLogTest, NormalLogging) {
//    cse::OutputLog logger(cse::LogLevel::NORMAL, "test_log.txt");
//    logger.log("This is a NORMAL log message.", cse::LogLevel::NORMAL);
//
//    std::ifstream logFile("test_log.txt");
//    std::string line;
//    bool found = false;
//
//    while (getline(logFile, line)) {
//        if (line == "This is a NORMAL log message.") {
//            found = true;
//            break;
//        }
//    }
//
//    ASSERT_TRUE(found);
//}
//
//
//// Test Debug Logging (Allowed when LogLevel is DEBUG)
//TEST(OutputLogTest, DebugLoggingAllowed) {
//    cse::OutputLog logger(cse::LogLevel::DEBUG, "test_log.txt");
//    logger.log("This is a DEBUG log message.", cse::LogLevel::DEBUG);
//
//    std::ifstream logFile("test_log.txt");
//    std::string line;
//    bool found = false;
//
//    while (getline(logFile, line)) {
//        if (line == "This is a DEBUG log message.") {
//            found = true;
//            break;
//        }
//    }
//
//    ASSERT_TRUE(found);
//}
//
//// Test File Opening Failure (Invalid Filename)
//
//
//// Test Destructor Properly Closes File
//TEST(OutputLogTest, DestructorClosesFile) {
//    std::string filename = "test_log.txt";
//    {
//        cse::OutputLog logger(cse::LogLevel::NORMAL, filename);
//    }
//    std::ifstream testFile(filename);
//    ASSERT_TRUE(testFile.good());  // File should be accessible
//}
//
//// Test Output to Console
//TEST(OutputLogTest, ConsoleOutput) {
//    cse::OutputLog logger(cse::LogLevel::NORMAL, "test_log.txt");
//
//    // Redirect std::cout
//    std::stringstream buffer;
//    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
//
//    logger.log("Console message", cse::LogLevel::NORMAL);
//
//    // Restore std::cout
//    std::cout.rdbuf(oldCout);
//
//    ASSERT_EQ(buffer.str(), "Console message\n");
//}
//
//
