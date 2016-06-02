cmake_minimum_required(VERSION 3.5)
project(TINY)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp  Scanner.h Token.h  Parser.h Tree.h)
add_executable(TINY ${SOURCE_FILES})