#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../AnnotatedWrapper/AnnotatedWrapper.h"
#include <sstream>

TEST_CASE("Test AnnotatedWrapper default construction", "[AnnotatedWrapper]") {
    cse::AnnotatedWrapper wrapper;

    // Test adding annotations with different types (string, number, key-value pairs)
    wrapper.addAnnotation("fontSize", 12.5f); // Add a float annotation
    wrapper.addAnnotation("fontColor", "blue"); // Add a string annotation
    wrapper.addAnnotation("background", "color", "white"); // Add a key-value pair

    CHECK(wrapper.getAnnotation("fontSize") == "12.5f");
    CHECK(wrapper.getAnnotation("fontColor") == "blue");
    CHECK(wrapper.getAnnotation("background") == "white"); // check different annotation types

    // Test retrieving annotations with type mismatch
    CHECK_THROWS_AS(wrapper.getAnnotation("fontSize"), std::bad_variant_access);

    // Test handling duplicate keys (overwriting)
    wrapper.addAnnotation("fontSize", 14.0f); // Overwrite the existing key
    CHECK(wrapper.getAnnotation("fontSize") == "14.0f");

    // Test removing a non-existent annotation
    CHECK_NOTHROW(wrapper.removeAnnotation("nonExistentKey")); // Should not throw

    // Test accessing a non-existent annotation
    CHECK_THROWS_AS(wrapper.getAnnotation("nonExistentKey"), std::out_of_range);

    // Test clearAnnotations()
    wrapper.clearAnnotations();
    CHECK(wrapper.getAnnotationCount() == 0);

    // Test integration with DataMap
    wrapper.addAnnotation("metadata", "width", "500");
    auto metadata = wrapper.getAnnotation("metadata");

    // Test empty key names
    CHECK_THROWS_AS(wrapper.addAnnotation("", "value"), std::invalid_argument);
}
