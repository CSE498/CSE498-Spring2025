#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cctype>

#include "StaticString.hpp"
#include "../StringSet/StringSet.hpp"

//CITE: https://chatgpt.com/share/67d78a2c-17a4-800e-b4f6-d9a48297fa9e
int main() {
  const int iterations = 100000;  // number of iterations for each test
  using namespace std::chrono;
  // TEST -----------------
  std::unordered_set<cse::StaticString<10>> myMap;
  cse::StaticString<10> s("Hello");
  myMap.insert(s);

  for(auto i : myMap)
  {
    std::cout << i.get_str() << std::endl;
  }

  cse::StringSet<cse::StaticString<10>> mySet;
  mySet.insert(s);

  std::cout << "MYSET PRINT: \n";
  
  for(auto i : mySet) {
    std::cout << i.get_str() << std::endl;
  }

  // cse::StaticString<10> s("Hello");

  // s.resize(20);
  // std::cout << "TEST DONE!\n"; 

  // Test 1: Construction, Copy, Assignment, and Element Access
  {
    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("Hello, World!");
      std::string s_copy(s);
      std::string s_assigned;
      s_assigned = s;
      volatile char ch = s[0]; // volatile to avoid optimization
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("Hello, World!");
      cse::StaticString<128> s_copy(s);
      cse::StaticString<128> s_assigned;
      s_assigned = s;
      volatile char ch = s[0];
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "Test 1: Construction, Copy, Assignment, Element Access\n";
    std::cout << "std::string:  " << duration_std << " microseconds\n";
    std::cout << "StaticString: " << duration_static << " microseconds\n";
  }

  // Test 2: Append Operations
  {
    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("Hello");
      s.append(", World");
      s.push_back('!');
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("Hello");
      s.append(", World");
      s.append('!');
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "\nTest 2: Append Operations\n";
    std::cout << "std::string:  " << duration_std << " microseconds\n";
    std::cout << "StaticString: " << duration_static << " microseconds\n";
  }

  // Test 3: Find Operations
  {
    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("Hello, World!");
      volatile size_t pos1 = s.find('o');
      volatile size_t pos2 = s.find("World");
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("Hello, World!");
      volatile size_t pos1 = s.find('o');
      volatile size_t pos2 = s.find("World");
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "\nTest 3: Find Operations\n";
    std::cout << "std::string:  " << duration_std << " microseconds\n";
    std::cout << "StaticString: " << duration_static << " microseconds\n";
  }

  // Test 4: Insert Operations
  {
    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("HelloWorld");
      s.insert(5, ", ");
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("HelloWorld");
      s.insert(", ", 5);
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "\nTest 4: Insert Operations\n";
    std::cout << "std::string:  " << duration_std << " microseconds\n";
    std::cout << "StaticString: " << duration_static << " microseconds\n";
  }

  // Test 5: Remove/Erase Operations
  {
    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("Hello, World!");
      s.erase(5, 2);  // remove ", "
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("Hello, World!");
      s.remove(5, 7);  // remove two characters (indexes 5 to 6)
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "\nTest 5: Remove/Erase Operations\n";
    std::cout << "std::string:  " << duration_std << " microseconds\n";
    std::cout << "StaticString: " << duration_static << " microseconds\n";
  }

  // Test 6: Replace Operations
  {
    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("Hello, World!");
      size_t pos = s.find("World");
      if (pos != std::string::npos) {
        s.replace(pos, 5, "Universe");
      }
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("Hello, World!");
      s.replace("World", "Universe");
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "\nTest 6: Replace Operations\n";
    std::cout << "std::string:  " << duration_std << " microseconds\n";
    std::cout << "StaticString: " << duration_static << " microseconds\n";
  }

  // Test 7: Split Operations
  {
    // Custom split for std::string (since there is no built-in one)
    auto split_string = [](const std::string& s, char delimiter) -> std::vector<std::string> {
      std::vector<std::string> result;
      size_t start = 0, end = 0;
      while ((end = s.find(delimiter, start)) != std::string::npos) {
        result.push_back(s.substr(start, end - start));
        start = end + 1;
      }
      result.push_back(s.substr(start));
      return result;
    };

    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("one,two,three,four");
      auto parts = split_string(s, ',');
      volatile size_t dummy = parts.size();
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("one,two,three,four");
      auto parts = s.split(',');
      volatile size_t dummy = parts.size();
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "\nTest 7: Split Operations\n";
    std::cout << "std::string (custom): " << duration_std << " microseconds\n";
    std::cout << "StaticString:         " << duration_static << " microseconds\n";
  }

  // Test 8: Transform Operations (convert to uppercase)
  {
    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("Hello, World!");
      std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("Hello, World!");
      s.transform([](char c) { return static_cast<char>(std::toupper(c)); });
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "\nTest 8: Transform Operations (Uppercase)\n";
    std::cout << "std::string:  " << duration_std << " microseconds\n";
    std::cout << "StaticString: " << duration_static << " microseconds\n";
  }

  // Test 9: Character Count
  {
    auto char_count_std = [](const std::string& s) -> std::unordered_map<char, size_t> {
      std::unordered_map<char, size_t> counts;
      for (char c : s) {
        counts[c]++;
      }
      return counts;
    };

    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("Hello, World!");
      auto counts = char_count_std(s);
      volatile size_t dummy = counts.size();
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("Hello, World!");
      auto counts = s.char_count();
      volatile size_t dummy = counts.size();
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "\nTest 9: Character Count Operations\n";
    std::cout << "std::string (custom): " << duration_std << " microseconds\n";
    std::cout << "StaticString:         " << duration_static << " microseconds\n";
  }

  // Test 10: findAll and rFind Operations
  {
    auto findAll_std = [](const std::string& s, const std::string& sub) -> std::vector<size_t> {
      std::vector<size_t> indices;
      size_t pos = s.find(sub);
      while (pos != std::string::npos) {
        indices.push_back(pos);
        pos = s.find(sub, pos + 1);
      }
      return indices;
    };

    auto rFind_std = [&findAll_std](const std::string& s, const std::string& sub) -> std::vector<size_t> {
      auto indices = findAll_std(s, sub);
      std::reverse(indices.begin(), indices.end());
      return indices;
    };

    auto start_std = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      std::string s("ababababab");
      auto indices1 = findAll_std(s, "ab");
      auto indices2 = rFind_std(s, "ab");
      volatile size_t dummy = indices1.size() + indices2.size();
    }
    auto end_std = high_resolution_clock::now();
    auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

    auto start_static = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
      cse::StaticString<128> s("ababababab");
      auto indices1 = s.findAll("ab");
      auto indices2 = s.rFind("ab");
      volatile size_t dummy = indices1.size() + indices2.size();
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<microseconds>(end_static - start_static).count();

    std::cout << "\nTest 10: findAll and rFind Operations\n";
    std::cout << "std::string (custom): " << duration_std << " microseconds\n";
    std::cout << "StaticString:         " << duration_static << " microseconds\n";
  }

  return 0;
}


