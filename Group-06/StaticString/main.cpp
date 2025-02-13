#include <iostream>
#include <chrono>
#include <string>
#include "StaticString.hpp"

int main() {
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
    return 0;
}