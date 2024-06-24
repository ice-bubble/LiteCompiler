/**
 * @file reportParserError.h
 * @brief error函数的声明。
 * @date 24-4-22
 */

#ifndef ROBIN_ERROR_H
#define ROBIN_ERROR_H

#include "../common.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"

/**
 * @brief 使用给定的源代码行号和错误消息的描述打印错误消息。
 * @param line 发生错误的行号。
 * @param message 描述问题的错误消息。
 */
void error(size_t line, std::string_view message);

/**
 * @brief 报告词法分析时的词法错误。
 * @param error_lexer 指向发生错误的词法分析器对象的指针。
 * @param line 发生错误的行号。
 * @param message 描述问题的错误消息。
 */
void reportLexerError(lexer::Lexer *error_lexer, size_t line, StringView message);

/**
 * @param error_token 发生错误的token。
 * @param message 描述问题的错误消息。
 * @brief 进行报错
 */
void error(const token::Token &error_token, StringView message);

/**
 * @param error_parser 发生错误的语法分析器。
 * @param error_token 发生错误的token。
 * @param message 描述问题的错误消息。
 * @brief 报告语法分析时的语法错误。
 */
void reportParserError(parser::Parser *error_parser, const token::Token &error_token, StringView message);

/**
 * @param line 发生错误的行号。
 * @param message 描述问题的错误消息。
 * @brief 报告语义分析时的语义错误。
 */
void reportSemanticError(size_t line, StringView message);

#endif //ROBIN_ERROR_H
