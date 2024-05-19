/**
 * @file error.h
 * @brief error函数的声明。
 * @date 24-4-22
 */

#ifndef ROBIN_ERROR_H
#define ROBIN_ERROR_H

#include "../common.h"
#include "../lexer/lexer.h"

/**
 * @brief 使用给定的源代码行号和错误消息的描述打印错误消息
 * @param line 源代码行号
 * @param message 错误消息的描述
 */
void error(size_t line, const String& message);

/**
 * @brief 处理词法分析器的错误，通过设置错误标志来指示发生错误。
 * @param error_lexer 指向发生错误的词法分析器对象的指针。
 * @param line 发生错误的行号。
 * @param message 描述问题的错误消息。
 */
void error(lexer::Lexer* error_lexer ,size_t line, const String& message);

void error(const token::Token& error_token , const String& message);

#endif //ROBIN_ERROR_H
