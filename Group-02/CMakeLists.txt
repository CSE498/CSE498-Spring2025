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

  # Set Wall, Wextra and Wpedantic flags
  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
  endif ()

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