#include <string>
#include <iostream>
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-06/StringSet/StringSet.cpp"

using namespace cse;

TEST_CASE("Insert and Size Tests", "[insert]"){
    StringSet set;

    REQUIRE(set.size() == 0);

    set.insert("blue");
    REQUIRE(set.size() == 1);

    set.insert("yellow");
    set.insert("black");
    REQUIRE(set.size() == 3);

    // Insert a duplicate, should not change size
    set.insert("black");
    REQUIRE(set.size() == 3);

    set.insert("purple");
    REQUIRE(set.size()==4);

    set.clear();
    set.insert({"black", "blue", "purple", "green", "yellow"});
    REQUIRE(set.size() == 5);

}

TEST_CASE("Test for erase", "[erase]"){
    StringSet set;

    set.insert("blue");
    set.insert("yellow");
    set.insert("black");
    REQUIRE(set.size() == 3);

    set.erase("yellow");
    set.erase("black");
    REQUIRE(set.size() == 1);

    // green not in the set, try deleting it, it should not affect our set
    set.erase("green");
    REQUIRE(set.size() == 1);

    set.erase("blue");
    REQUIRE(set.size() == 0);

    set.erase("white");
    REQUIRE(set.size()==0);

}


TEST_CASE("Test for clear", "[clear]"){

    StringSet set;

    set.insert("blue");
    set.insert("yellow");
    REQUIRE(set.size() == 2);

    set.clear();
    REQUIRE(set.size() == 0);

    // Try clearing empty set
    set.clear();
    REQUIRE(set.size() == 0);

}

TEST_CASE("More test for erase and clear together", "[erase][clear]"){
    StringSet set;

    set.insert("white");
    set.insert("blue");
    REQUIRE(set.size() == 2);

    set.erase("white");
    set.erase("blue");
    REQUIRE(set.size() == 0);

    // Try clear in empty set
    set.clear();
    REQUIRE(set.size() == 0);

    // Try deleting element from empty set
    set.erase("yellow");
    REQUIRE(set.size() == 0);

}

TEST_CASE("Test for empty", "[empty]"){
    StringSet set;
    REQUIRE(set.empty());

    set.insert("yellow");
    REQUIRE_FALSE(set.empty());

    set.erase("yellow");
    REQUIRE(set.empty());

    set.insert("blue");
    set.clear();
    REQUIRE(set.empty());

}

TEST_CASE("Test for count", "[count]"){
    StringSet set;

    // Empty set
    REQUIRE(set.count("blue") == 0);

    set.insert("blue");
    set.insert("yellow");
    REQUIRE(set.count("blue") == 1);
    REQUIRE(set.count("yellow") == 1);
    REQUIRE(set.count("red") == 0);

    // Try adding existing element
    set.insert("blue");
    REQUIRE(set.count("blue") == 1);

    // Check after erase
    set.erase("blue");
    REQUIRE(set.count("blue") == 0);

    // Check after clear
    set.clear();
    REQUIRE(set.count("yellow") == 0);
    REQUIRE(set.empty());

}

TEST_CASE("Test for Union", "[Union]"){
    StringSet set1, set2;

    // Empty sets
    StringSet unionSet = set1.Union(set2);
    REQUIRE(unionSet.size() == 0);
    REQUIRE(set1.size() == 0);
    REQUIRE(set2.size() == 0);

    // Not empty sets
    set1.insert("blue");
    set1.insert("yellow");
    set1.insert("black");

    set2.insert("green");
    set2.insert("pink");
    set2.insert("black");
    set2.insert("green");
    REQUIRE(set2.size() == 3);

    unionSet = set1.Union(set2);
    REQUIRE(unionSet.count("blue") == 1);
    REQUIRE(unionSet.count("yellow") == 1);
    REQUIRE(unionSet.count("black") == 1);
    REQUIRE(unionSet.count("green") == 1);
    REQUIRE(unionSet.count("pink") == 1);
    REQUIRE(unionSet.count("white") == 0);
    REQUIRE(unionSet.size() == 5); // blue, yellow, black, green, pink

    // One set empty other one is not
    set1.clear();
    unionSet = set1.Union(set2);
    REQUIRE(unionSet.count("blue") == 0);
    REQUIRE(unionSet.count("yellow") == 0);
    REQUIRE(unionSet.count("black") == 1);
    REQUIRE(unionSet.count("green") == 1);
    REQUIRE(unionSet.count("pink") == 1);
    REQUIRE(unionSet.count("white") == 0);
    REQUIRE(unionSet.size() == 3); // black, green, pink

}


