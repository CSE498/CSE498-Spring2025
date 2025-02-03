# CMakeLists.txt for the Tests directory
cmake_minimum_required(VERSION 3.20)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/Team07Library)

# Define source files for tests
set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/Tests/AuditedArrayTest.cpp
    # Add other test files here
)

# Add the test executable
add_executable(MyProjectTests ${TEST_SOURCES})

# Link Google Test libraries and pthread
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(MyProjectTests ${APPLICATION_LIBRARY} GTest::GTest GTest::Main pthread)

# Enable testing
enable_testing()
add_test(NAME MyProjectTests COMMAND MyProjectTests)

