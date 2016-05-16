cmake_minimum_required(VERSION 3.5)
project(HetAST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp HeteroAST.h  Token.h  AsignNode.h  ExprNode.h  StatNode.h  AddNode.h  PrintNode.h  IntNode.h  VarNode.h)
add_executable(HetAST ${SOURCE_FILES})