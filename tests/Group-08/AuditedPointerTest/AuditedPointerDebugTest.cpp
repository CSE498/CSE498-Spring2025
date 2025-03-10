#include "../../../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../AuditedPointer/AuditedPointer.h"

TEST_CASE("Test cse::Aptr basic operations", "[cse::Aptr]") {
    cse::Aptr<int> ptr = cse::MakeAudited<int>(42);
    REQUIRE(ptr);
    CHECK(*ptr == 42);
    ptr.Delete();
    CHECK_FALSE(ptr);
}

TEST_CASE("Test cse::Aptr copy constructor", "[cse::Aptr]") {
    cse::Aptr<int> ptr1 = cse::MakeAudited<int>(10);
    cse::Aptr<int> ptr2 = ptr1;
    CHECK(*ptr1 == *ptr2);
    ptr1.Delete();
    ptr2.Delete();
}

TEST_CASE("Test cse::Aptr move constructor", "[cse::Aptr]") {
    cse::Aptr<int> ptr1 = cse::MakeAudited<int>(20);
    cse::Aptr<int> ptr2 = std::move(ptr1);
    CHECK_FALSE(ptr1);
    CHECK(*ptr2 == 20);
    ptr2.Delete();
}

TEST_CASE("Test cse::Aptr copy assignment", "[cse::Aptr]") {
    cse::Aptr<int> ptr1 = cse::MakeAudited<int>(30);
    cse::Aptr<int> ptr2;
    ptr2 = ptr1;
    CHECK(*ptr1 == *ptr2);
    ptr1.Delete();
    ptr2.Delete();
}

TEST_CASE("Test cse::Aptr move assignment", "[cse::Aptr]") {
    cse::Aptr<int> ptr1 = cse::MakeAudited<int>(40);
    cse::Aptr<int> ptr2;
    ptr2 = std::move(ptr1);
    CHECK_FALSE(ptr1);
    CHECK(*ptr2 == 40);
    ptr2.Delete();
}

TEST_CASE("Test cse::Aptr null handling", "[cse::Aptr]") {
    cse::Aptr<int> ptr;
    CHECK_FALSE(ptr);
}

TEST_CASE("Test cse::Aptr multiple allocations", "[cse::Aptr]") {
    cse::Aptr<int> ptr1 = cse::MakeAudited<int>(50);
    cse::Aptr<int> ptr2 = cse::MakeAudited<int>(60);
    CHECK(*ptr1 == 50);
    CHECK(*ptr2 == 60);
    ptr1.Delete();
    ptr2.Delete();
}
