cmake_minimum_required(VERSION 3.22)
project(EfficientDataStructures C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
include(CTest)

add_library(headers-lib INTERFACE)
target_link_directories(headers-lib INTERFACE src)

add_subdirectory(tests)
