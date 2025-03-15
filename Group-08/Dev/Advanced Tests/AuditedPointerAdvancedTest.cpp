#include "../../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../AuditedPointer/AuditedPointer.h"

TEST_CASE("Test Aptr advanced operations", "[Aptr]") 
{
    // Test ID assignment and retrieval
    cse::Aptr<int> Aptr1 = cse::MakeAudited<int>(10);
    cse::Aptr<int> Aptr2 = cse::MakeAudited<int>(20);

    CHECK(Aptr1.GetID() != Aptr2.GetID()); // IDs should be unique
    CHECK(Aptr1.GetID() > 0); // IDs should be positive
    CHECK(Aptr2.GetID() > 0);

    // Test active Aptr tracking
    auto activeAptrs = cse::Aptr<int>::GetActiveAptrs();
    CHECK(activeAptrs.size() == 2); // Both pointers should be active
    CHECK(activeAptrs.find(Aptr1.GetID()) != activeAptrs.end());
    CHECK(activeAptrs.find(Aptr2.GetID()) != activeAptrs.end());

    // Test deletion and removal from active set
    int id = Aptr1.GetID();
    Aptr1.Delete(); // Delete the Aptr
    activeAptrs = cse::Aptr<int>::GetActiveAptrs();
    CHECK(activeAptrs.find(id) == activeAptrs.end()); // Should no longer be in the active set

    // Test Reset function
    cse::Aptr<int>::Reset(); // Reset all active Aptrs
    activeAptrs = cse::Aptr<int>::GetActiveAptrs();
    CHECK(activeAptrs.empty()); // Active set should be empty after reset

    Aptr2.Delete();
}
