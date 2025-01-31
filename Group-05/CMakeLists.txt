cmake_minimum_required(VERSION 3.30)
project(hamilton)

set(CMAKE_CXX_STANDARD 20)

add_executable(hamilton main.cpp src/Datum.h src/Datum.cpp)
