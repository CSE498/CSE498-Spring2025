#include "Serializer.h"
#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <fstream>

TEST(SerializerTest, Construct)
{
    cse::Serializer Saver(cse::Mode::SAVE);
    cse::Serializer Loader(cse::Mode::LOAD);
}

TEST(SerializerTest, Save)
{
    cse::Serializer Saver(cse::Mode::SAVE);

    struct Person
    {
        char name[100];
        int age;
        double height;
    };

    Person P1 = {"tdkduong", 22, 167.5};
    std::string TestP1 = "TestP1.bin";
    Saver.Serialize(P1, TestP1);

    std::ifstream inFile(TestP1, std::ios::binary);
    ASSERT_TRUE(inFile);

    std::streamsize TrueSize = sizeof(Person);
    std::ifstream file(TestP1, std::ios::binary | std::ios::ate);
    std::streamsize TestSize = file.tellg();
    ASSERT_EQ(TrueSize, TestSize);

    Person P2;
    inFile.read(reinterpret_cast<char *>(&P2), sizeof(Person));
    inFile.close();

    ASSERT_STREQ(P1.name, P2.name);
    ASSERT_EQ(P1.age, P2.age);
    ASSERT_EQ(P1.height, P2.height);
}

TEST(SerializerTest, Load)
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
    std::string TestP1 = "TestP1.bin";
    Saver.Serialize(P1, TestP1);

    Person P2;
    Loader.Serialize(P2, TestP1);

    ASSERT_STREQ(P1.name, P2.name);
    ASSERT_EQ(P1.age, P2.age);
    ASSERT_EQ(P1.height, P2.height);
}

TEST(SerializerTest, Int)
{
    cse::Serializer Saver(cse::Mode::SAVE);
    cse::Serializer Loader(cse::Mode::LOAD);
    int P1 = 42;
    std::string TestP1 = "TestP1.bin";
    int P2 = -1;
    Saver.Serialize(P1, TestP1);
    ASSERT_EQ(P2, -1);
    Loader.Serialize(P2, TestP1);
    ASSERT_EQ(P2, 42);
}