// int main() {
//   const int iterations = 100000;  // Adjust iteration count as needed

//   using namespace std::chrono;

//   //----------------------------------------------------------------------------
//   cse::StaticString<40> s("hello world");

//    [[maybe_unused]]auto val = s.find('h'); // 0
//    [[maybe_unused]]auto val2 = s.find('o'); // 4

//    [[maybe_unused]]auto val3 = s.find("hello"); // 0
//    [[maybe_unused]]auto val4 = s.find("world"); // 6
//    [[maybe_unused]]auto val5 = s.find("xyz"); // npos

//    [[maybe_unused]]auto val6 = s.find(std::string("hello")); // 0
//    [[maybe_unused]]auto val7 = s.find(std::string("world")); // 6
//    [[maybe_unused]]auto val8 = s.find(std::string("xyz")); // npos

//    [[maybe_unused]]auto val9 = s.find(std::string_view("hello")); // 0
//    [[maybe_unused]]auto val10 = s.find(std::string_view("world")); // 6
//    [[maybe_unused]]auto val11 = s.find(std::string_view("xyz")); // npos

//   //----------------------------------------------------------------------------
//   // ----------------------- std::string OPERATIONS -----------------------
//   auto start_std = high_resolution_clock::now();
//   for (int i = 0; i < iterations; ++i) {
//     // Construct from C-string literal
//     std::string s("Hello, World!");
//     // Copy construction
//     std::string s_copy(s);
//     // Assignment operator (from another string)
//     std::string s_assigned;
//     s_assigned = s;

//     // Element access using operator[]
//     [[maybe_unused]] char ch = s[0];

//     // Find a character
//     [[maybe_unused]] std::size_t pos = s.find('o');

//     // Append operations
//     s.append(" appended");  // Append a C-string literal
//     s.append("!");          // Append another C-string literal

//     // Substring extraction (start index 0, length 5)
//     std::string s_sub = s.substr(0, 5);

//     // Get underlying C-string pointer
//     [[maybe_unused]] const char* c_str = s.c_str();

