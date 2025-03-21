// These tests were generated with the assistance of GitHub Copilot

#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <random>
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-06/StringSet/StringSet.hpp"

using namespace cse;

TEST_CASE("Test for IsSubset", "[IsSubset]") {
	StringSet set1, set2;
	
	SECTION("Empty test is a subset of empty set and itself") {
		REQUIRE(set1.IsSubset(set2));
		REQUIRE(set1.IsSubset(set1));
	}
	
	SECTION("Non-empty set is a subset of itself") {
		set1.insert("cat");
		set1.insert("dog");
		REQUIRE(set1.IsSubset(set1));
	}
	
	SECTION("Non-empty set is a subset of another larger non-empty set") {
		set1.insert("cat");
		set2.insert("cat");
		set1.insert("dog");
		set2.insert("dog");
		
		set2.insert("ivan");
		set2.insert("monkey");
		
		REQUIRE(set1.IsSubset(set2));
		
	}
	
	SECTION("Superset is not a subset") {
		set1.insert("cat");
		set2.insert("cat");
		set1.insert("dog");
		set2.insert("dog");
		
		set1.insert("monkey");
		
		REQUIRE_FALSE(set1.IsSubset(set2));
	}
}

TEST_CASE("Test for SubstringFilter", "[SubstringFilter]") {
	StringSet set;
	
	SECTION("Filtering from an empty set should not cause errors") {
		set.SubstringFilter("something");
		REQUIRE(set.size() == 0);
	}
	
	SECTION("Filtering with non-occuring substring should not change the set") {
		set.insert("apple");
		set.insert("banana");
		set.insert("orange");
		set.SubstringFilter("something");
		
		REQUIRE(set.count("apple") == 1);
		REQUIRE(set.count("banana") == 1);
		REQUIRE(set.count("orange") == 1);
		REQUIRE(set.count("something") == 0);
	}
	
	SECTION("Using a substring that occurs in all elements") {
		set.insert("apple");
		set.insert("banana");
		set.insert("orange");
		set.SubstringFilter("a");
		REQUIRE(set.size() == 0);
	}
	
	SECTION("Using a substring that occurs in some elements") {
		set.insert("apple");
		set.insert("banana");
		set.insert("orange");
		set.insert("dog");
		REQUIRE(set.size() == 4);
		set.SubstringFilter("o");
		REQUIRE(set.size() == 2);
		REQUIRE(set.count("apple") == 1);
		REQUIRE(set.count("banana") == 1);
		REQUIRE(set.count("orange") == 0);
		REQUIRE(set.count("dog") == 0);
	}
}


// GitHub copilot helped write some initial code for this function
TEST_CASE("Test for Search", "[Search]") {
    // Create a StringSet and insert some strings
    StringSet set;
    set.insert("abc");
    set.insert("abcd");
    set.insert("aXcY");
    set.insert("aXcZ");
    set.insert("xyz");

    // Perform a search with a pattern and check if the result matches the expected output
    StringSet result = set.Search("a?c*");
    REQUIRE(result.size() == 4);
}
// GitHub copilot helped write some initial code for this function
TEST_CASE("Test for Count_occurrence", "[Count_occurrence]") {
    // Create a StringSet and insert some strings
    StringSet set;
    set.insert("abc");
    set.insert("abcd");
    set.insert("aXcY");
    set.insert("aXcZ");
    set.insert("xyz");

    // Check the occurrence count of specific characters in the set
    REQUIRE(set.countOccurence("a") == 4);
    REQUIRE(set.countOccurence("X") == 2);
    REQUIRE(set.countOccurence("z") == 1);
}

TEST_CASE("Test for random_sample", "[random_sample]") {
    // Create a StringSet and insert some strings
    StringSet set;
    set.insert("abc");
    set.insert("abcd");
    set.insert("aXcY");
    set.insert("aXcZ");
    set.insert("xyz");

    // Get a random sample of 2 strings from the set and check if the sample size is correct
    auto samples = set.RandomSample(2);
    REQUIRE(samples.size() == 2);
    // Ensure each sample exists in the set
    for (const auto& sample : samples) {
        REQUIRE(set.count(sample) == 1);
    }

    // Get a random sample of 2 strings from the set with a filter and check if the sample size is correct
    auto filteredSamples = set.RandomSample(2, [](const std::string& str) {
        return str.find('a') != std::string::npos;
    });
    REQUIRE(filteredSamples.size() == 2);
    // Ensure each sample exists in the set and matches the filter
    for (const auto& sample : filteredSamples) {
        REQUIRE(set.count(sample) == 1);
        REQUIRE(sample.find('a') != std::string::npos);
    }

    // Get a random sample of 3 strings from the set with a filter and check if the sample size is correct
    auto filteredSamples2 = set.RandomSample(3, [](const std::string& str) {
        return str.find('X') != std::string::npos;
    });
    REQUIRE(filteredSamples2.size() == 2); // Only 2 strings match the filter
    // Ensure each sample exists in the set and matches the filter
    for (const auto& sample : filteredSamples2) {
        REQUIRE(set.count(sample) == 1);
        REQUIRE(sample.find('X') != std::string::npos);
    }

    // Get a random sample of 3 strings from the set without a filter and check if the sample size is correct
    auto samplesWithoutFilter = set.RandomSample(3);
    REQUIRE(samplesWithoutFilter.size() == 3);
    // Ensure each sample exists in the set
    for (const auto& sample : samplesWithoutFilter) {
        REQUIRE(set.count(sample) == 1);
    }
}

