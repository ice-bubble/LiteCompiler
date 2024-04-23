/**
 * @file debug.cpp
 * @brief debug函数的实现。
 * @author lzy
 * @date 24-4-23
 */

#include "debug.h"

void printTokenList(const std::vector<Token::Token>& tokenList) {
    for (const auto &token: tokenList) {
        std::cout << token.toString() << std::endl;
    }
}