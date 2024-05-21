//
// Created by icelake on 24-5-19.
//

#include "../token/token.h"
#include "production.h"
#include "symbol.h"

namespace production {
    Map<token::TokenType, symbol::Symbol> Production::tokenToSym = {
            {token::TOKEN_EOF,           symbol::Symbol::EOF_FLAG},
            {token::TOKEN_INT_,          symbol::Symbol::INT_},
            {token::TOKEN_REAL_,         symbol::Symbol::REAL_},
            {token::TOKEN_STRING_,       symbol::Symbol::STRING_},
            {token::TOKEN_IDENTIFIER,    symbol::Symbol::IDENTIFIER},
            {token::TOKEN_INTEGER,       symbol::Symbol::INTEGER},
            {token::TOKEN_DOUBLE,        symbol::Symbol::DOUBLE},
            {token::TOKEN_STRING,        symbol::Symbol::STRING},
            {token::TOKEN_BOOL,          symbol::Symbol::BOOL},
            {token::TOKEN_CHAR,          symbol::Symbol::CHAR},
            {token::TOKEN_VAR,           symbol::Symbol::VAR},
            {token::TOKEN_BREAK,         symbol::Symbol::BREAK},
            {token::TOKEN_CONTINUE,      symbol::Symbol::CONTINUE},
            {token::TOKEN_RETURN,        symbol::Symbol::RETURN},
            {token::TOKEN_NOT,           symbol::Symbol::NOT},
            {token::TOKEN_MINUS,         symbol::Symbol::MINUS},
            {token::TOKEN_TRUE,          symbol::Symbol::TRUE},
            {token::TOKEN_FALSE,         symbol::Symbol::FALSE},
            {token::TOKEN_NIL,           symbol::Symbol::NIL},
            {token::TOKEN_LEFT_PAREN,    symbol::Symbol::LEFT_PAREN},
            {token::TOKEN_IF,            symbol::Symbol::IF},
            {token::TOKEN_WHILE,         symbol::Symbol::WHILE},
            {token::TOKEN_REPEAT,        symbol::Symbol::REPEAT},
            {token::TOKEN_LEFT_BRACE,    symbol::Symbol::LEFT_BRACE},
            {token::TOKEN_COMMA,         symbol::Symbol::COMMA},
            {token::TOKEN_EQUAL,         symbol::Symbol::EQUAL},
            {token::TOKEN_SEMICOLON,     symbol::Symbol::SEMICOLON},
            {token::TOKEN_ELSE,          symbol::Symbol::ELSE},
            {token::TOKEN_OR,            symbol::Symbol::OR},
            {token::TOKEN_AND,           symbol::Symbol::AND},
            {token::TOKEN_NOT_EQUAL,     symbol::Symbol::NOT_EQUAL},
            {token::TOKEN_EQUAL_EQUAL,   symbol::Symbol::EQUAL_EQUAL},
            {token::TOKEN_GREATER,       symbol::Symbol::GREATER},
            {token::TOKEN_GREATER_EQUAL, symbol::Symbol::GREATER_EQUAL},
            {token::TOKEN_LESS,          symbol::Symbol::LESS},
            {token::TOKEN_LESS_EQUAL,    symbol::Symbol::LESS_EQUAL},
            {token::TOKEN_PLUS,          symbol::Symbol::PLUS},
            {token::TOKEN_SLASH,         symbol::Symbol::DIV},
            {token::TOKEN_STAR,          symbol::Symbol::STAR},
            {token::TOKEN_MOD,           symbol::Symbol::MOD},
            {token::TOKEN_DOUBLE_ADD,    symbol::Symbol::DOUBLE_ADD},
            {token::TOKEN_DOUBLE_MINUS,  symbol::Symbol::DOUBLE_MINUS},
            {token::TOKEN_LEFT_BRACKET,  symbol::Symbol::LEFT_BRACKET},
            {token::TOKEN_FUNCTION,      symbol::Symbol::FUNCTION},
            {token::TOKEN_UNTIL,         symbol::Symbol::UNTIL},
            {token::TOKEN_RIGHT_BRACE,   symbol::Symbol::RIGHT_BRACE},
            {token::TOKEN_RIGHT_PAREN,   symbol::Symbol::RIGHT_PAREN},
            {token::TOKEN_RIGHT_BRACKET, symbol::Symbol::RIGHT_BRACKET}
    };
}