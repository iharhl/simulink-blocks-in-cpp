cmake_minimum_required(VERSION 3.12)
project(SimulinkBlocksInCpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

# Include so that testcase can call headers
include_directories(src)

add_subdirectory(src)
add_subdirectory(test)