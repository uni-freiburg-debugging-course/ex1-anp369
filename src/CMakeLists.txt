target_sources(lisp_parser PUBLIC lexer.cpp)

target_link_libraries(lisp_parser boost_program_options)
target_include_directories(lisp_parser PUBLIC ../inlclude)