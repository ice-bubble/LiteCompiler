/**
 * @file debug.h
 * @brief debug函数的声明。
 * @author lzy
 * @date 24-4-23
 */
#ifndef ROBIN_DEBUG_H
#define ROBIN_DEBUG_H

#include "../common.h"
#include "../token/token.h"

/**
 * @brief 打印请求的标记（token）列表。
 * @param tokenList 要打印的标记（token）列表。
 */
void printTokenList(const std::vector<Token::Token>& tokenList);

void printRequestedTokenList(const std::vector<Token::Token> &tokenList);

#endif //ROBIN_DEBUG_H
