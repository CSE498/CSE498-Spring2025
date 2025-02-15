#include "ErrorManager/ErrorManager.cpp"
#include "StaticString/StaticString.hpp"
#include "StringSet/StringSet.h"
#include "CommandLine/CommandLine.cpp"
#include "ArgManager/ArgManager.h"
#include <iostream>
#include <chrono>
#include <string>

void runErrorManager();
void runStaticString();
void runStringSet();
void runCommandLine();
void runArgManager(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    std::cout << "--------------------------------------------";
    std::cout << "\nRunning ErrorManager class\n\n";
    runErrorManager();
    std::cout << "--------------------------------------------";
    std::cout << "\nRunning StaticString class\n\n";
    runStaticString();
    std::cout << "--------------------------------------------";
    std::cout << "\nRunning StringSet class\n\n";
    runStringSet();
    std::cout << "--------------------------------------------";
    std::cout << "\nRunning CommandLine class\n\n";
    runCommandLine();
    std::cout << "--------------------------------------------";
    std::cout << "\nRunning ArgManager class\n\n";
    runArgManager(argc, argv);
}


void runErrorManager() {
    cse::ErrorManager manager;
    manager.setAction(cse::ErrorManager::ErrorLevel::Warning, [] () {
        std::cout << "Additional action because we triggered Warning\n";
    });
    manager.printError("Test message error", cse::ErrorManager::ErrorLevel::Info);
    manager.printError("Test message error", cse::ErrorManager::ErrorLevel::Warning);
    manager.printError("Test message error", cse::ErrorManager::ErrorLevel::Fatal);
    manager.printError(34, "Test message error", cse::ErrorManager::ErrorLevel::Fatal);
    manager.enableColors(false);
    manager.printError("Message with disabled colors (to be fixed)", cse::ErrorManager::ErrorLevel::Info);
}

void runStaticString() {
    const int iterations = 1000000;  

    using namespace std::chrono;

    // Test to time both std::String and StaticString to see performance differance
    // ----------------------------STD::STRING----------------------------------
    
    // Start the timing
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        std::string s = "Hello, World!";
        std::string s_copy = s; 
        std::string s_assigned;
        s_assigned = s; 

        std::size_t pos = s.find('!');
        char c = s[0];
        std::size_t length = s.length();
        std::size_t size = s.size();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start).count();


    // ----------------------------STATICSTRING---------------------------------
    
    // Start the timing
    auto start_static = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        cse::StaticString<128> s("Hello, World!");
        cse::StaticString<128> s_copy(s);
        cse::StaticString<128> s_assigned;
        s_assigned = s;

        std::size_t pos = s.find('!');
        char c = s[0];
        std::size_t length = s.length();
        std::size_t size = s.size();
    }

    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<milliseconds>(end_static - start_static).count();

   
    std::cout << "std::string operations took " << duration << " ms" << "\n";
    std::cout << "StaticString operations took " << duration_static << " ms" << std::endl;
}


void runStringSet() {
    cse::StringSet set1, set2;

    set1.insert("yellow");
    set1.insert("blue");
    set1.insert("black");

    set2.insert("yellow");
    set2.insert("blue");
    set2.insert("purple");

    std::cout << "Size for set1: " << set1.size() << "(yellow, blue and black)" << std::endl;
    std::cout << "Size for set2: " << set2.size() << "(yellow, blue and purple)" << std::endl;

    cse::StringSet setUnion = set1.Union(set2);
    std::cout << "Size of Union Set: " << setUnion.size() << "(yellow, blue, black and purple)" << std::endl;

    cse::StringSet setIntersection = set1.Intersection(set2);
    std::cout << "Size of Intersection set: " << setIntersection.size() << "(yellow and blue)" << std::endl;

    set1.clear();
    std::cout << "check if .clear() make our set empty: " << set1.size() << "(size)" << std::endl;
    std::cout << set1.empty() << std::endl;

    set2.erase("blue");
    std::cout << "check if .erase() deleted blue from the set2: " << set2.size() << "(yellow and purple)" << std::endl;
}


void runCommandLine() {
    cse::CommandLine cmd;

    // Add some commands
    cmd.addCommand("greet", []() { std::cout << "Hello, World!" << std::endl; });
    cmd.addCommand("farewell", []() { std::cout << "Goodbye, World!" << std::endl; });

    // Execute commands
    cmd.executeCommand("greet");
    cmd.executeCommand("farewell");
    cmd.executeCommand("unknown"); // This should print "Unknown command: unknown"

    // Track and print history
    cmd.trackHistory("greet");
    cmd.trackHistory("farewell");
    cmd.printHistory();

    // Track and get state
    cmd.trackState("active");
    std::cout << "Current state: " << cmd.getState() << std::endl;
}

void runArgManager(int argc, char* argv[]) {
    cse::ArgManager args(argc, argv);  // Pass input args into manager for processing.
    // after run, make command
    // run "./Lamport.exe --help" this will trigger help arguments

    if (args.Has("-h") || args.Has("--help")) {
        args.PrintHelp();
        exit(0);
    }
    // Set a default output filename, then Test if one was specified in the
    // command line arguments sent in.
    std::string out_filename="default_output.dat";
    if (args.Has("-o")) out_filename = args.GetOption("-o");


    cse::ArgManager manager(argc, argv);
    std::cout << "Did you pass an argument 'cat' when running executable?: ";
    if (manager.Has("cat"))
        std::cout << "yes\n";
    else
        std::cout << "no\n";

}