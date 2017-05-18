cmake_minimum_required(VERSION 3.7)
project(n_queens_puzzle)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES solver.cpp solver.h test.cpp)
add_executable(n_queens_puzzle ${SOURCE_FILES})