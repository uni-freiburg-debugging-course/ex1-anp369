cmake_minimum_required(VERSION 3.29)
project(lisp_parser)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra)

add_executable(lisp_parser main.cpp)
target_link_libraries(lisp_parser boost_program_options)

add_executable(lisp_parser_test tests/main.cpp)
target_link_libraries(lisp_parser_test PRIVATE gtest)
target_include_directories(lisp_parser_test PUBLIC src)

add_executable(fuzzer src/fuzzer.cpp)


add_subdirectory(src)
add_subdirectory(tests)
