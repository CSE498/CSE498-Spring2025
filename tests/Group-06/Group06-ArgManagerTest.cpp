#include <iostream>
#include <vector>
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-06/ArgManager/ArgManager.cpp"

TEST_CASE("ArgManager has no arguments", "[ArgManager]") {
    char *argVal []= {};
    int argC = 0;
    cse::ArgManager argManager(argC, argVal);

    SECTION("Has a argument");{
        //Make sure that there is expected behavior if there are no arguments provided
        bool hasCommand = argManager.HasArg("--Imaginary");
        REQUIRE(hasCommand == false);
    }    
}

TEST_CASE("ArgManager has a command", "[ArgManager]") {
    char *argVal []= {(char *)"--Test"};
    int argC = 1;
    cse::ArgManager argManager(argC, argVal);

    SECTION("Has a argument");{
        bool hasCommand = argManager.HasArg("--Test");
        REQUIRE(hasCommand == true);
    }

    SECTION("Does not have a argument")
    {
        bool hasArgument = argManager.HasArg("--Imaginary");
        REQUIRE(hasArgument == false);
    }
    
}

TEST_CASE("ArgManager GetOption", "[ArgManager]") {
    char *argVal []= {(char *)"--TestGetter"};
    int argC = 1;
    cse::ArgManager argManager(argC, argVal);

    SECTION("Successfully given output file"); 
    {
        // Set a default output filename, then Test if one was specified in the
        // command line arguments sent in.
        std::string out_filename="default_output.dat";
        if (argManager.HasArg("--TestGetter"))
            out_filename = argManager.GetSingleOption("--TestGetter");
        
        REQUIRE(out_filename != "default_output.dat");
    }

    SECTION("Option does not exist")
    {
        std::string out_filename="default_output.dat";
        if (argManager.HasArg("--DoesNotExist")) 
            out_filename = argManager.GetSingleOption("--DoesNotExist");
        
        REQUIRE(out_filename == "default_output.dat");
    }

    SECTION("Output file does not exist")
    {
        std::string out_filename="default_output.dat";
        if (argManager.HasArg("--TestGetter")) 
            out_filename = argManager.GetSingleOption("--TestGetter");
        
        REQUIRE(out_filename == "");
    }

    char *argVal2 []= {(char *)"--TestGetter", (char *)"success.dat"};
    int argC2 = 2;
    cse::ArgManager argManager2(argC2, argVal2);

    SECTION("Successfully given output file"); 
    {
        // Set a default output filename, then Test if one was specified in the
        // command line arguments sent in.
        std::string out_filename="default_output.dat";
        if (argManager2.HasArg("--TestGetter"))
            out_filename = argManager2.GetSingleOption("--TestGetter");
        
        REQUIRE(out_filename == "success.dat");
    }
}

TEST_CASE("ArgManager GetOptions", "[ArgManager]") {
    char *argVal [7]= {(char *)"--TestGetters", (char *)"5", (char *)"item1", (char *)"item2", (char *)"item3", (char *)"item4", (char *)"item5"};
    int argC = 7;
    cse::ArgManager argManager(argC, argVal);

    SECTION("Successfully given output list"); 
    {
        // Set a default output filename, then Test if one was specified in the
        // command line arguments sent in.
        std::vector<std::string> out_list= {"default_list"};
        if (argManager.HasArg("--TestGetters"))
        out_list = argManager.GetListOfOptions("--TestGetters");

        std::vector<std::string> correctOutput = { "item1", "item2", "item3", "item4", "item5"};
        REQUIRE(correctOutput.size() == out_list.size());

        REQUIRE(out_list[0] == correctOutput[0]);
        REQUIRE(out_list[1] == correctOutput[1]);
        REQUIRE(out_list[2] == correctOutput[2]);
        REQUIRE(out_list[3] == correctOutput[3]);
        REQUIRE(out_list[4] == correctOutput[4]);
    }

    SECTION("Option does not exist")
    {
        std::vector<std::string> out_list = {"default_list"};
        if (argManager.HasArg("--DoesNotExist")) 
        out_list = argManager.GetListOfOptions("--oesNotExist");
        
        REQUIRE((int)out_list.size() == 1);
        REQUIRE(out_list[0] == "default_list");
    }

    char *argVal2 []= {(char *)"--TestGetters", (char *)"7", (char *)"item1", (char *)"item2", (char *)"item3", (char *)"item4", (char *)"item5"};
    int argC2 = 7;
    cse::ArgManager argManager2(argC2, argVal2);

    SECTION("Not enough strings given for the size"); 
    {
        // Set a default output filename, then Test if one was specified in the
        // command line arguments sent in.
        std::vector<std::string> out_list= {"default_list"};
        if (argManager2.HasArg("--TestGetters"))
        out_list = argManager2.GetListOfOptions("--TestGetters");

        std::vector<std::string> correctOutput = { "item1", "item2", "item3", "item4", "item5"};
        REQUIRE(correctOutput.size() != out_list.size());
        REQUIRE(out_list[0] == "");
    }

    char *argVal3 [7]= {(char *)"--TestGetters", (char *)"NotAnInt", (char *)"item1", (char *)"item2", (char *)"item3", (char *)"item4", (char *)"item5"};
    int argC3 = 7;
    cse::ArgManager argManager3(argC3, argVal3);

    SECTION("a non integer was given for the list size"); 
    {
        std::vector<std::string> out_list= {"default_list"};
        if (argManager3.HasArg("--TestGetters"))
        out_list = argManager3.GetListOfOptions("--TestGetters");

        std::vector<std::string> correctOutput = { "item1", "item2", "item3", "item4", "item5"};
        REQUIRE(correctOutput.size() != out_list.size());
        //Argmanager should give a fallback return if no integer was provided
        REQUIRE(out_list[0] == "");
    }
}