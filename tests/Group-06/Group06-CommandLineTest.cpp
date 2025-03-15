#include <string>
#include <iostream>
#include <sstream>
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-06/CommandLine/CommandLine.cpp"

// Test case for adding and executing commands
TEST_CASE("CommandLine addCommand and executeCommand", "[CommandLine]") {
    cse::CommandLine cli;

    bool commandExecuted = false;
    cli.addCommand("test", [&]() { commandExecuted = true; });

    // Test executing an existing command
    SECTION("Execute existing command") {
        cli.executeCommand("test");
        REQUIRE(commandExecuted == true);
    }

    // Test executing a non-existing command
    SECTION("Execute non-existing command") {
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        cli.executeCommand("nonexistent");

        std::cout.rdbuf(p_cout_streambuf);
        REQUIRE(oss.str() == "Unknown command: nonexistent\n");
    }
}

// Test case for tracking and printing command history
TEST_CASE("CommandLine trackHistory and printHistory", "[CommandLine]") {
    cse::CommandLine cli;

    cli.trackHistory("command1");
    cli.trackHistory("command2");

    // Test printing the command history
    SECTION("Print history") {
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        cli.printHistory();

        std::cout.rdbuf(p_cout_streambuf);
        REQUIRE(oss.str() == "command1\ncommand2\n");
    }
}

// Test case for tracking and getting the current state
TEST_CASE("CommandLine trackState and getState", "[CommandLine]") {
    cse::CommandLine cli;

    cli.trackState("state1");
    REQUIRE(cli.getState() == "state1");

    cli.trackState("state2");
    REQUIRE(cli.getState() == "state2");
}

// Test case for adding multiple commands and executing them
TEST_CASE("CommandLine add multiple commands and execute", "[CommandLine]") {
    cse::CommandLine cli;

    bool command1Executed = false;
    bool command2Executed = false;

    cli.addCommand("command1", [&]() { command1Executed = true; });
    cli.addCommand("command2", [&]() { command2Executed = true; });

    // Test executing the first command
    SECTION("Execute command1") {
        cli.executeCommand("command1");
        REQUIRE(command1Executed == true);
        REQUIRE(command2Executed == false);
    }

    // Test executing the second command
    SECTION("Execute command2") {
        cli.executeCommand("command2");
        REQUIRE(command1Executed == false);
        REQUIRE(command2Executed == true);
    }
}

// Test case for printing an empty command history
TEST_CASE("CommandLine track and print empty history", "[CommandLine]") {
    cse::CommandLine cli;

    // Test printing the history when it is empty
    SECTION("Print empty history") {
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        cli.printHistory();

        std::cout.rdbuf(p_cout_streambuf);
        REQUIRE(oss.str().empty());
    }
}

// Test case for clearing the command history
TEST_CASE("CommandLine clearHistory", "[CommandLine]") {
    cse::CommandLine cli;

    cli.trackHistory("command1");
    cli.trackHistory("command2");

    // Test clearing the command history
    SECTION("Clear history") {
        cli.clearHistory();
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        cli.printHistory();

        std::cout.rdbuf(p_cout_streambuf);
        REQUIRE(oss.str().empty());
    }
}

// Test case for the help command
TEST_CASE("CommandLine help command", "[CommandLine]") {
    cse::CommandLine cli;

    cli.addCommand("test", []() {}, "A test command");

    // Test printing the help message
    SECTION("Print help") {
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        cli.executeCommand("help");

        std::cout.rdbuf(p_cout_streambuf);
        REQUIRE(oss.str() == "Available commands:\nhelp - Displays this help message\ntest - A test command\n");
    }
}