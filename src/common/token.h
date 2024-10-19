//
// Created by andi on 19.10.24.
//

#ifndef TOKEN_H
#define TOKEN_H


enum Operation {
    NOP,
    SIMPLIFY,
    ADD,
    SUBTRACT,
    MULTIPLY,
};

union TokenDetails {
    Operation op;
    int value;

    bool operator== (const TokenDetails& token) const {
        return op == token.op && value == token.value;
    }
};

enum TokenType {
    INVALID,
    PAR_L,
    PAR_R,
    OPERATION,
    CONSTANT,
};

class Token {
public:
    Token(TokenType type, TokenDetails details);

    Token();

    bool operator== (const Token& token) const {
        if (type != token.type) {return false;}
        if (type == CONSTANT) {
            return details.value == token.details.value;
        }
        return details.op == token.details.op;
    };

    TokenType type;
    TokenDetails details{};
};

#endif //TOKEN_H
