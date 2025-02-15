#include <iostream>
#include <vector>
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-06/ArgManager/ArgManager.cpp"

TEST_CASE("ArgManager has a command", "[ArgManager]") {
    char *argVal []= {"--Test"};
    int argC = 1;
    cse::ArgManager argManager(argC, argVal);

    SECTION("Has a argument");{
        bool hasCommand = argManager.Has("--Test");
        REQUIRE(hasCommand == true);
    }

    SECTION("Does not have a argument")
    {
        bool hasArgument = argManager.Has("--Imaginary");
        REQUIRE(hasArgument == false);
    }
    
}

TEST_CASE("ArgManager GetOption", "[ArgManager]") {
    char *argVal []= {"--TestGetter"};
    int argC = 1;
    cse::ArgManager argManager(argC, argVal);

    SECTION("Successfully given output file"); 
    {
        // Set a default output filename, then Test if one was specified in the
        // command line arguments sent in.
        std::string out_filename="default_output.dat";
        if (argManager.Has("--TestGetter"))
            out_filename = argManager.GetOption("-TestGetter");
        
        REQUIRE(out_filename != "default_output.dat");
    }

    SECTION("Option does not exist")
    {
        std::string out_filename="default_output.dat";
        if (argManager.Has("--DoesNotExist")) 
            out_filename = argManager.GetOption("-DoesNotExist");
        
        REQUIRE(out_filename == "default_output.dat");
    }
}