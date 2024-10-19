add_subdirectory(util)

target_sources(lisp_parser PUBLIC parser.h parser.cpp)
target_include_directories(lisp_parser PUBLIC .)

target_link_libraries(lisp_parser boost_program_options)