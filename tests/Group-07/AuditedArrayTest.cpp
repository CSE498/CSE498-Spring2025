/**
 * @file AuditedArrayTest.cpp
 * @author Siddhartha Bhattacharya
 */
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-07/Team07Library/AuditedArray.h"

TEST_CASE("AuditedArray Construction", "[AuditedArray]") {
	cse::AuditedArray<int, 5> arr;
}

TEST_CASE("AuditedArray Size", "[AuditedArray]") {
	cse::AuditedArray<int, 5> arr;
	REQUIRE(arr.size() == 5);
}

TEST_CASE("AuditedArray Access", "[AuditedArray]") {
	cse::AuditedArray<int, 5> arr;
	arr[0] = 1;
	REQUIRE(arr[0] == 1);
}

TEST_CASE("AuditedArray Assignment", "[AuditedArray]") {
	cse::AuditedArray<int, 5> arr;
	arr[0] = 1;
	cse::AuditedArray<int, 5> arr2 = arr;

	for (int i = 0; i < 5; i++) {
		REQUIRE(arr2[i] == arr[i]);
	}
}

TEST_CASE("AuditedArray Fill", "[AuditedArray]") {
	cse::AuditedArray<int, 5> arr;
	arr.fill(1);

	for (int i = 0; i < 5; i++) {
		REQUIRE(arr[i] == 1);
	}
}

TEST_CASE("AuditedArray Contains", "[AuditedArray]") {
	cse::AuditedArray<int, 5> arr;
	arr.fill(1);
	arr[1] = 3;

	REQUIRE(arr.contains(3));
	REQUIRE_FALSE(arr.contains(2));
}

TEST_CASE("AuditedArray IndexOf", "[AuditedArray]") {
	cse::AuditedArray<int, 5> arr;
	arr.fill(1);
	arr[1] = 3;

	REQUIRE(arr.indexOf(1) == 0);
	REQUIRE(arr.indexOf(2) == -1);
}
