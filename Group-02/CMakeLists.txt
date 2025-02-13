# Base CMake file for cseg2 project

# Set the minimum version of CMake that can be used to build the project
cmake_minimum_required(VERSION 3.14)

set(PROJECT_VERSION 0.1.0)
project(
    cseg2
    VERSION ${PROJECT_VERSION}
    DESCRIPTION "CSE 498 Group 2 Project"
    LANGUAGES CXX
)

set(LIBRARY_NAME cse)
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(BUILD_SHARED_LIBS OFF)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_STANDARD 20)

  # -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
    find_package(Doxygen)

    doxygen_add_docs(
        docs
        ${PROJECT_SOURCE_DIR}
        ALL
        COMMENT "Generate HTML documentation"
        CONFIG_FILE ${PROJECT_SOURCE_DIR}/Doxyfile
    )

  else ()
    message(STATUS "Doxygen not found, not adding docs target")
  endif ()

endif ()

# Add the subdirectories (libraries and executables)
add_subdirectory(src/cse)
add_subdirectory(src/app)

# ========== TEST SETUP ==========
add_subdirectory(include/third-party/Catch)
enable_testing()

file(GLOB_RECURSE TEST_FILES tests/AuditedVector/*.cpp)

add_executable(AuditedVectorTest ${TEST_FILES})

target_link_libraries(AuditedVectorTest PRIVATE Catch2::Catch2)

add_test(NAME AuditedVectorTest COMMAND AuditedVectorTest)

file(GLOB_RECURSE TEST_FILES tests/StateGridPosition/*.cpp)

add_executable(StateGridPositionTest ${TEST_FILES} src/cse/StateGridPosition.cpp)

target_include_directories(StateGridPositionTest PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(StateGridPositionTest PRIVATE Catch2::Catch2)

add_test(NAME StateGridPositionTest COMMAND StateGridPositionTest)