TEST_CASE("Test for Intersection", "[Intersection]"){
    StringSet set1, set2;

    // Empty sets
    StringSet intersectionSet = set1.Intersection(set2);
    REQUIRE(intersectionSet.size() == 0);
    REQUIRE(set1.size() == 0);
    REQUIRE(set2.size() == 0);

    // Not empty sets
    set1.insert("blue");
    set1.insert("yellow");
    set1.insert("black");

    set2.insert("green");
    set2.insert("blue");
    set2.insert("black");
    set2.insert("green");
    REQUIRE(set2.size() == 3);

    intersectionSet = set1.Intersection(set2);
    REQUIRE(intersectionSet.count("blue") == 1);
    REQUIRE(intersectionSet.count("black") == 1);
    REQUIRE(intersectionSet.count("green") == 0);
    REQUIRE(intersectionSet.count("yellow") == 0);
    REQUIRE(intersectionSet.size() == 2); // blue, black

    // One empty set
    set1.clear();
    intersectionSet = set1.Intersection(set2);
    REQUIRE(intersectionSet.count("blue") == 0);
    REQUIRE(intersectionSet.count("black") == 0);
    REQUIRE(intersectionSet.size() == 0);

}


TEST_CASE("Test for Difference", "[Difference]"){
    StringSet set1, set2;

    set1.insert("blue");
    set1.insert("yellow");
    set1.insert("black");

    set2.insert("green");
    set2.insert("blue");
    set2.insert("purple");

    StringSet differenceSet1 = set1.Difference(set2);
    REQUIRE(differenceSet1.count("yellow") == 1);
    REQUIRE(differenceSet1.count("black") == 1);
    REQUIRE(differenceSet1.count("blue") == 0);
    REQUIRE_FALSE(differenceSet1.count("green") == 1);
    REQUIRE(differenceSet1.size() == 2); // yellow, black (elements that present in first set but not in second set)

    StringSet differenceSet2 = set2.Difference(set1);
    REQUIRE(differenceSet2.count("green") == 1);
    REQUIRE(differenceSet2.count("purple") == 1);
    REQUIRE(differenceSet2.count("blue") == 0);
    REQUIRE_FALSE(differenceSet2.count("yellow") == 1);
    REQUIRE(differenceSet2.size() == 2); // green and purple (present in set2 but not in set1)

    // Try same set, needs to return empty set
    StringSet differenceSet3 = set2.Difference(set2);
    REQUIRE(differenceSet3.size() == 0);

    set1.clear();
    set2.clear();
    differenceSet1.clear();
    differenceSet2.clear();
    REQUIRE(set1.size() == 0);
    REQUIRE(set2.size() == 0);
    REQUIRE(differenceSet1.size() == 0);
    REQUIRE(differenceSet2.size() == 0);

    // 2 sets with the same elements
    set1.insert("white");
    set1.insert("brown");
    set1.insert("red");

    set2.insert("white");
    set2.insert("brown");
    set2.insert("red");

    differenceSet1 = set1.Difference(set2);
    REQUIRE(differenceSet1.count("white") == 0);
    REQUIRE(differenceSet1.count("brown") == 0);
    REQUIRE(differenceSet1.count("red") == 0);
    REQUIRE_FALSE(differenceSet1.count("yellow") == 1);
    REQUIRE(differenceSet1.size() == 0);

    differenceSet2 = set2.Difference(set1);
    REQUIRE(differenceSet2.count("white") == 0);
    REQUIRE(differenceSet2.count("brown") == 0);
    REQUIRE(differenceSet2.count("red") == 0);
    REQUIRE_FALSE(differenceSet2.count("green") == 1);
    REQUIRE(differenceSet2.size() == 0);

    // 2 empty sets
    set1.clear();
    set2.clear();

    differenceSet1 = set1.Difference(set2);
    REQUIRE(differenceSet1.count("white") == 0);
    REQUIRE(differenceSet1.size() == 0);

    differenceSet2 = set2.Difference(set1);
    REQUIRE(differenceSet2.count("white") == 0);
    REQUIRE(differenceSet2.size() == 0);

    // one set empty other is not
    set2.insert("blue");
    differenceSet2 = set2.Difference(set1);
    REQUIRE(differenceSet2.size() == 1);
    REQUIRE(differenceSet2.count("blue") == 1);
    REQUIRE(differenceSet2.count("black") == 0);

}


 TEST_CASE("Test for RetainFilter ", "[RetainFilter]"){

     StringSet set;

     set.insert("blue");
     set.insert("yellow");
     set.insert("black");
     set.insert("red");
     set.insert("brown");
     set.insert("white");

     set.RetainFilter([](const std::string& str){
         return str.size() > 4;
     });

     REQUIRE(set.size() == 4);
     REQUIRE(set.count("yellow") == 1);
     REQUIRE(set.count("black") == 1);
     REQUIRE(set.count("brown") == 1);
     REQUIRE(set.count("white") == 1);
     REQUIRE(set.count("blue") == 0);
     REQUIRE(set.count("red") == 0);
     REQUIRE(set.count("green") == 0);

     set.clear();
     REQUIRE(set.size() == 0);
     REQUIRE(set.count("yellow") == 0);

     // Try in empty set (shouldn't give any errors, set still needs to be empty)
     set.RetainFilter([](const std::string& str){
         return str.size() > 4;
     });

     REQUIRE(set.size() == 0);

 }

 TEST_CASE("Test for RemoveFilter", "[RemoveFilter]"){
     StringSet set;

     set.insert("blue");
     set.insert("yellow");
     set.insert("black");
     set.insert("red");
     set.insert("brown");
     set.insert("white");


     set.RemoveFilter([](const std::string& str){
         return str.size() > 4;
     });

     REQUIRE(set.size() == 2);
     REQUIRE(set.count("yellow") == 0);
     REQUIRE(set.count("black") == 0);
     REQUIRE(set.count("brown") == 0);
     REQUIRE(set.count("white") == 0);
     REQUIRE(set.count("blue") == 1);
     REQUIRE(set.count("red") == 1);
     REQUIRE(set.count("green") == 0);

     set.clear();
     REQUIRE(set.size() == 0);
     REQUIRE(set.count("yellow") == 0);


     // Try it in an empty set (shouldn't give any errors, still needs to be empty set)
     set.RemoveFilter([](const std::string& str){
         return str.size() > 4;
     });

     REQUIRE(set.size() == 0);

 }



TEST_CASE("Test for iterator", "[iterator]"){

    StringSet set;

    REQUIRE(set.size() == 0);
    REQUIRE(set.begin() == set.end());

    set.insert("blue");
    set.insert("yellow");
    set.insert("black");
    set.insert("green");
    set.insert("white");

    REQUIRE(set.size() == 5);
    REQUIRE(set.begin() != set.end());

    std::unordered_set<std::string> expected = {"blue", "yellow", "black", "green", "white"};
    std::unordered_set<std::string> iterated;

    for(auto i = set.begin(); i != set.end(); ++i)
    {
        iterated.insert(*i);
    }

    REQUIRE(iterated.size() == 5);
    REQUIRE(expected == iterated);

}

