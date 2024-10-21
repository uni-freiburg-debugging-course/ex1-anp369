//
// Created by andi on 19.10.24.
//

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <gtest/gtest_prod.h>

#include "common/astnode.h"
#include "common/token.h"

class Parser {
public:
    ///
    /// Instantiate the Parser class and hand it an istream. This could either be an input file
    /// or stdin.
    /// @param loggingEnabled if enabled, emit logging info for lexing and parsing
    explicit Parser(bool loggingEnabled);

    /// parses the given input and returns an AST if successful, fails with exit(EXIT_FAILURE) otherwise
    /// @param input string containing the lisp expression to parse
    /// @return root node of the constructed AST
    ASTNode parse(const std::string &input);

private:
    FRIEND_TEST(Lexer, CorrectOrderOfElements);
    bool _isLoggingEnabled;

    /// buffer during tokenizing for memorizing the current expected token
    TokenType _currentGuess = TokenType::INVALID;

    /// the expression that currently gets parsed
    std::string _currentInput;

    /// holds already discovered tokens in order they occured
    std::vector<Token> _tokens;

    /// holds the position the lexer is currently at in the search string
    unsigned int _currentPos = 0;

    /// @param message logs the given message to stdout if enabled
    void log(const std::string &message) const;

    /// prints an error message to the user in case of invalid input
    void _handleInvalid() const;

    // LEXING FUNCTIONS

    /// returns a token object for the given paranthesis
    /// @param c
    /// @return
    void _tokenizeParantheses(char c);

    /// processes an encountered space in the string
    void _tokenizeSpace();

    /// @param c
    /// @return
    void _tokenizeDigit(char c);

    /// processes alphanumeric characters
    void _tokenizeAlpha(char c);

    /// processes '+', '*', '-'
    void _tokenizeOperationChar(char c);

    // PARSING FUNCTIONS
    /// starts building the AST from the lexed tokens
    ASTNode _parseToken(const std::vector<Token> &tokens);
};

#endif //PARSER_H
