//
// Created by Ice-bubble on 24-4-21.
//

#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include "../Token/Token.h"
#include <string>
#include <unordered_set>
#include <map>

class Lexer
{
public:
    Lexer(const std::string &input);

    bool LexicalAnalyze(std::vector<Token> &tokens);

    // std::string errorMsg(const std::string &msg) const;

private:
    std::string input;
    size_t currentPos;
    size_t line_num;       // 行号
    std::string *str_temp; // 比较字符串是的临时变量
    std::map<std::string, TokenType> keywords; // 添加关键字映射表

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
    TokenType checkKeyword(const std::string& keyword);
};

#endif // LEXER_H
