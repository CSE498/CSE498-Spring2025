#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-03/src/FunctionSet.h"
#include <cstddef>
#include <iostream>
#define CATCH_CONFIG_MAIN
int func1(int x){return x+2;}
int func2(int x){return x+1;}
int func3(int x){return x*3;}
std::function<int(int)> nullFunc = nullptr;

TEST_CASE("Test1", "Basic")
{
    int x  = 0;
    CHECK(x == 0);
}

TEST_CASE("Test2","IsEmpty")
{
    cse::FunctionSet<int,int> set1;
    CHECK(set1.IsEmpty());
}

TEST_CASE("Test3","AddFuntion")
{
    cse::FunctionSet<int,int> set2;
    CHECK(set2.IsEmpty());
    set2.AddFunction(func1);
    CHECK_FALSE(set2.IsEmpty());
    set2.AddFunction(func2);
    CHECK(set2.CountFun()==2U);
}
TEST_CASE("Test4","ClearAll")
{
    cse::FunctionSet<int,int> set3;
    CHECK(set3.IsEmpty());
    set3.AddFunction(func1);
    set3.AddFunction(func2);
    CHECK(set3.CountFun()==2U);
    set3.ClearAll();
    CHECK(set3.IsEmpty());
}
TEST_CASE("Test5","Index")
{
    cse::FunctionSet<int,int> set5;
    set5.AddFunction(func1);
    set5.AddFunction(func2);
    CHECK(set5.CountFun()==2U);
    CHECK(set5.FindFunctionIndex(func2)==1);
}
TEST_CASE("Test6","RemoveFunc")
{
    cse::FunctionSet<int,int> set6;
    set6.AddFunction(func1);
    set6.AddFunction(func2);
    set6.AddFunction(func3);
    CHECK(set6.CountFun()==3U);
    CHECK(set6.FindFunctionIndex(func3)==2);
    set6.RemoveFunction(func2);
    CHECK(set6.FindFunctionIndex(func3)==1);

}

TEST_CASE("Test7","Edge"){
    cse::FunctionSet<int,int> set7;
    CHECK(set7.IsEmpty());
    CHECK_FALSE(set7.FindFunctionIndex(func1)==1);
    set7.AddFunction(nullFunc);
    set7.FindFunctionIndex(nullFunc);
    set7.RemoveFunction(nullFunc);
}
TEST_CASE("Test8","CallAll")
{
    cse::FunctionSet<int,int> set2;
    CHECK(set2.IsEmpty());
    set2.AddFunction(func1);
    CHECK_FALSE(set2.IsEmpty());
    set2.AddFunction(func2);
    CHECK(set2.CountFun()==2U);

    auto result = set2.CallAll(6);
    REQUIRE(result.size() == 2);
    CHECK(result[0] == 8);
    CHECK(result[1] == 7);
}

TEST_CASE("FunctionSetTest1", "CheckEmpty") {
    cse::FunctionSet<int, int> set1;
    CHECK(set1.IsEmpty());
}