//     // (Optional) Perform a comparison operation
//     bool eq = (s == s_copy);
//     bool ne = (s != s_copy);
//     bool lt = (s < s_copy);
//     bool gt = (s > s_copy);
//     bool le = (s <= s_copy);
//     bool ge = (s >= s_copy);
//     (void)eq;  // Avoid unused variable warning
//     (void)ne;  // Avoid unused variable warning
//     (void)lt;  // Avoid unused variable warning
//     (void)gt;  // Avoid unused variable warning
//     (void)le;  // Avoid unused variable warning
//     (void)ge;  // Avoid unused variable warning
//   }
//   auto end_std = high_resolution_clock::now();
//   auto duration_std = duration_cast<microseconds>(end_std - start_std).count();

//   // --------------------- StaticString OPERATIONS ------------------------
//   auto start_static = high_resolution_clock::now();
//   for (int i = 0; i < iterations; ++i) {
//     // Construct from C-string literal
//     cse::StaticString<128> s("Hello, World!");
//     // Copy construction
//     cse::StaticString<128> s_copy(s);
//     // Assignment operator (from another StaticString)
//     cse::StaticString<128> s_assigned;
//     s_assigned = s;

//     // Element access using operator[]
//     [[maybe_unused]] char ch = s[0];

//     // Find a character
//     [[maybe_unused]] std::size_t pos = s.find('o');

//     // Append operations (using C-string literal and a single character)
//     s.append(" appended");  // Append a C-string literal
//     s.append('!');          // Append a single character

//     // Substring extraction (start index 0, end index 5; returns a
//     // std::string_view)
//     [[maybe_unused]] auto s_sub = s.substr(0, 5);

//     // Get underlying C-string pointer
//     [[maybe_unused]] const char* c_str = s.get_str();

//     // (Optional) Perform a comparison operation
//     bool eq = (s == s_copy);
//     bool ne = (s != s_copy);
//     bool lt = (s < s_copy);
//     bool gt = (s > s_copy);
//     bool le = (s <= s_copy);
//     bool ge = (s >= s_copy);
//     (void)eq;  // Avoid unused variable warning
//     (void)ne;  // Avoid unused variable warning
//     (void)lt;  // Avoid unused variable warning
//     (void)gt;  // Avoid unused variable warning
//     (void)le;  // Avoid unused variable warning
//     (void)ge;  // Avoid unused variable warning
//   }
//   auto end_static = high_resolution_clock::now();
//   auto duration_static =
//       duration_cast<microseconds>(end_static - start_static).count();

//   // ----------------------- Print the timing results -----------------------
//   std::cout << "std::string operations took " << duration_std << " ms"
//             << std::endl;
//   std::cout << "StaticString operations took " << duration_static << " ms"
//             << std::endl;

//   return 0;
// }

/*
CHAT-GPT USED TO UPGRADE THIS MAIN:
PROMPT:
    Can you give me a main function that compares both std::string and
staticString class in terms of performance by doing same operations for each
class? StaticString.hpp and main.cpp that we already had provided.

ANSWER:
    Below is an example main() function that performs the same operations using
both std::string and your cse::StaticString class. It times the following
operations in each iteration:

Construction from a C-string literal
Copy construction
Assignment (from another object)
Element access via operator[]
Finding a character
Appending a C-string literal and a single character
Extracting a substring (for std::string we use substr(), for StaticString we use
your substr() method) Retrieving the underlying C-string pointer This version
avoids using any extra temporary std::string or std::string_view objects beyond
those operations that both types support.

cpp
Copy
#include <chrono>
#include <iostream>
#include <string>

#include "StaticString.hpp"  // Ensure this header uses your latest StaticString
implementation

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
    auto duration_std = duration_cast<milliseconds>(end_std -
start_std).count();

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

        // Substring extraction (start index 0, end index 5; returns a
std::string_view) auto s_sub = s.substr(0, 5);

        // Get underlying C-string pointer
        const char* c_str = s.get_str();

        // (Optional) Perform a comparison operation
        bool eq = (s == s_copy);
        (void)eq;  // Avoid unused variable warning
    }
    auto end_static = high_resolution_clock::now();
    auto duration_static = duration_cast<milliseconds>(end_static -
start_static).count();

    // ----------------------- Print the timing results -----------------------
    std::cout << "std::string operations took " << duration_std << " ms" <<
std::endl; std::cout << "StaticString operations took " << duration_static << "
ms" << std::endl;

    return 0;
}
Explanation
std::string Block:

Constructs a string using a C-string literal.
Performs a copy construction and assignment.
Accesses the first character, finds the character 'o', appends two literals,
extracts a substring of the first five characters, and retrieves the underlying
C-string pointer. StaticString Block:

Does the same operations using your cse::StaticString<128> class.
Note that appending a literal and a single character are available, and
substr(0, 5) returns a std::string_view that is comparable in cost. Both blocks
are timed using std::chrono::high_resolution_clock to provide a performance
comparison between std::string and your custom static string class.
*/