/**
 * @file error.cpp
 * @brief error函数的实现。
 * @date 24-4-22
 */

#include "error.h"

void error(size_t line, const String &message) {
    std::cerr << "[line: " << line << "] Error:" << message << std::endl;
}

void error(lexer::Lexer *error_lexer, size_t line, const String &message) {
    error_lexer->hasError = true;
    error(line, message);
}

void error(const token::Token& error_token, const String &message) {
    std::cerr << "[token: " << error_token.toString() << "] Error:" << message << std::endl;
}