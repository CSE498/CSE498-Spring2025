cmake_minimum_required(VERSION 3.20)
project(Team07Library)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/Team07Library)

# Define source and header files
set(LIBRARY_SOURCES
    ${CMAKE_SOURCE_DIR}/Team07Library/AuditedArray.cpp
    # Add other source files here
)

set(LIBRARY_HEADERS
    ${CMAKE_SOURCE_DIR}/Team07Library/AuditedArray.h
    # Add other header files here
)

# Create the library
add_library(${PROJECT_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

