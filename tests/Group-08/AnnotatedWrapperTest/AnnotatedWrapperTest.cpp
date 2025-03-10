 #include "../../../../third-party/Catch/single_include/catch2/catch.hpp"
 #include "../../AnnotatedWrapper/AnnotatedWrapper.h"
 using namespace cse;

TEST_CASE("Test AnnotatedWrapper default construction", "[AnnotatedWrapper]") {
    AnnotatedWrapper wrapper;
    CHECK(wrapper.getAnnotation("key1").empty());
    CHECK(wrapper.getAnnotation("key2").empty());
}

TEST_CASE("Test AnnotatedWrapper addAnnotation operation", "[AnnotatedWrapper]") {
    AnnotatedWrapper wrapper;
    wrapper.addAnnotation("key1", "value1");
    wrapper.addAnnotation("key2", "value2");
    wrapper.addAnnotation("key3", "value3");

    CHECK(wrapper.getAnnotation("key1") == "value1");
    CHECK(wrapper.getAnnotation("key2") == "value2");
    CHECK(wrapper.getAnnotation("key3") == "value3");
}

TEST_CASE("Test AnnotatedWrapper getAnnotation operation", "[AnnotatedWrapper]") {
    AnnotatedWrapper wrapper;
    wrapper.addAnnotation("keyA", "valueA");
    wrapper.addAnnotation("keyB", "valueB");

    CHECK(wrapper.getAnnotation("keyA") == "valueA");
    CHECK(wrapper.getAnnotation("keyB") == "valueB");
    CHECK(wrapper.getAnnotation("keyC").empty());
}

TEST_CASE("Test AnnotatedWrapper removeAnnotation operation", "[AnnotatedWrapper]") {
    AnnotatedWrapper wrapper;
    wrapper.addAnnotation("key1", "value1");
    wrapper.addAnnotation("key2", "value2");

    wrapper.removeAnnotation("key2");
    CHECK(wrapper.getAnnotation("key2").empty());
    CHECK(wrapper.getAnnotation("key1") == "value1");
}

TEST_CASE("Test AnnotatedWrapper clearAnnotations operation", "[AnnotatedWrapper]") {
    AnnotatedWrapper wrapper;
    wrapper.addAnnotation("key1", "value1");
    wrapper.addAnnotation("key2", "value3");

    wrapper.clearAnnotations();
    CHECK(wrapper.getAnnotation("key1").empty());
    CHECK(wrapper.getAnnotation("key2").empty());
    
}

TEST_CASE("Test AnnotatedWrapper overwriteAnnotation operation", "[AnnotatedWrapper]") {
    AnnotatedWrapper wrapper;
    wrapper.addAnnotation("key1", "value1");
    wrapper.addAnnotation("key1", "newValue");

    CHECK(wrapper.getAnnotation("key1") == "newValue");
}

TEST_CASE("Test AnnotatedWrapper add and remove multiple annotations", "[AnnotatedWrapper]") {
    AnnotatedWrapper wrapper;
    wrapper.addAnnotation("key1", "value1");
    wrapper.addAnnotation("key2", "value2");
    wrapper.addAnnotation("key3", "value3");

    CHECK(wrapper.getAnnotation("key1") == "value1");
    CHECK(wrapper.getAnnotation("key2") == "value2");
    CHECK(wrapper.getAnnotation("key3") == "value3");

    wrapper.removeAnnotation("key1");
    wrapper.removeAnnotation("key3");

    CHECK(wrapper.getAnnotation("key1").empty());
    CHECK(wrapper.getAnnotation("key2") == "value2");
    CHECK(wrapper.getAnnotation("key3").empty());
}