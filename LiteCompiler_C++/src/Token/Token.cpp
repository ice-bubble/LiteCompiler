//
// Created by Ice-bubble on 24-4-21.
//

#include "Token.h"

Token::Token(TokenType type, const std::string &value, size_t line_n) : type(type), value(value), line_num(line_n) {}

TokenType Token::getType() const
{
    return type;
}

std::string Token::getValue() const
{
    return value;
}

size_t Token::getLineNum() const
{
    return line_num;
}
