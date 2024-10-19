add_subdirectory(common)

target_sources(lisp_parser PUBLIC parser.h parser.cpp)
target_include_directories(lisp_parser PUBLIC .)

target_sources(lisp_parser_test PUBLIC parser.h parser.cpp)
target_include_directories(lisp_parser_test PUBLIC .)

