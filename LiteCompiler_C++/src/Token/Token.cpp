//
// Created by Ice-bubble on 24-4-21.
//

#include "Token.h"

Token::Token(TokenType type, const std::string &value) : type(type), value(value) {}

TokenType Token::getType() const
{
    return type;
}

std::string Token::getValue() const
{
    return value;
}
