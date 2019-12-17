cmake_minimum_required(VERSION 3.15)
project(Heap)

set(CMAKE_CXX_STANDARD 14)

add_executable(Heap main.cpp TestHeap.h HEAP_TESTER.h)
add_subdirectory(Google_tests)
include_directories(Google_tests/googletest/include)
include_directories(Google_tests/googlemock/include)
target_link_libraries(Heap gtest gtest_main)