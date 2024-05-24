/**
 * @file error.cpp
 * @brief error函数的实现。
 * @date 24-4-22
 */

#include "error.h"

void error(size_t line, StringView message) {
    std::cerr << "[line: " << line << "] Error:" << message << std::endl;
}

void reportLexerError(lexer::Lexer *error_lexer, size_t line, StringView message) {
    error_lexer->hasError = true;
    error(line, message);
}

void error(const token::Token &error_token, StringView message) {
    std::cerr << "[line: " << error_token.getLine() << " token: '" << error_token.getLexeme() << "'] Error:" << message
              << std::endl;
}

void reportParserError(parser::Parser *error_parser, const token::Token &error_token, StringView message) {
    error_parser->hasError = true;
    if (error_token.getType() == token::TOKEN_EOF) return error(error_token.getLine()-1, message);
    error(error_token, message);
}