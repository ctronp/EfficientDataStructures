cmake_minimum_required(VERSION 3.22)
project(EfficientDataStructures C)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_BUILD_TYPE RelWithDebInfo)
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_C_FLAGS "-O0 -g -flto")
#set(CMAKE_CXX_FLAGS "-O0 -g -flto")


add_library(headers-lib INTERFACE)
target_include_directories(headers-lib INTERFACE src/**)

add_executable(main_test main.c)
target_link_libraries(main_test headers-lib)


add_subdirectory(Google_tests)