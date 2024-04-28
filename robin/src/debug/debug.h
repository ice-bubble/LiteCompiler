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
 * @brief 打印详细的标记（token）列表。
 * @param tokenList 要打印的标记（token）列表。
 */
void printTokenList(const List<Token::Token>& tokenList);

/**
 * @brief 打印请求的标记（token）列表。
 * @param tokenList 要打印的标记（token）列表。
 */
void printRequestedTokenList(const List<Token::Token> &tokenList);

/**
 * @brief 打印给定token序列的符号表。
 * @param tokenList 待分析的符号表。
 */
void printSymbolTable(const List<Token::Token>& tokenList);

/**
 * @brief 如果符号表中不存在，则将令牌的词素插入符号表中。
 * @param t 要插入符号表的令牌的词素。
 * @param symbolTable 要插入令牌词素的符号表。
 */
void insertToSymbolTable(const Token::Token& t, List<String>& symbolTable);



#endif //ROBIN_DEBUG_H