TEST_CASE("Test for Statistic", "[Statistic]") {
    // Create a StringSet and insert some strings
    StringSet set;
    set.insert("abc");
    set.insert("abcd");
    set.insert("aXcY");
    set.insert("aXcZ");
    set.insert("xyz");

    // Get statistics from the set and check if they match the expected values
    // Github copilot helped with the tuple syntax because I forgot it
    auto stats = set.Statistics();
    REQUIRE(std::get<0>(stats) == 5); // Number of strings
    REQUIRE(std::get<1>(stats) == Approx(3.6)); // Average length
    REQUIRE(std::get<2>(stats).size() == 4); // Longest string
    REQUIRE(std::get<3>(stats).size() == 3); // Shortest string
}

TEST_CASE("Tests for SizeFilter", "[SizeFilter]") {
	StringSet set;
	
	SECTION("Filtering an empty set does not cause an error") {
		set.SizeFilter(100);
		REQUIRE(set.size() == 0);
	}
	
	SECTION("Filtering a set with same string lengths should not change it") {
		set.insert({"applee", "banana", "orange"});
		set.SizeFilter(6);
		
		REQUIRE(set.size() == 3);
	}
	
	SECTION("Filtering a set with multiple different elements") {
		set.insert({"apple", "banana", "orange", "ivan", "goose"});
		set.SizeFilter(5);
		
		REQUIRE(set.size() == 2);
		REQUIRE(set.count("apple") == 1);
		REQUIRE(set.count("goose") == 1);
	}
}


TEST_CASE("Test for UnionWith", "[UnionWith]"){
    StringSet set1;
    StringSet set2;

    // Not empty sets
    set1.insert("black");
    set1.insert("blue");
    set1.insert("brown");

    set2.insert("purple");
    set2.insert("white");
    set2.insert("yellow");

    StringSet unionSet = set1.UnionWith(set2, [](const std::string& str){
        return str.find('l') != std::string::npos;
    });
    REQUIRE(unionSet.size() == 4);
    REQUIRE(unionSet.count("black") == 1);
    REQUIRE(unionSet.count("blue") == 1);
    REQUIRE(unionSet.count("purple") == 1);
    REQUIRE(unionSet.count("yellow") == 1);

    // One empty set

    set2.clear();
    unionSet.clear();

    unionSet = set1.UnionWith(set2, [](const std::string& str){
        return str.find('l') != std::string::npos;
    });

    REQUIRE(unionSet.size() == 2);
    REQUIRE(unionSet.count("black") == 1);
    REQUIRE(unionSet.count("blue") == 1);

    // Two empty sets

    set1.clear();
    unionSet.clear();

    unionSet = set1.UnionWith(set2, [](const std::string& str){
        return str.find('l') != std::string::npos;
    });

    REQUIRE(unionSet.size() == 0);
}

TEST_CASE("Test for SymmetricDifference", "[SymmetricDifference]"){
    StringSet set1;
    StringSet set2;

    // Empty sets
    StringSet symmetricSet = set1.SymmetricDifference(set2);

    REQUIRE(symmetricSet.size() == 0);

    // One empty set
    set1.insert("black");
    set1.insert("blue");
    set1.insert("green");

    symmetricSet = set1.SymmetricDifference(set2);
    REQUIRE(symmetricSet.size() == 3);
    REQUIRE(symmetricSet.count("black") == 1);
    REQUIRE(symmetricSet.count("blue") == 1);
    REQUIRE(symmetricSet.count("green") == 1);

    // Not empty sets
    symmetricSet.clear();
    set2.insert("black");
    set2.insert("yellow");
    set2.insert("white");

    symmetricSet = set1.SymmetricDifference(set2);
    REQUIRE(symmetricSet.size() == 4);
    REQUIRE(symmetricSet.count("blue") == 1);
    REQUIRE(symmetricSet.count("green") == 1);
    REQUIRE(symmetricSet.count("yellow") == 1);
    REQUIRE(symmetricSet.count("white") == 1);

    // Try same set
    symmetricSet.clear();
    symmetricSet = set1.SymmetricDifference(set1);
    REQUIRE(symmetricSet.size() == 0);
}

TEST_CASE("Test for ToVector", "[ToVector]"){
    StringSet set1;

    set1.insert("black");
    set1.insert("blue");
    set1.insert("green");
    set1.insert("yellow");

    std::vector<std::string> vec1 = set1.ToVector();

    REQUIRE(vec1.size() == 4);

    // Empty set

    StringSet set2;

    std::vector<std::string> vec2 = set2.ToVector();
    REQUIRE(vec2.size() == 0);
}

TEST_CASE("Test for sort", "[sort]"){
    StringSet set;

    // Empty set

    std::set<std::string> sortedSet = set.sort([](const std::string& str1, const std::string& str2){
        return str1.size() < str2.size();
    });

    std::set<std::string> expected = {};

    REQUIRE(sortedSet == expected);

    set.insert("black");
    set.insert("red");
    set.insert("purple");

    sortedSet = set.sort([](const std::string& str1, const std::string& str2){
        return str1.size() < str2.size();
    });

    expected = {"red", "black", "purple"};

    REQUIRE(sortedSet == expected);

}