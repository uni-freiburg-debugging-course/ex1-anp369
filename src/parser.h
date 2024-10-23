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
    void parse(const std::string &input);

    // resets the parser to accept a new expression
    void reset();

private:
    FRIEND_TEST(Lexer, CorrectOrderOfElements);
    bool mIsLoggingEnabled;

    /// the expression that currently gets parsed
    std::string mCurrentInput;

    /// holds already discovered tokens in order they occurred
    std::vector<Token> mTokens;

    std::unique_ptr<ASTNode> mAstRoot;

    /// holds the position the lexer is currently at in the search string
    unsigned int mCurrentPos = 0;

    /// @param message logs the given message to stdout if enabled
    void log(const std::string &message) const;

    /// prints an error message to the user in case of invalid input encountered during lexing
    void handleInvalidLexing() const;

    /// prints an error message that occurred during parsing
    void handleInvalidParsing(const Token& pToken) const;

    // LEXING FUNCTIONS
    // lexes the string stored in the mCurrentInput field
    void lexString();

    /// returns a token object for the given parenthesis
    /// @param pChar
    /// @return
    void tokenizeParantheses(char pChar);

    /// processes an encountered space in the string
    void tokenizeSpace();

    /// @return
    void tokenizeDigit();

    /// processes alphanumeric characters
    void tokenizeAlpha();

    /// processes '+', '*', '-'
    void tokenizeOperationChar(char pChar);

    // PARSING FUNCTIONS
    /// starts building the AST from the lexed tokens
    std::unique_ptr<ASTNode> parseTokens();

    // EVALUATOR FUNCTIONS

    // starts evaluating the AST starting at mAstRoot
    void evaluate();
};

#endif //PARSER_H
