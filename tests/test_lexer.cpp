//
// Created by andi on 19.10.24.
//

#include <gtest/gtest.h>

#include "../src/parser.h"


TEST(Lexer, CorrectOrderOfElements) {
    std::string statement = "(simplify (* 79 -180))";
    std::vector<Token> correctTokens;

    correctTokens.emplace_back(PAR_L, TokenDetails{.op = NOP});
    correctTokens.emplace_back(OPERATION, TokenDetails{.op = SIMPLIFY});
    correctTokens.emplace_back(PAR_L, TokenDetails{.op = NOP});
    correctTokens.emplace_back(OPERATION, TokenDetails{.op = MULTIPLY});
    correctTokens.emplace_back(CONSTANT, TokenDetails{.value = 79});
    correctTokens.emplace_back(CONSTANT, TokenDetails{.value = -180});
    correctTokens.emplace_back(PAR_R, TokenDetails{.op = NOP});
    correctTokens.emplace_back(PAR_R, TokenDetails{.op = NOP});

    Parser p(false);
    p.parse(statement);

    ASSERT_EQ(correctTokens.size(), p._tokens.size());
    for (size_t i = 0; i < correctTokens.size(); i++) {
        ASSERT_EQ(p._tokens[i], correctTokens[i]);
    }
}