if (!LIBRARY_NAME)
  # If the LIBRARY_NAME is not set, set it to cse
  set(LIBRARY_NAME cse)
endif ()

message(STATUS "Building Library: ${LIBRARY_NAME}")

# Set the header and source files
set(
    HEADER_FILES
    ${PROJECT_SOURCE_DIR}/include/cse/ActionMap.h
    ${PROJECT_SOURCE_DIR}/include/cse/StateGrid.h
    ${PROJECT_SOURCE_DIR}/include/cse/StateGridPosition.h
    ${PROJECT_SOURCE_DIR}/include/cse/AuditedVector.h
        ${PROJECT_SOURCE_DIR}/include/cse/DataMap.hpp
    ${PROJECT_SOURCE_DIR}/include/cse/AdvancedDataMap.hpp
)

set(
    SOURCE_FILES
    ActionMap.cpp
    StateGrid.cpp
    StateGridPosition.cpp
    AuditedVector.cpp
    DataMap.cpp
    AdvancedDataMap.cpp
)

# Add the library target
if (BUILD_SHARED_LIBS)
  # Set the export all symbols flag when building on Windows (for shared libraries)
  # (kernel32.dll, user32.dll, etc.)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
  add_library(${LIBRARY_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
else ()
  add_library(${LIBRARY_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
endif ()

# Set default compile flags for GCC
if (CMAKE_COMPILER_IS_GNUCXX)
  message(STATUS "GCC detected, adding compile flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wall -Wextra")
endif (CMAKE_COMPILER_IS_GNUCXX)

# Set the include directories
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Set the C++ standard to C++20
target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_20)