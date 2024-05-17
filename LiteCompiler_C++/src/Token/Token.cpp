//
// Created by Ice-bubble on 24-4-21.
//

#include "Token.h"

Token::Token(TokenType type, const std::string &value, size_t line_n) : type(type), value(value), line_num(line_n) {}

Token::Token(NonTerminal nonTerminal, const std::string &value, size_t line_n): value(value), line_num((line_n))
{
    // 初始化 Token 对象，使其表示一个非终结符
    this->type = TokenType::NONTERMINAL;
    this->nonTerminal = nonTerminal;
}

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
