#include "../../AuditedPointer/AuditedPointer.h"
#include "../../../../third-party/Catch/single_include/catch2/catch.hpp"

#ifdef NDEBUG

TEST_CASE("Test Aptr basic operations", "[Aptr]") {
    Aptr<int> ptr = MakeAudited<int>(42);
    REQUIRE(ptr);
    CHECK(*ptr == 42);
    ptr.Delete();
    CHECK_FALSE(ptr);
}

TEST_CASE("Test Aptr copy constructor", "[Aptr]") {
    Aptr<int> ptr1 = MakeAudited<int>(10);
    Aptr<int> ptr2 = ptr1;
    CHECK(*ptr1 == *ptr2);
    ptr1.Delete();
    ptr2.Delete();
}

TEST_CASE("Test Aptr move constructor", "[Aptr]") {
    Aptr<int> ptr1 = MakeAudited<int>(20);
    Aptr<int> ptr2 = std::move(ptr1);
    CHECK_FALSE(ptr1);
    CHECK(*ptr2 == 20);
    ptr2.Delete();
}

TEST_CASE("Test Aptr copy assignment", "[Aptr]") {
    Aptr<int> ptr1 = MakeAudited<int>(30);
    Aptr<int> ptr2;
    ptr2 = ptr1;
    CHECK(*ptr1 == *ptr2);
    ptr1.Delete();
    ptr2.Delete();
}

TEST_CASE("Test Aptr move assignment", "[Aptr]") {
    Aptr<int> ptr1 = MakeAudited<int>(40);
    Aptr<int> ptr2;
    ptr2 = std::move(ptr1);
    CHECK_FALSE(ptr1);
    CHECK(*ptr2 == 40);
    ptr2.Delete();
}

TEST_CASE("Test Aptr null handling", "[Aptr]") {
    Aptr<int> ptr;
    CHECK_FALSE(ptr);
}

TEST_CASE("Test Aptr multiple allocations", "[Aptr]") {
    Aptr<int> ptr1 = MakeAudited<int>(50);
    Aptr<int> ptr2 = MakeAudited<int>(60);
    CHECK(*ptr1 == 50);
    CHECK(*ptr2 == 60);
    ptr1.Delete();
    ptr2.Delete();
}

#endif
