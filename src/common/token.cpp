//
// Created by andi on 19.10.24.
//
#include "token.h"

Token::Token(const TokenType pType, const TokenDetails pDetails) {
    this->mDetails = pDetails;
    this->mType = pType;
}

Token::Token() {
    mDetails = TokenDetails{};
    mDetails.op = Operation::NOP;
    mDetails.value = 0;
    mType = TokenType::INVALID;
}

std::string Token::toString() const {
    std::string value;
    switch (mType) {
        case TokenType::PAR_L:
            value += "PAR_L";
            break;
        case TokenType::PAR_R:
            value += "PAR_R";
            break;
        case TokenType::INVALID:
            value += "INVALID";
            break;
        case TokenType::KEYWORD:
            value += "KEYWORD: ";
            switch (mDetails.kw) {
                case Keyword::SIMPLIFY:
                    value += "SIMPLIFY";
            }
            break;
        case TokenType::OPERATION:
            value += "OPERATION: ";
            switch (mDetails.op) {
                case Operation::NOP:
                    value += "NOP";
                    break;
                case Operation::ADD:
                    value += "ADD";
                    break;

                case Operation::SUBTRACT:
                    value += "SUBTRACT";
                    break;

                case Operation::MULTIPLY:
                    value += "MULTIPLY";
                    break;
            }
            break;
        case TokenType::CONSTANT:
            value += "CONSTANT: ";
            value += std::to_string(mDetails.value);
            break;
        default: value += "UNKNOWN";
    }

    return value;
}
