#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-07/Team07Library/Serializer.h"

#include <iostream>
#include <fstream>

TEST_CASE("Serializer Construction", "[Serializer]")
{
    cse::Serializer Saver(cse::Mode::SAVE);
    cse::Serializer Loader(cse::Mode::LOAD);
}

TEST_CASE("Serializer Save", "[Serializer]")
{
    cse::Serializer Saver(cse::Mode::SAVE);
    struct Person
    {
        char name[100];
        int age;
        double height;
    };
    Person P1 = {"tdkduong", 22, 167.5};
    Saver.Serialize(P1, "TestP1.bin");
    std::ifstream inFile("TestP1.bin", std::ios::binary);
    REQUIRE(inFile);
    std::streamsize TrueSize = sizeof(Person);
    std::ifstream file("TestP1.bin", std::ios::binary | std::ios::ate);
    std::streamsize TestSize = file.tellg();
    REQUIRE(TrueSize == TestSize);
    Person P2;
    inFile.read(reinterpret_cast<char *>(&P2), sizeof(Person));
    inFile.close();
    for (int i = 0; i < 100; i++)
        REQUIRE(P1.name[i] == P2.name[i]);
    REQUIRE(P1.age == P2.age);
    REQUIRE(P1.height == P2.height);
    std::remove("TestP1.bin");
}

TEST_CASE("Serializer Load", "Serializer")
{
    cse::Serializer Saver(cse::Mode::SAVE);
    cse::Serializer Loader(cse::Mode::LOAD);
    struct Person
    {
        char name[100];
        int age;
        double height;
    };
    Person P1 = {"tdkduong", 22, 167.5};
    Saver.Serialize(P1, "TestP1.bin");
    Person P2;
    Loader.Serialize(P2, "TestP1.bin");
    for (int i = 0; i < 100; i++)
        REQUIRE(P1.name[i] == P2.name[i]);
    REQUIRE(P1.age == P2.age);
    REQUIRE(P1.height == P2.height);
    std::remove("TestP1.bin");
}
