cmake_minimum_required(VERSION 3.5)
project(JsonParser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp lex.cpp lex.h json.h json.cpp  parser.cpp parser.h)
add_executable(JsonParser ${SOURCE_FILES})