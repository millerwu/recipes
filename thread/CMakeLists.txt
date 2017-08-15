cmake_minimum_required(VERSION 2.6)

project(fake_thread C CXX)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")

set(thread_srcs
        Thread.cc)

add_library(fake_thread ${thread_srcs})
target_link_libraries(fake_thread pthread)
set_target_properties(fake_thread PROPERTIES COMPILE_FLAGS "-std=c++0x")

add_subdirectory(test)

