#include <string>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-06/StaticString/StaticString.hpp"


using namespace cse;


TEST_CASE("Tests for constructors", "[StaticString]") {

    SECTION("Constructor by default")
    {
        StaticString<10> s;
        REQUIRE(s.length() == 0);
        REQUIRE(s.size() == 10);
        REQUIRE(std::strcmp(s.get_str(), "") == 0);
    }

    SECTION("Constructor for empty string")
    {
        StaticString<0> s;
        REQUIRE(s.length() == 0);
        REQUIRE(s.size() == 0);
        REQUIRE(std::strcmp(s.get_str(), "") == 0);


        StaticString<5> s2("");
        REQUIRE(s2.length() == 0);
        REQUIRE(s2.size() == 5);
        REQUIRE(std::strcmp(s2.get_str(), "") == 0);
    }

    SECTION("Constructor with valid string")
    {
        StaticString<10> s("Hello");
        REQUIRE(s.length() == 5);
        REQUIRE(s.size() == 10);
        REQUIRE(std::strcmp(s.get_str(), "Hello") == 0);
    }   

    SECTION("Constructor with a string exactly equal to capacity") {
        char exact[11] = "1234567890"; 
        StaticString<10> s(exact);
        REQUIRE(s.length() == 10);
        REQUIRE(std::strcmp(s.get_str(), exact) == 0);
    }

    SECTION("Copy constructor, copy another StaticString object")
    {
        StaticString<10> s("Hello");
        StaticString<10> copy(s);
        REQUIRE(copy.length() == s.length());
        REQUIRE(std::strcmp(copy.get_str(), s.get_str()) == 0);
    }

}


TEST_CASE("Tests for operators", "[StaticString]") {

    SECTION("Assignment operator copies correctly")
    {
        StaticString<10> s("Hello");
        StaticString<10> s2;
        s2 = s;
        REQUIRE(s2.length() == s.length());
        REQUIRE(std::strcmp(s2.get_str(), s.get_str()) == 0);

        StaticString<20> s3;
        s3 = s2;
        REQUIRE(s3.length() == s2.length());
        REQUIRE(std::strcmp(s3.get_str(), s2.get_str()) == 0);
    }

    SECTION("Assigning a normal string") {
        StaticString<10> s;
        s = "Hello";
        REQUIRE(s.length() == 5);
        REQUIRE(std::strcmp(s.get_str(), "Hello") == 0);
    }

    SECTION("Assigning an empty string") {
        StaticString<10> s;
        s = "";
        REQUIRE(s.length() == 0);
        REQUIRE(std::strcmp(s.get_str(), "") == 0);
    }

    SECTION("Assigning nullptr should reset the string") {
        StaticString<10> s("Hello");
        s = nullptr;
        REQUIRE(s.length() == 0);
        REQUIRE(std::strcmp(s.get_str(), "") == 0);
    }

    SECTION("Assigning a string exactly fitting MaxSize") {
        StaticString<10> s;
        s = "HelloWorld"; 
        REQUIRE(s.length() == 10);
        REQUIRE(std::strcmp(s.get_str(), "HelloWorld") == 0);
    }

    SECTION("Assigning multiple times should overwrite previous value") {
        StaticString<10> s("Hello");
        s = "World!";
        REQUIRE(s.length() == 6);
        REQUIRE(std::strcmp(s.get_str(), "World!") == 0);

        s = "123456";  
        REQUIRE(s.length() == 6);
        REQUIRE(std::strncmp(s.get_str(), "123456", 10) == 0);
    }

    SECTION("Operator[] with valid index")
    {
        StaticString<10> s("World");
        REQUIRE(s[0] == 'W');
        REQUIRE(s[1] == 'o');
        REQUIRE(s[2] == 'r');
        REQUIRE(s[3] == 'l');
        REQUIRE(s[4] == 'd');
        REQUIRE(s[5] == '\0');
        REQUIRE(s[10] == '\0');
    }

    SECTION("Operator[], changing the indexed value.")
    {
        StaticString<10> s("Test");
        s.set(2,'a');
        REQUIRE(s[2] == 'a');

        StaticString<10> s2("Teat");
        REQUIRE(std::strcmp(s.get_str(), s2.get_str()) == 0);
        REQUIRE(s.to_string() == "Teat");

        // Add a character to the end of string.
        s.set(4,'a');
        REQUIRE(s[4] == 'a');
        REQUIRE(s.to_string() == "Teata");
        StaticString<10> s3("Teata");
        REQUIRE(std::strcmp(s.get_str(), s3.get_str()) == 0);

    }

    // Comparison Operators

    StaticString<10> s1("Alpha");
    StaticString<10> s2("Bravo");
    StaticString<10> s3("Alpha");  
    StaticString<10> s4("alpha");  
    StaticString<10> s5("Alphabeta"); 
    StaticString<10> s6("12345");  
    StaticString<10> s7("!@#$%"); 
    StaticString<10> emptyString(""); 
    
    SECTION("Equality and inequality operators") {
        REQUIRE(s1 == s3);       
        REQUIRE_FALSE(s1 == s2); 
        REQUIRE(s1 != s2);       
        REQUIRE_FALSE(s1 != s3);

        
        REQUIRE(s1 == "Alpha");
        REQUIRE_FALSE(s1 == "Bravo");
        REQUIRE(s2 != "Alpha");

        
        REQUIRE(emptyString == "");  
        REQUIRE_FALSE(emptyString == s1);
        REQUIRE(emptyString != s1);
    }

    SECTION("Less than operator <") {
        REQUIRE(s1 < s2);  
        REQUIRE(s1 < s5);  
        REQUIRE(emptyString < s1);  
        REQUIRE_FALSE(s2 < s1);  
    }

    SECTION("Greater than operator >") {
        REQUIRE(s2 > s1);  
        REQUIRE(s5 > s1); 
        REQUIRE(s1 > emptyString); 
        REQUIRE_FALSE(s1 > s2);  
    }

    SECTION("Less than or equal operator <=") {
        REQUIRE(s1 <= s3);  
        REQUIRE(s1 <= s2);  
        REQUIRE(s1 <= s5);  
        REQUIRE(emptyString <= s1);  
    }

    SECTION("Greater than or equal operator >=") {
        REQUIRE(s2 >= s1);  
        REQUIRE(s5 >= s1);  
        REQUIRE(s1 >= emptyString);  
        REQUIRE(s1 >= s3);  
    }

    SECTION("Case sensitivity check") {
        REQUIRE_FALSE(s1 == s4);  
        REQUIRE(s1 < s4);  
        REQUIRE(s4 > s1);  
    }

    SECTION("Numbers and special characters") {
        REQUIRE(s7 < s1);  
        REQUIRE(s6 < s2);  
        REQUIRE(s7 < s6);  
    }

}


