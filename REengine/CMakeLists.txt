cmake_minimum_required(VERSION 3.5)
project(REengine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp NFA.cpp NFA.h match.h match.cpp)
add_executable(REengine ${SOURCE_FILES})