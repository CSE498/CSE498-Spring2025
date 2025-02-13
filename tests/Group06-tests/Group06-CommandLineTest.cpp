#include <string>
#include <iostream>
#include <sstream>
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-06/CommandLine/CommandLine.cpp"

TEST_CASE("CommandLine addCommand and executeCommand", "[CommandLine]") {
    cse::CommandLine cli;

    bool commandExecuted = false;
    cli.addCommand("test", [&]() { commandExecuted = true; });

    SECTION("Execute existing command") {
        cli.executeCommand("test");
        REQUIRE(commandExecuted == true);
    }

    SECTION("Execute non-existing command") {
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        cli.executeCommand("nonexistent");

        std::cout.rdbuf(p_cout_streambuf);
        REQUIRE(oss.str() == "Unknown command: nonexistent\n");
    }
}

TEST_CASE("CommandLine trackHistory and printHistory", "[CommandLine]") {
    cse::CommandLine cli;

    cli.trackHistory("command1");
    cli.trackHistory("command2");

    SECTION("Print history") {
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        cli.printHistory();

        std::cout.rdbuf(p_cout_streambuf);
        REQUIRE(oss.str() == "command1\ncommand2\n");
    }
}

TEST_CASE("CommandLine trackState and getState", "[CommandLine]") {
    cse::CommandLine cli;

    cli.trackState("state1");
    REQUIRE(cli.getState() == "state1");

    cli.trackState("state2");
    REQUIRE(cli.getState() == "state2");
}

TEST_CASE("CommandLine add multiple commands and execute", "[CommandLine]") {
    cse::CommandLine cli;

    bool command1Executed = false;
    bool command2Executed = false;

    cli.addCommand("command1", [&]() { command1Executed = true; });
    cli.addCommand("command2", [&]() { command2Executed = true; });

    SECTION("Execute command1") {
        cli.executeCommand("command1");
        REQUIRE(command1Executed == true);
        REQUIRE(command2Executed == false);
    }

    SECTION("Execute command2") {
        cli.executeCommand("command2");
        REQUIRE(command1Executed == false);
        REQUIRE(command2Executed == true);
    }
}

TEST_CASE("CommandLine track and print empty history", "[CommandLine]") {
    cse::CommandLine cli;

    SECTION("Print empty history") {
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        cli.printHistory();

        std::cout.rdbuf(p_cout_streambuf);
        REQUIRE(oss.str().empty());
    }
}