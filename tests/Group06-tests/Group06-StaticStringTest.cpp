#include <string>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <string_view>
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
        REQUIRE(s.size() == 10);
        REQUIRE(std::strcmp(s.get_str(), exact) == 0);
    }

    SECTION("Copy constructor, copy another StaticString object")
    {
        StaticString<10> s("Hello");
        StaticString<10> copy(s);
        REQUIRE(copy.length() == s.length());
        REQUIRE(std::strcmp(copy.get_str(), s.get_str()) == 0);

        StaticString<5> small_copy(s);
        REQUIRE(small_copy.length() == s.length());
        REQUIRE(std::strcmp(small_copy.get_str(), s.get_str()) == 0);

        StaticString<15> large_copy(s);
        REQUIRE(large_copy.length() == s.length());
        REQUIRE(std::strcmp(large_copy.get_str(), s.get_str()) == 0);

        StaticString<128>s5("");
        StaticString<128>s6(s5);
        REQUIRE(s5.length() == 0);
        
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
        REQUIRE(s3.length() == s.length());
        REQUIRE(std::strcmp(s3.get_str(), s2.get_str()) == 0);
    }

    SECTION("Assigning a normal string") {
        StaticString<10> s;
        s = "Hello";
        REQUIRE(s.length() == 5);
        REQUIRE(std::strcmp(s.get_str(), "Hello") == 0);

        StaticString<5> s2;
        s2 = "Hello";
        REQUIRE(s2.length() == 5);
        REQUIRE(std::strcmp(s2.get_str(), "Hello") == 0);
    }

    SECTION("Assigning an empty string") {
        StaticString<10> s;
        s = "";
        REQUIRE(s.length() == 0);
        REQUIRE(s.size() == 10);
        REQUIRE(std::strcmp(s.get_str(), "") == 0);
    }

    SECTION("Assigning nullptr should reset the string") {
        StaticString<10> s("Hello");
        s = nullptr;
        REQUIRE(s.length() == 0);
        REQUIRE(s.size() == 10);
        REQUIRE(std::strcmp(s.get_str(), "") == 0);
    }

    SECTION("Assigning a string exactly fitting MaxSize") {
        StaticString<10> s;
        s = "HelloWorld"; 
        REQUIRE(s.length() == 10);
        REQUIRE(s.size() == 10);
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

        s = "Hi!";  
        REQUIRE(s.length() == 3);
        REQUIRE(std::strncmp(s.get_str(), "Hi!", 10) == 0);
    }

    SECTION("Operator[] with valid index")
    {
        StaticString<10> s("World");
        REQUIRE(s[0] == 'W');
        REQUIRE(s[1] == 'o');
        REQUIRE(s[2] == 'r');
        REQUIRE(s[3] == 'l');
        REQUIRE(s[4] == 'd');
    }

    SECTION("Operator[], changing the indexed value.")
    {
        StaticString<10> s("Test");
        s.set(2,'a');
        REQUIRE(s[2] == 'a');

        StaticString<10> s2("Teat");
        REQUIRE(std::strcmp(s.get_str(), s2.get_str()) == 0);
        REQUIRE(s.to_string() == "Teat");

    }

    // Comparison Operators

    StaticString<10> s1("Alpha");
    StaticString<10> s2("Bravo");
    StaticString<10> s3("Alpha");  
    StaticString<10> s4("alpha");  
    StaticString<10> s5("Alphabeta"); 
    StaticString<10> s6("12345");  
    StaticString<10> s7("!@#$%"); 
    StaticString<10> s8("ABCDEFGHIJ"); 
    StaticString<10> s9("ABCDEFGHIJ");  
    StaticString<10> s10("ABCDEFGHI"); 
    StaticString<10> emptyString(""); 


    // Comparisons conducted lexicograhical orders based
    SECTION("Equality and inequality operators") {
        REQUIRE(s1 == s3);       // Alpha == Alpha True
        REQUIRE_FALSE(s1 == s2); // Alpha == Bravo Fals
        REQUIRE(s1 != s2);       // Alpha != Bravo True
        REQUIRE_FALSE(s1 != s3); // Alpha != Alpha False

        
        REQUIRE(s1 == "Alpha");         // Alpha == Alpha True
        REQUIRE_FALSE(s1 == "Bravo");   // Alpha == Bravo False
        REQUIRE(s2 != "Alpha");         // Bravo != Alpha True

        
        REQUIRE(emptyString == "");        // "" == ""  True
        REQUIRE_FALSE(emptyString == s1);  // "" == Alpha False
        REQUIRE(emptyString != s1);        // "" != Alpha True
    }

    SECTION("Less than operator <") {
        REQUIRE(s1 < s2);           // Alpha < Bravo True
        REQUIRE(s1 < s5);           // Alpha < Alphabeta True
        REQUIRE_FALSE(s1 < s3);     // Alpha < Alpha False
        REQUIRE(emptyString < s1);  // "" < Alpha True
        REQUIRE_FALSE(s2 < s1);     // Bravo < Alpha False

        REQUIRE(s7 < s6);  // !@#$% < 12345 True
        REQUIRE(s6 < s2);  // 12345 < Bravo True
        REQUIRE(s7 < s1);  // !@#$% < Alpha True
    }

    SECTION("Greater than operator >") {
        REQUIRE(s2 > s1);           // Bravo > Alpha True
        REQUIRE(s5 > s1);           // Alphabeta > Alpha True
        REQUIRE(s1 > emptyString);  // Alpha > "" True
        REQUIRE_FALSE(s1 > s2);     // Alpha > Bravo False
    }

    SECTION("Less than or equal operator <=") {
        REQUIRE(s1 <= s3);          // Alpha <= Alpha True
        REQUIRE(s1 <= s2);          // Alpha <= Bravo True
        REQUIRE(s1 <= s5);          // Alpha <= Alphabeta True
        REQUIRE(emptyString <= s1); // "" <= Alpha True
    }

    SECTION("Greater than or equal operator >=") {
        REQUIRE(s2 >= s1);          // Bravo >= Alpha True
        REQUIRE(s5 >= s1);          // Alphabeta >= Alpha True
        REQUIRE(s1 >= emptyString); // Alpha >= "" True
        REQUIRE(s1 >= s3);          // Alpha >= Alpha True
    }

    SECTION("Case sensitivity check") {
        REQUIRE_FALSE(s1 == s4);  // Alpha == alpha False
        REQUIRE(s1 < s4);         // Alpha < alpha True
        REQUIRE(s4 > s1);         // alpha > Alpha True
    }

    SECTION("Numbers and special characters") {
        REQUIRE(s7 < s1);  // !@#$% < Alpha True
        REQUIRE(s6 < s2);  // 12345 < Bravo True
        REQUIRE(s7 < s6);  // !@#$% < 12345 True
    }

    SECTION("Edge Cases: Longer and Truncated Strings") {
        REQUIRE(s8 == s9);  
        REQUIRE_FALSE(s8 < s9); 
        REQUIRE_FALSE(s8 > s9); 
        REQUIRE(s10 < s8); // ABCDEFGHI < ABCDEFGHIJ True
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
        StaticString<10> s2("Hello");
        REQUIRE(std::strcmp(s.get_str(), "HelloWorld") == 0);
        REQUIRE_FALSE(std::strcmp(s2.get_str(), "HelloWorld") == 0);
    }

    SECTION("find member function")
    {
        StaticString<10> s("abcdef");
        REQUIRE(s.find('a') == 0);
        REQUIRE(s.find('d') == 3);
        REQUIRE(s.find('z') == StaticString<10>::npos);
        REQUIRE(s.find('g') == s.npos);
    }

    SECTION("to_string member function")
    {
        StaticString<10> s("HelloWorld");
        StaticString<10> s2("Hello");
        StaticString<10> s3(s2);

        REQUIRE(s.to_string() == "HelloWorld");
        REQUIRE(s2.to_string() == "Hello");
        REQUIRE(s3.to_string() == "Hello");      
    }

    SECTION("set member function")
    {
        StaticString<10> s("HelloWorld");
        StaticString<10> s2("Hello");
        StaticString<10> s3(s2);

        s.set(0, 'A');  // AelloWorld
        s2.set(0, 'B');  // Bello
        
        REQUIRE(s.to_string() == "AelloWorld");
        REQUIRE(s2.to_string() == "Bello");
        REQUIRE(s3.to_string() == "Hello");

        s.set(9, '!');
        REQUIRE(s.to_string() == "AelloWorl!");

    }


    SECTION("Append member function")
    {
        StaticString<20> s("HelloWorld");
        StaticString<20> s2("Hello");
        StaticString<20> s3;
        StaticString<10> s4;

        s.append("HELLOWORLD");
        s2.append("WORLD");
        s3.append("TESTMESSAGE:");

        REQUIRE(s.to_string() == "HelloWorldHELLOWORLD");
        REQUIRE(s.length() == 20);

        REQUIRE(s2.to_string() == "HelloWORLD");
        REQUIRE(s2.length() == 10);

        REQUIRE(s3.to_string() == "TESTMESSAGE:");
        REQUIRE(s3.length() == 12);

        s2.append('!');
        REQUIRE(s2.to_string() == "HelloWORLD!");
        REQUIRE(s2.length() == 11);

        s4 = "";
        s4.append('1');
        REQUIRE(s4.to_string() == "1");
        REQUIRE(s4.length() == 1);
        
        // Test the edge case of inserting null terminator to the string
        s4.set(0, '\0');
        REQUIRE(s4.to_string() == "\0");
        REQUIRE(s4.length() == 0);
        
        s2.set(5, '\0'); // S2 = "Hello\0ORLD!"
        REQUIRE(s2.length() == 5);
        REQUIRE(s2.to_string() == "Hello");
        s2.append('W');
        REQUIRE(s2.length() == 6);
        REQUIRE(s2.to_string() == "HelloW");
        s2.append("ORLD!");
        REQUIRE(s2.length() == 11);
        REQUIRE(s2.to_string() == "HelloWORLD!");

        s2.set(1, '\0');
        REQUIRE(s2.length() == 1);
        REQUIRE(s2.to_string() == "H");
        s2.append("elloWORLD!");
        REQUIRE(s2.length() == 11);
        REQUIRE(s2.to_string() == "HelloWORLD!");
        
        s2.set(9, '\0');
        REQUIRE(s2.length() == 9);
        REQUIRE(s2.to_string() == "HelloWORL");


        StaticString<20> s5("Hello");
        StaticString<20> s6;

        std::string temp = "TEST!";
        s5.append(temp);

        REQUIRE(s5.length() == 10);
        REQUIRE(s5.to_string() == "HelloTEST!");

        std::string_view sub_str = s5.substr(0, 5);
        s6.append(sub_str);
        REQUIRE(s6.length() == 5);
        REQUIRE(s6.to_string() == "Hello");

    }

    SECTION("concat member function")
    {
        StaticString<20> s("HelloWorld");
        StaticString<20> s2("Hello");
        StaticString<20> s3;
        StaticString<10> s4;
        StaticString<5> s5("12345");

        s.concat(s);
        REQUIRE(s.length() == 20);
        REQUIRE(s.to_string() == "HelloWorldHelloWorld");

        s2.concat(s3);
        REQUIRE(s2.length() == 5);
        REQUIRE(s2.to_string() == "Hello");

        s3.concat(s2);
        REQUIRE(s3.length() == 5);
        REQUIRE(s3.to_string() == "Hello");

        s3.concat(s5);
        REQUIRE(s3.length() == 10);
        REQUIRE(s3.to_string() == "Hello12345");

        s4.concat(s3);
        REQUIRE(s4.length() == 10);
        REQUIRE(s4.to_string() == "Hello12345");


        s.set(5, '\0');
        s3.concat(s);
        REQUIRE(s3.length() == 15);
        REQUIRE(s3.to_string() == "Hello12345Hello");

    }

    SECTION("substr member function")
    {
        StaticString<20> s("HelloWorld");
        StaticString<20> s2("Hello");
        StaticString<20> s3("1234567890");

        REQUIRE(s.substr(0,5) == "Hello");
        REQUIRE(s.substr(1,6) == "elloW");
        REQUIRE(s.substr(0,10) == "HelloWorld");
        REQUIRE(s2.substr(1,2) == "e");
        
        REQUIRE(s2.substr(1,1) == "");

        std::string_view temp = s3.substr(1,6);
        REQUIRE(temp == "23456");

    }
}

