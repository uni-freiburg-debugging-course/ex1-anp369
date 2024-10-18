cmake_minimum_required(VERSION 3.29)
project(lisp_parser)

set(CMAKE_CXX_STANDARD 11)


add_executable(lisp_parser main.cpp)
add_subdirectory(src)
