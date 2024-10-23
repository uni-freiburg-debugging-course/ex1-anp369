//
// Created by andi on 19.10.24.
//

#include <gtest/gtest.h>

#include "../src/parser.h"


TEST(Lexer, CorrectOrderOfElements) {
    const std::string statement = "(simplify (* 79 -180))";
    std::vector<Token> correctTokens;

    correctTokens.emplace_back(TokenType::PAR_L, TokenDetails{.op = Operation::NOP});
    correctTokens.emplace_back(TokenType::KEYWORD, TokenDetails{.kw = Keyword::SIMPLIFY});
    correctTokens.emplace_back(TokenType::PAR_L, TokenDetails{.op = Operation::NOP});
    correctTokens.emplace_back(TokenType::OPERATION, TokenDetails{.op = Operation::MULTIPLY});
    correctTokens.emplace_back(TokenType::CONSTANT, TokenDetails{.value = 79});
    correctTokens.emplace_back(TokenType::CONSTANT, TokenDetails{.value = -180});
    correctTokens.emplace_back(TokenType::PAR_R, TokenDetails{.op = Operation::NOP});
    correctTokens.emplace_back(TokenType::PAR_R, TokenDetails{.op = Operation::NOP});

    Parser p(false);
    p.parse(statement);

    ASSERT_EQ(correctTokens.size(), p.mTokens.size());
    for (size_t i = 0; i < correctTokens.size(); i++) {
        ASSERT_EQ(p.mTokens[i], correctTokens[i]);
    }
}