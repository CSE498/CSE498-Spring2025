//==============================================================================
// BEYOND THIS POINT TESTS ARE FOR ADVANCED MEMEBR FUNCTIONS
//==============================================================================
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

#include "../../Group-06/StaticString/StaticString.hpp"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

using namespace cse;

TEST_CASE("Tests for advanced memeber functions", "[StaticString]") {

  SECTION("TESTS: Find_all member function") {
    StaticString<20> s("HelloWorldHelloWorld");
    StaticString<20> s2("abcdabcdabcdabcd");
    StaticString<20> s3("1234567890123545");

    REQUIRE(s.findAll("Hello") == [0,10]);
    REQUIRE(s2.findAll("ab") == [0,4,8,12]);
    REQUIRE(s3.findAll("34") == [2]);
    
    REQUIRE(s.findAll('e') == [1,11]);
    REQUIRE(s.findAll('E') == cse::StaticString::npos);
    REQUIRE(s.findAll('d') == [9,19]);

    REQUIRE(s2.findAll("abcD") == cse::StaticString::npos);
    REQUIRE(s2.findAll("abcd") == [0,4,8,12]);

    REQUIRE(s3.findAll("0") == [9]);

  }

  SECTION("TESTS: rFind  member function") {
    StaticString<20> s("HelloWorldHelloWorld");
    StaticString<20> s2("abcdabcdabcdabcd");
    StaticString<20> s3("1234567890123545");

    REQUIRE(s.rFind("Hello") == [10,0]);
    REQUIRE(s2.rFind("ab") == [12,8,4,0]);
    REQUIRE(s3.rFind("34") == [2]);
    
    REQUIRE(s.rFind('e') == [11,1]);
    REQUIRE(s.rFind('E') == cse::StaticString::npos);
    REQUIRE(s.rFind('d') == [19,9]);

    REQUIRE(s2.rFind("abcD") == cse::StaticString::npos);
    REQUIRE(s2.rFind("abcd") == [12,8,4,0]);

    REQUIRE(s3.rFind("0") == [9]);
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
    s3.replace("1234", "00")
    REQUIRE(std::strcmp(s3.get_str(), "00567890123545") == 0);

    s3.replace("00", "1234");
    REQUIRE(std::strcmp(s2.get_str(), "1234567890123545") == 0);

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
    CHECK_THROWS(s.replace("o","******") == std::out_of_range);

  }

  SECTION("TESTS: Replace_if  member function") {
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
  }

  SECTION("TESTS: Operators member function") {
    //operator>> for file streams 
    std::istringstream iss("TestInput");
    StaticString<20> s;
    
    iss >> s;
    REQUIRE(std::strcmp(s.get_str(), "TestInput") == 0);
    
    std::istringstream iss2("Hello World");
    StaticString<20> s2;
    iss2 >> s2;
    // Due to whitespace only first input read check that
    REQUIRE(std::strcmp(s2.get_str(), "Hello") == 0);


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
    for (auto it = begin; it != end; ++it) {
        result.push_back(*it);
    }
    REQUIRE(result == "abcdef");

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

    s2.insert("!!!", 7);
    REQUIRE(std::strcmp(s2.get_str(), "a1234bcd!!!") == 0);

    s2.insert('*', 3);
    REQUIRE(std::strcmp(s2.get_str(), "a12*34bcd!!!") == 0);

    s3.insert(std::string_view("Test"), 3);
    std::string_view inserted(s3.get_str() + 3, 4);
    REQUIRE(inserted == "123Test4567890");
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
    REQUIRE(std::strcmp(s.get_str(), "bbbcccaaa") == 0);

    s = "aaabbbcccaaa";
    s.remove(3,8);
    REQUIRE(std::strcmp(s.get_str(), "aaaaaa") == 0);
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

  SECTION("TESTS: Transform with lambda  member function") {
    StaticString<20> s("abc");

    s.transform([](char ch) -> char {
        if (ch >= 'a' && ch <= 'z')
            return static_cast<char>(ch - 'a' + 'A');
        return ch;
    });
    REQUIRE(std::strcmp(s.get_str(), "ABC") == 0);
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
  }

  SECTION("TESTS: split member function") {
    StaticString<30> s("Hello,World,Test");
    std::vector<StaticString<30>> result;

    s.split(',', result);

    REQUIRE(result.size() == 3);
    REQUIRE(result[0].to_string() == "Hello");
    REQUIRE(result[1].to_string() == "World");
    REQUIRE(result[2].to_string() == "Test");
  }

  SECTION("TESTS: compare member function") {
    StaticString<10> s1("Hello");
    StaticString<10> s2("Hello");
    StaticString<10> s3("World");

    REQUIRE(s1.compare(s2, [](char a, char b) { return a == b; }) == true);
    REQUIRE(s1.compare(s3, [](char a, char b) { return a == b; }) == false);
  }
}