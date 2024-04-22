//
// Created by Ice-bubble on 24-4-21.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
    // 定义标记类型
    KEYWORD,    // 关键字
    IDENTIFIER, // id
    INTEGER, // int
    FLOAT, // double、float
    SEMICOLON, // ";"
    ASSIGNMENT, // "="赋值运算符
    PLUS, // "+"
    PLUS_FORWARD, // "+="
    MINUS, // "-"
    MINUS_FORWARD, // "-="
    MULTIPLY, // "*"
    MULTIPLY_FORWARD, // "*="
    DIVIDE, // "/"
    DIVIDE_FORWARD, // "/="
    AND, // "&"
    AND_FORWARD, // "&="
    LOGICAL_AND, // "&&"
    OR, // "|"
    OR_FORWARD, // "|="
    LOGICAL_OR, // "||"
    XOR, // "^"
    XOR_FORWARD, // "^="
    NOT, // "~"
    EQUAL, // "=="
    ABOVE, // ">"
    BELOW, // "<"
    ABOVE_OR_EUQAL, // ">="
    BELOW_OR_EUQAL, // "<="
    LEFT_PAREN, // "("
    RIGHT_PAREN, // ")"
    LEFT_BRACKET, // "["
    RIGHT_BRACKET, // "]"
    LEFT_BRACE, // "{"
    RIGHT_BRACE, // "}"
    D_MARKS, // "
    S_MARKS, // '
    MEMBER, // "."
    COMMA, // ","
    EMPTY, // 空
    INVALID // 非法的标记
};

class Token
{
public:
    Token(TokenType type, const std::string &value);

    TokenType getType() const;

    std::string getValue() const;

private:
    TokenType type;
    std::string value;
};

#endif // TOKEN_H
