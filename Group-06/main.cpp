#include "ErrorManager/ErrorManager.cpp"
#include "StaticString/StaticString.hpp"
#include "StringSet/StringSet.hpp"
#include "CommandLine/CommandLine.cpp"
#include "ArgManager/ArgManager.h"
#include <iostream>
#include <chrono>
#include <string>
#include <string_view>

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
    cse::ErrorManager manager("text.log");
    manager.setAction(cse::ErrorManager::ErrorLevel::Warning, [] () {
        std::cout << "Additional action because we triggered Warning\n";
    });
    manager.printError("Test message error", cse::ErrorManager::ErrorLevel::Info);
    manager.printError("Test message error", cse::ErrorManager::ErrorLevel::Warning);
    manager.printError("Test message error", cse::ErrorManager::ErrorLevel::Fatal);
    manager.printError(34, "Test message error", cse::ErrorManager::ErrorLevel::Fatal);
    manager.enableColors(false);
    manager.printError("Message with disabled colors", cse::ErrorManager::ErrorLevel::Info);
}

void runStaticString() {
    
    const int iterations = 100000;  // Adjust iteration count as needed 

    using namespace std::chrono;

    // ----------------------- std::string OPERATIONS -----------------------
    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        // Construct from C-string literal
        std::string s("Hello, World!");
        // Copy construction
        std::string s_copy(s);
        // Assignment operator (from another string)
        std::string s_assigned;
        s_assigned = s;

        // Element access using operator[]
        [[maybe_unused]] char ch = s[0];

        // Find a character
        [[maybe_unused]] std::size_t pos = s.find('o');

        // Append operations
        s.append(" appended");  // Append a C-string literal
        s.append("!");          // Append another C-string literal

        // Substring extraction (start index 0, length 5)
        std::string s_sub = s.substr(0, 5);

        // Get underlying C-string pointer
        [[maybe_unused]] const char* c_str = s.c_str();

        // (Optional) Perform a comparison operation
        bool eq = (s == s_copy);
        bool ne = (s != s_copy);
        bool lt = (s < s_copy);
        bool gt = (s > s_copy);
        bool le = (s <= s_copy);
        bool ge = (s >= s_copy);
        (void)eq;  // Avoid unused variable warning
        (void)ne;  // Avoid unused variable warning
        (void)lt;  // Avoid unused variable warning
        (void)gt;  // Avoid unused variable warning
        (void)le;  // Avoid unused variable warning
        (void)ge;  // Avoid unused variable warning
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<milliseconds>(end_std - start_std).count();

    // --------------------- StaticString OPERATIONS ------------------------
    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        // Construct from C-string literal
        cse::StaticString<128> s("Hello, World!");
        // Copy construction
        cse::StaticString<128> s_copy(s);
        // Assignment operator (from another StaticString)
        cse::StaticString<128> s_assigned;
        s_assigned = s;

        // Element access using operator[]
        [[maybe_unused]] char ch = s[0];

        // Find a character
        [[maybe_unused]] std::size_t pos = s.find('o');

        // Append operations (using C-string literal and a single character)
        s.append(" appended");  // Append a C-string literal
        s.append('!');          // Append a single character

        // Substring extraction (start index 0, end index 5; returns a
        // std::string_view)
        [[maybe_unused]] auto s_sub = s.substr(0, 5);

        // Get underlying C-string pointer
        [[maybe_unused]] const char* c_str = s.get_str();

        // (Optional) Perform a comparison operation
        bool eq = (s == s_copy);
        bool ne = (s != s_copy);
        bool lt = (s < s_copy);
        bool gt = (s > s_copy);
        bool le = (s <= s_copy);
        bool ge = (s >= s_copy);
        (void)eq;  // Avoid unused variable warning
        (void)ne;  // Avoid unused variable warning
        (void)lt;  // Avoid unused variable warning
        (void)gt;  // Avoid unused variable warning
        (void)le;  // Avoid unused variable warning
        (void)ge;  // Avoid unused variable warning
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static =
        duration_cast<milliseconds>(end_static - start_static).count();

    // ----------------------- Print the timing results -----------------------
    std::cout << "std::string operations took " << duration_std << " ms"
                << std::endl;
    std::cout << "StaticString operations took " << duration_static << " ms"
                << std::endl;
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

    if (args.HasArg("-h") || args.HasArg("--help")) {
        args.PrintHelp();
        exit(0);
    }
    // Set a default output filename, then Test if one was specified in the
    // command line arguments sent in.
    std::string out_filename="default_output.dat";
    if (args.HasArg("-o")) out_filename = args.GetSingleOption("-o");

    std::cout << "File Name sent out: " << out_filename << "\n";

    std::vector<std::string> out_list = {"Default list"};
    if (args.HasArg("-l")) out_list = args.GetListOfOptions("-l");
    for (int i = 0 ; i < (int)out_list.size(); i++)
    {
        if (i == 0)
        {
            std::cout << "List: ";
        }
        std::cout << out_list[i];
        if (i < (int)out_list.size() - 1)
        {
            std::cout << ", ";
        }
        else{
            std::cout << "\n";
        }
    }

    cse::ArgManager manager(argc, argv);
    std::cout << "Did you pass an argument 'cat' when running executable?: ";
    if (manager.HasArg("cat"))
        std::cout << "yes\n";
    else
        std::cout << "no\n";

}