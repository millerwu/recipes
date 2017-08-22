cmake_minimum_required(VERSION 2.6)

project(fake_thread C CXX)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(thread_srcs
        Thread.cc
        TimeStamp.cc)

add_library(fake_thread ${thread_srcs})
target_link_libraries(fake_thread pthread)

message(STATUS "start build subdirectory test")
add_subdirectory(test)

