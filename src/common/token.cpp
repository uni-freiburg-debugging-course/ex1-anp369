//
// Created by andi on 19.10.24.
//
#include "token.h"

Token::Token(const TokenType type, const TokenDetails details) {
    this->details = details;
    this->type = type;
}

Token::Token() {
    details = TokenDetails();
    details.op = NOP;
    details.value = 0;
    type = INVALID;
}
