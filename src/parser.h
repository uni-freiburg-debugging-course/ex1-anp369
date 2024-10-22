//
// Created by andi on 19.10.24.
//

#ifndef PARSER_H
#define PARSER_H

#include <memory>
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
    std::unique_ptr<ASTNode>& parse(const std::string &input);

private:
    FRIEND_TEST(Lexer, CorrectOrderOfElements);
    bool mIsLoggingEnabled;

    /// the expression that currently gets parsed
    std::string mCurrentInput;

    /// holds already discovered tokens in order they occured
    std::vector<Token> mTokens;

    std::unique_ptr<ASTNode> mAstRoot;

    /// holds the position the lexer is currently at in the search string
    unsigned int mCurrentPos = 0;

    /// @param message logs the given message to stdout if enabled
    void log(const std::string &message) const;

    /// prints an error message to the user in case of invalid input encountered during lexing
    void handleInvalidLexing() const;

    /// prints an error message that occured during parsing
    void handleInvalidParsing(const Token& pToken) const;
    // LEXING FUNCTIONS

    /// returns a token object for the given paranthesis
    /// @param pChar
    /// @return
    void tokenizeParantheses(char pChar);

    /// processes an encountered space in the string
    void tokenizeSpace();

    /// @param pChar
    /// @return
    void tokenizeDigit(char pChar);

    /// processes alphanumeric characters
    void tokenizeAlpha(char pChar);

    /// processes '+', '*', '-'
    void tokenizeOperationChar(char pChar);

    // PARSING FUNCTIONS
    /// starts building the AST from the lexed tokens
    std::unique_ptr<ASTNode> parseTokens(const std::vector<Token>& pTokens);
};

#endif //PARSER_H
