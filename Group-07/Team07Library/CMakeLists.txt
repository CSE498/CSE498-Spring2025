#Used Professor Owen's CMake files for CSE 335 for our project

project(Team07Library)

set(SOURCE_FILES
        AuditedArray.cpp
        AuditedArray.h
        DataFileManager.cpp
        DataFileManager.h
        OutputLog.cpp
        OutputLog.h
        Scheduler.cpp
        Scheduler.h
        Serializer.cpp
        Serializer.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})