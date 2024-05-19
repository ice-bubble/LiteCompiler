//
// Created by icelake on 24-5-19.
//

#include "../token/token.h"
#include "production.h"
#include "symbol.h"

namespace production{
    Map<token::TokenType, symbol::Symbol> Production::tokenToSym = {
            {token::TOKEN_MINUS,       symbol::Symbol::minus},
            {token::TOKEN_PLUS,        symbol::Symbol::plus},
            {token::TOKEN_SLASH,       symbol::Symbol::div},
            {token::TOKEN_STAR,        symbol::Symbol::star},
            {token::TOKEN_MOD,         symbol::Symbol::mod},
            {token::TOKEN_LEFT_PAREN,  symbol::Symbol::left_paren},
            {token::TOKEN_RIGHT_PAREN, symbol::Symbol::right_paren},
            {token::TOKEN_REAL_,       symbol::Symbol::real_},
            {token::TOKEN_INT_,        symbol::Symbol::int_}
    };
}