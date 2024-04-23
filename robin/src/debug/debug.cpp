//
// Created by icelake on 24-4-23.
//

#include "debug.h"

void printRequestedTokenList(std::vector<Token::Token> tokenList) {
    for (const auto &token: tokenList) {
        std::cout << token.toString() << std::endl;
    }
}