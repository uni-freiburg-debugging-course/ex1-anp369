//
// Created by andi on 19.10.24.
//
#include "token.h"

Token::Token(TokenType type, TokenDetails details) {
    details = details;
    type = type;
}

Token::Token() {
    details = TokenDetails();
    details.op = NOP;
    details.value = 0;
    type = INVALID;
}
