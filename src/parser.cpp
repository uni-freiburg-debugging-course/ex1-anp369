#include <iostream>

#include "parser.h"
#include "common/token.h"

//
// Created by andi on 19.10.24.
//

// ---------------------------------------------------------------------------------------------------------------------
Parser::Parser(const bool loggingEnabled) : _isLoggingEnabled(loggingEnabled) {
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::log(const std::string &message) const {
    if (_isLoggingEnabled) {
        std::cout << "[DBG] " << message << std::endl;
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::_handleInvalid() const {
    std::cerr << "Invalid input: " << _currentInput << "at character \'"
            << _currentInput[_currentPos] << '\'' << std::endl;
    exit(EXIT_FAILURE);
}

// ---------------------------------------------------------------------------------------------------------------------
ASTNode Parser::parse(const std::string &input) {
    _currentInput = input;
    _currentPos = 0;
    this->log("Parsing: " + input);

    while (_currentPos < _currentInput.length() - 1) {
        const auto &c = _currentInput[_currentPos];
        if (std::isdigit(c)) _tokenizeDigit(c);
        else if (std::isalpha(c)) _tokenizeAlpha(std::tolower(c));
        else if (c == '(' || c == ')') _tokenizeParantheses(c);
        else if (c == ' ') _tokenizeSpace();
        else if (c == '+' || c == '-' || c == '*') _tokenizeOperationChar(c);
        else _handleInvalid();
    }

    // Lexing done begin parsing
    ASTNode root;
    return root;
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::_tokenizeParantheses(char c) {
    TokenDetails det{.op = NOP};
    if (c == '(') _tokens.emplace_back(PAR_L, det);
    else if (c == ')') _tokens.emplace_back(PAR_R, det);
    _currentPos++;
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::_tokenizeSpace() {
    _currentPos++;
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::_tokenizeDigit(char c) {
    const size_t nextSpace = _currentInput.find(' ', _currentPos);
    const size_t nextParR = _currentInput.find(')', _currentPos);
    int number;
    if (nextSpace != std::string::npos) {
        const std::string nextNumber = _currentInput.substr(_currentPos, nextSpace - _currentPos);
        number = std::stoi(nextNumber);
        _currentPos = nextSpace;
    }
    else if (nextParR != std::string::npos) {
        const std::string nextNumber = _currentInput.substr(_currentPos, nextParR - _currentPos);
        number = std::stoi(nextNumber);
        _currentPos = nextParR;
    }
    if (nextSpace != std::string::npos || nextParR != std::string::npos) {
        TokenDetails det{.value = number};
        _tokens.emplace_back(CONSTANT, det);
        return;
    }

    _handleInvalid();
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::_tokenizeAlpha(char c) {
    const size_t nextSpace = _currentInput.find(' ', _currentPos);
    if (nextSpace != std::string::npos) {
        const std::string nextOp = _currentInput.substr(_currentPos, nextSpace - _currentPos);
        if (nextOp == "simplify") {
            TokenDetails det{.op = SIMPLIFY};
            _tokens.emplace_back(TokenType::OPERATION, det);
            _currentPos = nextSpace;
            return;
        }
        _handleInvalid();
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::_tokenizeOperationChar(char c) {
    if (c == '-' && std::isdigit(_currentInput[_currentPos + 1])) {
        _tokenizeDigit(c);
    } else {
        TokenDetails det{};
        if (c == '-') {
            det = {.op = SUBTRACT};
        }
        if (c == '*') {
            det = {.op = MULTIPLY};
        }
        if (c == '+') {
            det = {.op = ADD};
        }
        _tokens.emplace_back(TokenType::OPERATION, det);
        _currentPos++;
    }
}

//  ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
