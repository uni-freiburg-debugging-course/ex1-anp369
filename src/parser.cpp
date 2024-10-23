#include <iostream>
#include <memory>

#include "parser.h"
#include "common/token.h"

//
// Created by andi on 19.10.24.
//

// ---------------------------------------------------------------------------------------------------------------------
Parser::Parser(const bool loggingEnabled) : mIsLoggingEnabled(loggingEnabled) {
    mAstRoot = std::make_unique<ASTNode>();
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::log(const std::string &message) const {
    if (mIsLoggingEnabled) {
        std::cout << "[DBG] " << message << std::endl;
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::handleInvalidLexing() const {
    fprintf(stderr, "Invalid input: %s at character %c ('\\%x') at index %d",
            mCurrentInput.c_str(), mCurrentInput[mCurrentPos], mCurrentInput[mCurrentPos], mCurrentPos);
    exit(EXIT_FAILURE);
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::handleInvalidParsing(const Token &pToken) const {
    fprintf(stderr, "Error while parsing token %s", pToken.toString().c_str());
    exit(EXIT_FAILURE);
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::lexString() {
    while (mCurrentPos < mCurrentInput.length()) {
        const auto &c = mCurrentInput[mCurrentPos];
        if (std::isdigit(c)) tokenizeDigit();
        else if (std::isalpha(c)) tokenizeAlpha();
        else if (c == '(' || c == ')') tokenizeParantheses(c);
        else if (c == ' ') tokenizeSpace();
        else if (c == '+' || c == '-' || c == '*') tokenizeOperationChar(c);
        else handleInvalidLexing();
    }

    // post-processing, remove initial and ending parantheses
    if (mTokens.front().mType == TokenType::PAR_L && mTokens.back().mType == TokenType::PAR_R) {
        mTokens.erase(mTokens.begin());
        mTokens.erase(mTokens.end());
    }
}

// ---------------------------------------------------------------------------------------------------------------------
std::unique_ptr<ASTNode> &Parser::parse(const std::string &input) {
    mCurrentInput = input;
    mCurrentPos = 0;
    this->log("Parsing: " + input);

    lexString();

    // Lexing done begin parsing
    mAstRoot = std::move(parseTokens());
    return mAstRoot;
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::tokenizeParantheses(char pChar) {
    if (pChar == '(') mTokens.emplace_back(TokenType::PAR_L, TokenDetails{.op = Operation::NOP});
    else if (pChar == ')') mTokens.emplace_back(TokenType::PAR_R, TokenDetails{.op = Operation::NOP});
    mCurrentPos++;
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::tokenizeSpace() {
    mCurrentPos++;
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::tokenizeDigit() {
    const size_t nextSpace = mCurrentInput.find(' ', mCurrentPos);
    const size_t nextParR = mCurrentInput.find(')', mCurrentPos);
    int number;
    if (nextSpace != std::string::npos) {
        const std::string nextNumber = mCurrentInput.substr(mCurrentPos, nextSpace - mCurrentPos);
        number = std::stoi(nextNumber);
        mTokens.emplace_back(TokenType::CONSTANT, TokenDetails{.value = number});
        mCurrentPos = nextSpace;
        return;
    }
    if (nextParR != std::string::npos) {
        const std::string nextNumber = mCurrentInput.substr(mCurrentPos, nextParR - mCurrentPos);
        number = std::stoi(nextNumber);
        mTokens.emplace_back(TokenType::CONSTANT, TokenDetails{.value = number});
        mCurrentPos = nextParR;
        return;
    }
    handleInvalidLexing();
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::tokenizeAlpha() {
    const size_t nextSpace = mCurrentInput.find(' ', mCurrentPos);
    if (nextSpace != std::string::npos) {
        const std::string nextOp = mCurrentInput.substr(mCurrentPos, nextSpace - mCurrentPos);
        if (nextOp == "simplify") {
            TokenDetails det{.kw = Keyword::SIMPLIFY};
            mTokens.emplace_back(TokenType::KEYWORD, det);
            mCurrentPos = nextSpace;
            return;
        }
        handleInvalidLexing();
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void Parser::tokenizeOperationChar(char pChar) {
    if (pChar == '-' && std::isdigit(mCurrentInput[mCurrentPos + 1])) {
        tokenizeDigit();
    } else {
        TokenDetails det{};
        if (pChar == '-') {
            det = {.op = Operation::SUBTRACT};
        }
        if (pChar == '*') {
            det = {.op = Operation::MULTIPLY};
        }
        if (pChar == '+') {
            det = {.op = Operation::ADD};
        }
        mTokens.emplace_back(TokenType::OPERATION, det);
        mCurrentPos++;
    }
}

//  ---------------------------------------------------------------------------------------------------------------------
std::unique_ptr<ASTNode> Parser::parseTokens() {
    /* check first token
     * if it is an opening par '(' eat it (rm from vector) for now and search at i+1
     * if not, then assign the next token to the root node
     * if it is an opening par '(' recursively search slice [i+1:] of the tokens and assign result to left child
     * if not assign token to the left child
     * check next token
     * if it is an opening par '(' recursively search slice [i+1:] of the tokens and assign result to right child
     * if not assign it to the right child
     * make sure the next token is a closing par ')', otherwise abort parsing with an error message
     */
    std::unique_ptr<ASTNode> root = std::make_unique<ASTNode>();
    constexpr unsigned int first = 0;

    // parse expression root
    if (mTokens.at(0).mType == TokenType::PAR_L) {
        //auto cpVec = std::vector<Token>(mTokens.begin() + first + 1, mTokens.end());
        this->mTokens.erase(mTokens.begin());
        root = std::move(parseTokens());
    } else {
        root->mAction = mTokens[first];
        mTokens.erase(mTokens.begin());
    }


    // parse left child
    if (mTokens[first].mType == TokenType::PAR_L) {
        //auto cpVec = std::vector<Token>(mTokens.begin() + first + 1, mTokens.end());
        this->mTokens.erase(mTokens.begin());
        root->mLeft = std::move(parseTokens());
    } else {
        root->mLeft = std::make_unique<ASTNode>();
        root->mLeft->mAction = mTokens[first];
        mTokens.erase(mTokens.begin());
    }


    // parse right child
    // skip in case of simplify keywords as they only have one child
    if (!(root->mAction.mType == TokenType::KEYWORD && mAstRoot->mAction.mDetails.kw == Keyword::SIMPLIFY)) {
        if (mTokens[first].mType == TokenType::PAR_L) {
            //auto cpVec = std::vector<Token>(mTokens.begin() + first + 1, mTokens.end());
            mTokens.erase(mTokens.begin());
            root->mRight = std::move(parseTokens());
        } else {
            root->mRight = std::make_unique<ASTNode>();
            root->mRight->mAction = mTokens[first];
            mTokens.erase(mTokens.begin());
        }
    }
    if (mTokens[first].mType == TokenType::PAR_R) {
        mTokens.erase(mTokens.begin());
        return root;
    }
    handleInvalidParsing(mTokens[first]);
    exit(1);
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
void Parser::evaluate() {

}
