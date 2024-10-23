//
// Created by andi on 19.10.24.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <string>


enum class Operation {
    NOP,
    ADD,
    SUBTRACT,
    MULTIPLY,
};

enum class Keyword {
    SIMPLIFY,
};

union TokenDetails {
    Keyword kw;
    Operation op;
    int value;

    bool operator== (const TokenDetails& token) const {
        return op == token.op && value == token.value && kw == token.kw;
    }
};

enum class TokenType {
    INVALID,
    PAR_L,
    PAR_R,
    KEYWORD,
    OPERATION,
    CONSTANT,
};

class Token {
public:
    Token(TokenType pType, TokenDetails pDetails);

    Token();

    std::string toString() const;

    bool operator== (const Token& token) const {
        if (mType != token.mType) {return false;}
        if (mType == TokenType::CONSTANT) {
            return mDetails.value == token.mDetails.value;
        }
        if (mType == TokenType::KEYWORD) {
            return mDetails.kw == token.mDetails.kw;
        }
        return mDetails.op == token.mDetails.op;
    };

    TokenType mType;
    TokenDetails mDetails{};
};

#endif //TOKEN_H
