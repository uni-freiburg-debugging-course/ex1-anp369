//
// Created by andi on 19.10.24.
//

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <istream>
#include <memory>

#include "util/ASTNode.h"

class Parser {
public:
    ///
    /// Instantiate the Parser class and hand it an istream. This could either be an input file
    /// or stdin.
    /// @param loggingEnabled if enabled, emit logging info for lexing and parsing
    Parser(bool loggingEnabled);

    /// parses the given input and returns an AST if successful, fails with exit(EXIT_FAILURE) otherwise
    /// @param input string containing the lisp expression to parse
    /// @return root node of the constructed AST
    ASTNode parse(std::string &input);

private:
    bool _isLoggingEnabled;

    ///
    /// @param message logs the given message to stdout if enabled
    void log(const std::string &message);
};

#endif //PARSER_H
