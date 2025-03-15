#include "../../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../TagManager/TagManager.h"

TEST_CASE("Test AddTag", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("school", "urgent");
    tm.AddTag("school", "low");
    tm.AddTag("school", "medium");
    tm.AddTag("work", "low");
    tm.AddTag("personal", "medium");


    assert(tm.GetTags("school").size() == 3);
    assert(tm.GetTags("work").size() == 1);
    assert(tm.GetTags("personal").size() == 1);
    assert(tm.GetTags("CSE498").empty());

}

TEST_CASE("Test RemoveTag", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("CSE498", "urgent");
    tm.AddTag("CSE498", "work");

    tm.RemoveTag("CSE498", "work");

    assert(tm.GetTags("CSE498").size() == 1);

    tm.RemoveTag("CSE498", "no");
    assert(tm.GetTags("CSE498").size() == 1);
}

TEST_CASE("Test GetTag", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("CSE498", "urgent");
    tm.AddTag("CSE498", "work");

    auto tags = tm.GetTags("CSE498");
    assert(tags.size() == 2);
    assert(tags.count("urgent") == 1);
    assert(tags.count("work") == 1);

    tags = tm.GetTags("no");
    assert(tags.empty());
}

TEST_CASE("Test GetTaskTags", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("CSE498", "urgent");
    tm.AddTag("CSE498", "work");
    tm.AddTag("school", "urgent");

    auto tasks = tm.GetTaskTags("urgent");
    assert(tasks.size() == 2);
    assert(tasks.count("CSE498") == 1);
    assert(tasks.count("school") == 1);
}

TEST_CASE("Test ClearTagForTask", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("CSE498", "urgent");
    tm.AddTag("CSE498", "work");
    tm.AddTag("school", "urgent");

    tm.ClearTagsForTask("CSE498");

    assert(tm.GetTags("CSE498").empty());
    assert(tm.GetTags("school").size() == 1);
}

TEST_CASE("Test ClearTags", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("CSE498", "urgent");
    tm.AddTag("CSE498", "work");
    tm.AddTag("school", "urgent");

    tm.ClearTags("urgent");

    assert(tm.GetTags("school").empty());
    assert(tm.GetTags("CSE498").size() == 1);
}

TEST_CASE("Test HasTag", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("CSE498", "urgent");

    assert(tm.HasTag("CSE498", "urgent"));
    CHECK_FALSE(tm.HasTag("CSE498", "no"));
    CHECK_FALSE(tm.HasTag("school", "urgent"));
}

TEST_CASE("Test removing a tag removes it from task", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("CSE498", "urgent");
    tm.AddTag("CSE498", "work");

    tm.RemoveTag("CSE498", "urgent");

    CHECK_FALSE(tm.HasTag("CSE498", "urgent"));
    assert(tm.HasTag("CSE498", "work"));
}

TEST_CASE("Test ClearTagsForTask remove all associations", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("CSE498", "urgent");
    tm.AddTag("CSE498", "work");

    tm.ClearTagsForTask("CSE498");

    CHECK_FALSE(tm.HasTag("CSE498", "urgent"));
    CHECK_FALSE(tm.HasTag("CSE498", "work"));
}

TEST_CASE("Test ClearTags remove all associations", "[TagManager]") {
    cse::TagManager tm;

    tm.AddTag("CSE498", "urgent");
    tm.AddTag("CSE498", "work");
    tm.AddTag("school", "urgent");

    tm.ClearTags("urgent");

    assert(tm.HasTag("CSE498", "work"));
    CHECK_FALSE(tm.HasTag("CSE498", "urgent"));
    CHECK_FALSE(tm.HasTag("school", "urgent"));
}


