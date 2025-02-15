#include <iostream>
#include <chrono>
#include <string>
#include <string_view>
#include "StaticString.hpp"


int main() {
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
        char ch = s[0];

        // Find a character
        std::size_t pos = s.find('o');

        // Append operations
        s.append(" appended");  // Append a C-string literal
        s.append("!");          // Append another C-string literal

        // Substring extraction (start index 0, length 5)
        std::string s_sub = s.substr(0, 5);

        // Get underlying C-string pointer
        const char* c_str = s.c_str();

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
        char ch = s[0];

        // Find a character
        std::size_t pos = s.find('o');

        // Append operations (using C-string literal and a single character)
        s.append(" appended");  // Append a C-string literal
        s.append('!');          // Append a single character

        // Substring extraction (start index 0, end index 5; returns a std::string_view)
        auto s_sub = s.substr(0, 5);

        // Get underlying C-string pointer
        const char* c_str = s.get_str();

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
    auto duration_static = duration_cast<milliseconds>(end_static - start_static).count();

    // ----------------------- Print the timing results -----------------------
    std::cout << "std::string operations took " << duration_std << " ms" << std::endl;
    std::cout << "StaticString operations took " << duration_static << " ms" << std::endl;

    return 0;
}



/*
CHAT-GPT USED TO UPGRADE THIS MAIN:
PROMPT:
    Can you give me a main function that compares both std::string and staticString class in terms of performance by doing same operations for each class?
    StaticString.hpp and main.cpp that we already had provided.

ANSWER:
    Below is an example main() function that performs the same operations using both std::string and your cse::StaticString class. It times the following operations in each iteration:

Construction from a C-string literal
Copy construction
Assignment (from another object)
Element access via operator[]
Finding a character
Appending a C-string literal and a single character
Extracting a substring (for std::string we use substr(), for StaticString we use your substr() method)
Retrieving the underlying C-string pointer
This version avoids using any extra temporary std::string or std::string_view objects beyond those operations that both types support.

cpp
Copy
#include <iostream>
#include <chrono>
#include <string>
#include "StaticString.hpp"  // Ensure this header uses your latest StaticString implementation

int main() {
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
        char ch = s[0];

        // Find a character
        std::size_t pos = s.find('o');

        // Append operations
        s.append(" appended");  // Append a C-string literal
        s.append("!");          // Append another C-string literal

        // Substring extraction (start index 0, length 5)
        std::string s_sub = s.substr(0, 5);

        // Get underlying C-string pointer
        const char* c_str = s.c_str();

        // (Optional) Perform a comparison operation
        bool eq = (s == s_copy);
        (void)eq;  // Avoid unused variable warning
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
        char ch = s[0];

        // Find a character
        std::size_t pos = s.find('o');

        // Append operations (using C-string literal and a single character)
        s.append(" appended");  // Append a C-string literal
        s.append('!');          // Append a single character

        // Substring extraction (start index 0, end index 5; returns a std::string_view)
        auto s_sub = s.substr(0, 5);

        // Get underlying C-string pointer
        const char* c_str = s.get_str();

        // (Optional) Perform a comparison operation
        bool eq = (s == s_copy);
        (void)eq;  // Avoid unused variable warning
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<milliseconds>(end_static - start_static).count();

    // ----------------------- Print the timing results -----------------------
    std::cout << "std::string operations took " << duration_std << " ms" << std::endl;
    std::cout << "StaticString operations took " << duration_static << " ms" << std::endl;

    return 0;
}
Explanation
std::string Block:

Constructs a string using a C-string literal.
Performs a copy construction and assignment.
Accesses the first character, finds the character 'o', appends two literals, extracts a substring of the first five characters, and retrieves the underlying C-string pointer.
StaticString Block:

Does the same operations using your cse::StaticString<128> class.
Note that appending a literal and a single character are available, and substr(0, 5) returns a std::string_view that is comparable in cost.
Both blocks are timed using std::chrono::high_resolution_clock to provide a performance comparison between std::string and your custom static string class.

*/