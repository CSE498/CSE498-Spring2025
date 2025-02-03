# Used Professor Owen's CMake files from CSE 335 for our project
cmake_minimum_required(VERSION 3.20)
project(Group-07)
set(APPLICATION_LIBRARY Team07Library)

set(CMAKE_CXX_STANDARD 23)

# Add subdirectory for the library
add_subdirectory(${APPLICATION_LIBRARY})

# Include directories
include_directories(${APPLICATION_LIBRARY})
include_directories(${CMAKE_SOURCE_DIR}/Team07Library)  # Include Team07Library directory

# Define source files
set(SOURCE_FILES main.cpp)

# Add executable for the main project
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${APPLICATION_LIBRARY})

# Add subdirectory for the tests
add_subdirectory(Tests)

if(APPLE)
    # When building for MacOS, also copy files into the bundle resources
    set(RESOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/team07.app/Contents/Resources)
endif()

