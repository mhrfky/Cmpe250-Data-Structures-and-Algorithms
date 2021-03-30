cmake_minimum_required(VERSION 1.6)
project(project4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(project4 ${SOURCE_FILES})