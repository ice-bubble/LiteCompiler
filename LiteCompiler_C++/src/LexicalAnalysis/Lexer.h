//
// Created by Ice-bubble on 24-4-21.
//

#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include "../Token/Token.h"
#include <string>
#include <unordered_set>

class Lexer
{
public:
    Lexer(const std::string &input);

    bool LexicalAnalyze(std::vector<Token> &tokens);

    // std::string errorMsg(const std::string &msg) const;

private:
    std::string input;
    size_t currentPos;
    int line_num;       // 行号
    // 无序集合存储关键字
    std::unordered_set<std::string> keywords = {
        "if",
        "else",
        "while",
        "for",
        "return",
        "integer",
        "double",
        "function",
        "read",
        "write",
        "repeat",
        "until",
        "do",
        "char"
    };

    char peek() const;

    char advance();

    bool isAtEnd() const;

    bool isAlpha(char c) const;

    bool isDigit(char c) const;

    void skipWhitespace();

    void skipComment();

    Token parseIdentifier();

    Token parseNumber();

    Token parseSymbol();

    // 判断标识符是否为关键字
    bool isKeyword(const std::string &identifier) const;
};

#endif // LEXER_H
