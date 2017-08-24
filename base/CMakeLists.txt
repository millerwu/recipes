cmake_minimum_required(VERSION 2.6)

project(fake_base C CXX)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(base_srcs
        Thread.cc
        TimeStamp.cc)

add_library(fake_base ${base_srcs})
target_link_libraries(fake_base pthread)

message(STATUS "start build subdirectory test")
add_subdirectory(test)
