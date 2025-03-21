//==============================================================================
// BEYOND THIS POINT TESTS ARE FOR ADVANCED MEMEBR FUNCTIONS
//==============================================================================
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include <ostream>

#include "../../Group-06/StaticString/StaticString.hpp"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

using namespace cse;

TEST_CASE("Tests for advanced memeber functions", "[StaticString]") {

  SECTION("TESTS: Find_all member function") {
    StaticString<20> s("HelloWorldHelloWorld");
    StaticString<20> s2("abcdabcdabcdabcd");
    StaticString<20> s3("1234567890123545");

    REQUIRE(s.findAll("Hello") == std::vector<size_t>{0,10});
    REQUIRE(s2.findAll("ab") == std::vector<size_t>{0,4,8,12});
    REQUIRE(s3.findAll("34") ==std::vector<size_t>{2});
    
    REQUIRE(s.findAll('e') == std::vector<size_t>{1,11});
    REQUIRE(s.findAll('E') == std::vector<size_t>{});//cse::StaticString::npos2);
    REQUIRE(s.findAll('d') == std::vector<size_t>{9,19});

    REQUIRE(s2.findAll("abcD") == std::vector<size_t>{});//cse::StaticString::npos2);
    REQUIRE(s2.findAll("abcd") == std::vector<size_t>{0,4,8,12});

    REQUIRE(s3.findAll("0") == std::vector<size_t>{9});

  }

  SECTION("TESTS: rFind  member function") {
    StaticString<20> s("HelloWorldHelloWorld");
    StaticString<20> s2("abcdabcdabcdabcd");
    StaticString<20> s3("1234567890123545");

    REQUIRE(s.rFind("Hello") == std::vector<size_t>{10,0});
    REQUIRE(s2.rFind("ab") == std::vector<size_t>{12,8,4,0});
    REQUIRE(s3.rFind("34") == std::vector<size_t>{2});
    
    REQUIRE(s.rFind('e') == std::vector<size_t>{11,1});
    REQUIRE(s.rFind('E') == std::vector<size_t>{});//cse::StaticString::npos);
    REQUIRE(s.rFind('d') == std::vector<size_t>{19,9});

    REQUIRE(s2.rFind("abcD") == std::vector<size_t>{});//cse::StaticString::npos);
    REQUIRE(s2.rFind("abcd") == std::vector<size_t>{12,8,4,0});

    REQUIRE(s3.rFind("0") == std::vector<size_t>{9});
  }

  SECTION("TESTS: Replace  member function") {
    StaticString<20> s("HelloWorldHelloWorld");
    StaticString<20> s2("abcdabcdabcdabcd");
    StaticString<20> s3("1234567890123545");
    StaticString<20> s4("12345");

    s.replace("Hello", "olleH");
    REQUIRE(std::strcmp(s.get_str(), "olleHWorldolleHWorld") == 0);

    s2.replace('d', '!');
    REQUIRE(std::strcmp(s2.get_str(), "abc!abc!abc!abc!") == 0);

    s2.replace('a', '*');
    REQUIRE(std::strcmp(s2.get_str(), "*bc!*bc!*bc!*bc!") == 0);

    // Replace by greater or smaller size
    // Replace checks if replace occurs size would be exceeded or not
    s3.replace("1234", "00");
    REQUIRE(std::strcmp(s3.get_str(), "00567890123545") == 0);

    s3.replace("00", "1234");
    REQUIRE(std::strcmp(s3.get_str(), "1234567890123545") == 0);

    s4.replace('1', "HI");
    REQUIRE(std::strcmp(s4.get_str(), "HI2345") == 0);

    s4.replace('2', "my");
    REQUIRE(std::strcmp(s4.get_str(), "HImy345") == 0);

    s4.replace('3', "Name");
    REQUIRE(std::strcmp(s4.get_str(), "HImyName45") == 0);

    s4.replace('4', "IS");
    REQUIRE(std::strcmp(s4.get_str(), "HImyNameIS5") == 0);

    s4.replace('5', "**********");
    REQUIRE(std::strcmp(s4.get_str(), "HImyNameIS**********") == 0);

    s4.replace("**********",'5');
    REQUIRE(std::strcmp(s4.get_str(), "HImyNameIS5") == 0);
    //Check if replace with larger value than size it can take would occur or not?
    CHECK_THROWS(s.replace("o","******"));
  }

  /*SECTION("TESTS: Replace_if  member function") {
    // Takes a lambda as the condition
    StaticString<20> s("HelloWorldHelloWorld");

    s.replace_if("Hello","HI", [](){return true;});
    REQUIRE(std::strcmp(s.get_str(), "HIWorldHIWorld") == 0);

    s.replace_if("HI","Hello", [](){return false;});
    REQUIRE(std::strcmp(s.get_str(), "HIWorldHIWorld") == 0);


    StaticString<50> s2("a1b2c3d4");
    // replace_if(conditionLambda, replacementLambda)
    s2.replace_if(
        [](char ch) -> bool { return (ch >= '1' && ch <= '4'); },
        [](char ch) -> char { return ch + 1; }
    );

    REQUIRE(std::strcmp(s2.get_str(), "a2b3c4d5") == 0);
  }*/

  SECTION("TESTS: Operators member function") {
    //operator>> for file streams 
    std::istringstream iss("TestInput");
    StaticString<20> s;
    
    REQUIRE(std::strcmp(s.get_str(), "") == 0);
    REQUIRE(s.length() == 0);
    iss >> s;
    REQUIRE(std::strcmp(s.get_str(), "TestInput") == 0);
    REQUIRE(s.length() == 9);
    
    std::istringstream iss2("Hello World");
    StaticString<20> s2;

    iss2 >> s2;
    // Due to whitespace only first input read check that
    REQUIRE(std::strcmp(s2.get_str(), "Hello") == 0);
    REQUIRE(s2.length() == 5);

    //operator<< for streams
    StaticString<20> s3("HelloWorld");
    std::ostringstream oss;
    
    oss << s3;
    REQUIRE(oss.str() == "HelloWorld");
  }

  SECTION("TESTS: Iterators") {
    StaticString<10> s("abcdef");

    auto begin = s.begin();
    auto end = s.end();

    std::string result;
    int counter = 0;
    for (auto it = begin; it != end; ++it) {
        result.push_back(*it);
        counter++;
    }
    std::cout << std::to_string(counter);
    REQUIRE(result == "abcdef");

    std::string temp_result;
    int temp_counter = 0;
    for(auto item : s) {
      temp_result.push_back(item);
      temp_counter++;
    }

    REQUIRE(temp_result == "abcdef");
  }

  SECTION("TESTS: Insert member function") {
    StaticString<30> s("HelloWorld");
    StaticString<20> s2("abcd");
    StaticString<20> s3("1234567890");

    s.insert("Hello", 0);
    REQUIRE(std::strcmp(s.get_str(), "HelloHelloWorld") == 0);

    s.insert("World", 10);
    REQUIRE(std::strcmp(s.get_str(), "HelloHelloWorldWorld") == 0);

    s.insert(" ", 5);
    REQUIRE(std::strcmp(s.get_str(), "Hello HelloWorldWorld") == 0);

    s2.insert("1234", 1);
    REQUIRE(std::strcmp(s2.get_str(), "a1234bcd") == 0);

    s2.insert("!!!", 8);
    REQUIRE(std::strcmp(s2.get_str(), "a1234bcd!!!") == 0);

    s2.insert('*', 3);
    REQUIRE(std::strcmp(s2.get_str(), "a12*34bcd!!!") == 0);

    s3.insert(std::string_view("Test"), 3);
    std::string_view inserted(s3.get_str() + 3, 4);
    REQUIRE(inserted == "Test");

    // Error Checking
    StaticString<10> s4("1234567890");
    CHECK_THROWS_AS(s4.insert('x',0), std::out_of_range);
    CHECK_THROWS_AS(s4.insert('x',5), std::out_of_range);
    CHECK_THROWS_AS(s4.insert('x',10), std::out_of_range);
    CHECK_THROWS_AS(s4.insert('x',9), std::out_of_range);

    CHECK_THROWS_AS(s4.insert("TEST",0), std::out_of_range);
    CHECK_THROWS_AS(s4.insert(std::string_view("Test"),4), std::out_of_range);

    CHECK_THROWS_AS(s4.insert("TEST", 10), std::out_of_range);
    CHECK_THROWS_AS(s4.insert(std::string("test"),0), std::out_of_range);

    StaticString<10> s5("12345678");
    CHECK_THROWS_AS(s5.insert("TEST",0), std::out_of_range);

    // Check if nullptr handled correctly
    // S2 is a12*34bcd!!!
    s2.set(3,'\0');
    CHECK(std::strcmp(s2.get_str(), "a12") == 0);

    s2.insert("TEST", 2);
    CHECK(std::strcmp(s2.get_str(), "a1TEST2") == 0);

    s2.insert("---", 7);
    CHECK(std::strcmp(s2.get_str(), "a1TEST2---") == 0);
  }

  SECTION("TESTS: Erase  member function") {
    StaticString<40> s("aaabbbcccaaa");

    s.erase("aaa");
    REQUIRE(std::strcmp(s.get_str(), "bbbccc") == 0);

    s = "aaabbbcccaaa";
    s.erase("aaa", 0);
    REQUIRE(std::strcmp(s.get_str(), "bbbcccaaa") == 0);

    s = "abcbdb";
    s.erase('b');
    REQUIRE(std::strcmp(s.get_str(), "acd") == 0);
  }

  SECTION("TESTS: Remove member function") {
    StaticString<40> s("aaabbbcccaaa");

    s.remove(0,2);
    REQUIRE(std::strcmp(s.get_str(), "abbbcccaaa") == 0);

    s = "aaabbbcccaaa";
    s.remove(3,9);
    REQUIRE(std::strcmp(s.get_str(), "aaaaaa") == 0);

    s = "aaabbbcccaaa";
    s.remove(9,12);
    REQUIRE(std::strcmp(s.get_str(), "aaabbbccc") == 0);

    // Check Error cases 
    CHECK_THROWS_AS(s.remove(2,0), std::out_of_range);
    CHECK_THROWS_AS(s.remove(0,0), std::out_of_range);
    CHECK_THROWS_AS(s.remove(2,10), std::out_of_range);

    s.remove(0,1);
    REQUIRE(std::strcmp(s.get_str(), "aabbbccc") == 0);
  }

  SECTION("TESTS: Swap  member function") {
    StaticString<40> s("Hello World Hello");

    s.swap("Hello", "Tests", [](const std::string_view& word) { return word == "Hello"; });
    REQUIRE(std::strcmp(s.get_str(), "Tests World Tests") == 0);

    s = "hello world";
    s.swap("hello", "hi");
    REQUIRE(std::strcmp(s.get_str(), "hi world") == 0);

    StaticString<50> s1("Temp temp TEMP temp");

    auto isAllLower = [](const std::string_view& word) -> bool {
         for (char ch : word) {
             if (!std::islower(static_cast<unsigned char>(ch)))
                 return false;
         }
         return true;
    };
    s1.swap("temp", "final", isAllLower);
    REQUIRE(std::strcmp(s1.get_str(), "Temp final TEMP final") == 0);
  }

  SECTION("TESTS: Trim  member function") {
    StaticString<30> s("Hello World   ");

    s.trim();
    REQUIRE(std::strcmp(s.get_str(), "Hello World") == 0);

    s = "test";
    s.trim();
    REQUIRE(std::strcmp(s.get_str(), "test") == 0);
  }
  
  
  SECTION("TESTS: Foreach with lambda  member function") {
    StaticString<20> s("abc");
    std::string collected;
    
    s.foreach([&collected](char ch) { collected.push_back(ch); });
    REQUIRE(collected == "abc");

    int count = 0;
    s.foreach([&count](char) { ++count; });
    REQUIRE(count == 3);


    StaticString<50> s2("Hello World");
    int vowelCount = 0;

    s2.foreach([&vowelCount](char& ch) {
         // If the character is a vowel, count it and convert to uppercase
         if (std::strchr("aeiou", ch)) {
             vowelCount++;
             ch = static_cast<char>(std::toupper(ch));
         }
    });

    REQUIRE(vowelCount == 3);
    REQUIRE(std::strcmp(s2.get_str(), "HEllO WOrld") == 0);
  }
  
  SECTION("TESTS: Transform with lambda member function") {
    StaticString<20> s("abc");

    auto transformed = s.transform([](char ch) -> char {
        if (ch >= 'a' && ch <= 'z')
            return static_cast<char>(ch - 'a' + 'A');
        return ch;
    });
    REQUIRE(std::strcmp(s.get_str(), "abc") == 0);
    REQUIRE(std::strcmp(transformed.get_str(), "ABC") == 0);
  }
  
  SECTION("TESTS: Count member function") { 
    StaticString<40> s("aabbccddeeff");

    auto counts = s.char_count();

    REQUIRE(counts['a'] == 2);
    REQUIRE(counts['b'] == 2);
    REQUIRE(counts['c'] == 2);
    REQUIRE(counts['d'] == 2);
    REQUIRE(counts['e'] == 2);
    REQUIRE(counts['f'] == 2);

    StaticString<40> s2("a");

    auto counts2 = s2.char_count();
    REQUIRE(counts2['a'] == 1);

    StaticString<40> s3("ababbabbaab");

    auto counts3 = s3.char_count();
    REQUIRE(counts3['a'] == 5);
    REQUIRE(counts3['b'] == 6);
  }

  SECTION("TESTS: split member function") {
    StaticString<30> s("Hello,World,Test");
    std::vector<StaticString<30>> result;

    result = s.split(',');

    REQUIRE(result.size() == 3);
    REQUIRE(result[0].to_string() == "Hello");
    REQUIRE(result[1].to_string() == "World");
    REQUIRE(result[2].to_string() == "Test");

    // Test to see if delimiter at the end
    StaticString<30> s2("Hello,World,Test,");
    std::vector<StaticString<30>> result2;

    result2 = s2.split(',');

    REQUIRE(result2.size() == 3);
    REQUIRE(result2[0].to_string() == "Hello");
    REQUIRE(result2[1].to_string() == "World");
    REQUIRE(result2[2].to_string() == "Test");

    // Test to see if delimiter at the beginning
    StaticString<30> s3(",Hello,World,Test");
    std::vector<StaticString<30>> result3;

    result3 = s3.split(',');

    REQUIRE(result3.size() == 3);
    REQUIRE(result3[0].to_string() == "Hello");
    REQUIRE(result3[1].to_string() == "World");
    REQUIRE(result3[2].to_string() == "Test");
  }

  SECTION("TESTS: compare member function") {
    StaticString<10> s1("Hello");
    StaticString<10> s2("Hello");
    StaticString<10> s3("World");

    REQUIRE(s1.compare(s2, [](char a, char b) { return a == b; }) == true);
    REQUIRE(s1.compare(s3, [](char a, char b) { return a == b; }) == false);

    /*
      For the application part 
      StaticString<10> s1("Hello")
      StaticString<10> s1("__l*") 
      with a custom match pattern function or a class will be fed in to 
      compare function as comparator thus will be able to check if the 
      pattern matches.
    */
  }

  SECTION("TESTS: empty and clear") {
    StaticString<10> s1("Hello");
    StaticString<10> s2("Hello World");
    StaticString<10> s3("");

    REQUIRE(s1.empty() == false);
    s1.clear();
    REQUIRE(s1.empty() == true);

    for(auto i : s1) {
      REQUIRE(i == '\0');
    }

    REQUIRE(s3.empty() == true);
    s3.clear();
    REQUIRE(s3.empty() == true);


    REQUIRE(s2.empty() == false);
    s2.set(5,'\0');
    REQUIRE(s2.empty() == false);

    s2.clear();
    REQUIRE(s2.empty() == true);

    for(auto i : s2) {
      REQUIRE(i == '\0');
    }
  }

  //cse::StaticString<10> s2("Hello World"); get_Str() = "Hello Worl"
}

TEST_CASE("Tests for advanced edge case tests", "[StaticString]") {
  SECTION("TESTS: Constructor templated types") {
    StaticString<10> s("Hello World");
    REQUIRE(std::strcmp(s.get_str(), "Hello Worl") == 0); // Longer string but only allowed part used

    StaticString<10> s1("Hello World TEST");
    REQUIRE(std::strcmp(s1.get_str(), "Hello Worl") == 0); // Longer string but only allowed part used


    std::string input = "std::String";
    StaticString<11> s2(input);
    REQUIRE(std::strcmp(s2.get_str(), "std::String") == 0);

    std::string_view view{"std::string_view"};
    StaticString<30> s3(view);
    REQUIRE(std::strcmp(s3.get_str(), "std::string_view") == 0);

  }

}