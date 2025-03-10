cmake_minimum_required(VERSION 3.30)
project(hamilton)

set(CMAKE_CXX_STANDARD 20)

add_executable(hamilton src/ExpressionParser.h src/ExpressionParser.cpp src/DataGrid.h src/DataGrid.cpp src/Datum.h src/Datum.cpp src/CSVfile.h src/CSVfile.cpp src/ReferenceVector.h)
