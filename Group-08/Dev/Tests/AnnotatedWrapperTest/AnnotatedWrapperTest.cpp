#include "../../AnnotatedWrapper/AnnotatedWrapper.h"
#include "../../../../third-party/Catch/single_include/catch2/catch.hpp"

TEST_CASE("Test cse::AnnotatedWrapper", "[base]")
{
    AnnotatedWrapper wrapper;
    
    SECTION("Check if annotations are added correctly")
    {
        wrapper.addAnnotation("key1", "value1");
        wrapper.addAnnotation("key2", "value2");
        wrapper.addAnnotation("key3", "value3");
        
        REQUIRE(wrapper.getAnnotation("key1") == "value1");
        REQUIRE(wrapper.getAnnotation("key2") == "value2");
        REQUIRE(wrapper.getAnnotation("key3") == "value3");
    }

    SECTION("Check if annotations are removed correctly")
    {
        wrapper.removeAnnotation("key2");
        REQUIRE(wrapper.getAnnotation("key2") == "");
    }

    SECTION("Check if annotations are cleared correctly")
    {
        wrapper.clearAnnotations();
        REQUIRE(wrapper.getAnnotation("key1") == "");
        REQUIRE(wrapper.getAnnotation("key2") == "");
        REQUIRE(wrapper.getAnnotation("key3") == "");
    }

}