TEST_CASE("Tests for member functions", "[StaticString]") {

    SECTION("size and length member functions")
    {
        StaticString<15> s("Hello");
        REQUIRE(s.size() == 15);
        REQUIRE(s.length() == 5);

        StaticString<20> s2(s);
        REQUIRE(s2.size() == 20);
        REQUIRE(s2.length() == 5);
    }
    
    SECTION("get_str member function")
    {
        StaticString<10> s("HelloWorld");
        REQUIRE(std::strcmp(s.get_str(), "HelloWorld") == 0);
    }

    SECTION("find member function")
    {
        StaticString<10> s("abcdef");
        REQUIRE(s.find('a') == 0);
        REQUIRE(s.find('d') == 3);
        REQUIRE(s.find('z') == StaticString<10>::npos);
    }

    SECTION("to_string member function")
    {
        StaticString<10> s("HelloWorld");
        StaticString<10> s2("Hello");
        StaticString<10> s3(s2);

        REQUIRE(s.to_string() == "HelloWorld");
        REQUIRE(s2.to_string() == "Hello");
        REQUIRE(s3.to_string() == "Hello");


        s2.set(5,'o');
        s2.set(6,'o');
        REQUIRE(s2.to_string() == "Hellooo");
        
    }

    SECTION("set member function and Update_length private member function tests")
    {
        StaticString<10> s("Hello");
        s.set(5,'o');
        s.set(6,'o');
        REQUIRE(s.to_string() == "Hellooo");
        REQUIRE(s.length() == 7);

        s.set(5, '\0');
        REQUIRE(s.to_string() == "Hello");
        REQUIRE(s.length() == 5);

    }

}

