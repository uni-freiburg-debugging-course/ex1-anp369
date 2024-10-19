#include "parser.h"

#include <fstream>
#include <iostream>
//
// Created by andi on 19.10.24.
//

// ---------------------------------------------------------------------------------------------------------------------
Parser::Parser(const bool loggingEnabled) : _isLoggingEnabled(loggingEnabled) {
}

// ---------------------------------------------------------------------------------------------------------------------
ASTNode Parser::parse(std::string &input) {
    this->log(input);
    ASTNode node;
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::log(const std::string &message) {
    if (_isLoggingEnabled) {
        std::cout << "[DBG] " << message << std::endl;
    }
}
