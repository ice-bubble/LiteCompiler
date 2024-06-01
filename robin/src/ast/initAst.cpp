//
// Created by icelake on 24-5-19.
//

#include "../token/token.h"
#include "production.h"
#include "symbol.h"

namespace production {
    Map<token::TokenType, symbol::Symbol> Production::tokenToSym = {
            {token::TOKEN_EOF,           symbol::Symbol::DOLLAR},
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
            {token::TOKEN_RIGHT_BRACKET, symbol::Symbol::RIGHT_BRACKET},
            {token::TOKEN_FOR,           symbol::Symbol::FOR}
    };
}

namespace ast {
    Map<Pair<IdentifierType, IdentifierType>, IdentifierType> Type::typeTransform = {
            {{BASE_,   BASE_},   BASE_},
            {{BASE_,   VAR_},    BASE_},
            {{BASE_,   ARRAY_},  BASE_},
            {{BASE_,   FUNC_},   BASE_},
            {{BASE_,   STRING_}, BASE_},
            {{BASE_,   NIL_},    BASE_},
            {{BASE_,   BOOL_},   BASE_},
            {{BASE_,   CHAR_},   BASE_},
            {{BASE_,   INT_},    BASE_},
            {{BASE_,   REAL_},   BASE_},

            {{VAR_,    BASE_},   BASE_},
            {{VAR_,    VAR_},    VAR_},
            {{VAR_,    ARRAY_},  ARRAY_},
            {{VAR_,    FUNC_},   FUNC_},
            {{VAR_,    STRING_}, BASE_},
            {{VAR_,    NIL_},    BASE_},
            {{VAR_,    BOOL_},   BOOL_},
            {{VAR_,    CHAR_},   CHAR_},
            {{VAR_,    INT_},    INT_},
            {{VAR_,    REAL_},   REAL_},

            {{ARRAY_,  BASE_},   BASE_},
            {{ARRAY_,  VAR_},    ARRAY_},
            {{ARRAY_,  ARRAY_},  ARRAY_},
            {{ARRAY_,  FUNC_},   BASE_},
            {{ARRAY_,  STRING_}, BASE_},
            {{ARRAY_,  NIL_},    BASE_},
            {{ARRAY_,  BOOL_},   BASE_},
            {{ARRAY_,  CHAR_},   BASE_},
            {{ARRAY_,  INT_},    BASE_},
            {{ARRAY_,  REAL_},   BASE_},

            {{FUNC_,   BASE_},   BASE_},
            {{FUNC_,   VAR_},    FUNC_},
            {{FUNC_,   ARRAY_},  BASE_},
            {{FUNC_,   FUNC_},   FUNC_},
            {{FUNC_,   STRING_}, BASE_},
            {{FUNC_,   NIL_},    BASE_},
            {{FUNC_,   BOOL_},   BASE_},
            {{FUNC_,   CHAR_},   BASE_},
            {{FUNC_,   INT_},    BASE_},
            {{FUNC_,   REAL_},   BASE_},

            {{STRING_, BASE_},   BASE_},
            {{STRING_, VAR_},    STRING_},
            {{STRING_, ARRAY_},  BASE_},
            {{STRING_, FUNC_},   BASE_},
            {{STRING_, STRING_}, STRING_},
            {{STRING_, NIL_},    BASE_},
            {{STRING_, BOOL_},   BASE_},
            {{STRING_, CHAR_},   BASE_},
            {{STRING_, INT_},    BASE_},
            {{STRING_, REAL_},   BASE_},

            {{NIL_,    BASE_},   BASE_},
            {{NIL_,    VAR_},    NIL_},
            {{NIL_,    ARRAY_},  BASE_},
            {{NIL_,    FUNC_},   BASE_},
            {{BASE_,   STRING_}, BASE_},
            {{NIL_,    NIL_},    BASE_},
            {{NIL_,    BOOL_},   BOOL_},
            {{NIL_,    CHAR_},   CHAR_},
            {{NIL_,    INT_},    INT_},
            {{NIL_,    REAL_},   REAL_},

            {{BOOL_,   BASE_},   BASE_},
            {{BOOL_,   VAR_},    BOOL_},
            {{BOOL_,   ARRAY_},  BASE_},
            {{BOOL_,   FUNC_},   BASE_},
            {{BOOL_,   STRING_}, BASE_},
            {{BOOL_,   NIL_},    BASE_},
            {{BOOL_,   BOOL_},   BOOL_},
            {{BOOL_,   CHAR_},   CHAR_},
            {{BOOL_,   INT_},    INT_},
            {{BOOL_,   REAL_},   REAL_},

            {{CHAR_,   BASE_},   BASE_},
            {{CHAR_,   VAR_},    CHAR_},
            {{CHAR_,   ARRAY_},  BASE_},
            {{CHAR_,   FUNC_},   BASE_},
            {{CHAR_,   STRING_}, BASE_},
            {{CHAR_,   NIL_},    BASE_},
            {{CHAR_,   BOOL_},   CHAR_},
            {{CHAR_,   CHAR_},   CHAR_},
            {{CHAR_,   INT_},    INT_},
            {{CHAR_,   REAL_},   REAL_},

            {{INT_,    BASE_},   BASE_},
            {{INT_,    VAR_},    INT_},
            {{INT_,    ARRAY_},  BASE_},
            {{INT_,    FUNC_},   BASE_},
            {{INT_,    STRING_}, BASE_},
            {{INT_,    NIL_},    BASE_},
            {{INT_,    BOOL_},   INT_},
            {{INT_,    CHAR_},   INT_},
            {{INT_,    INT_},    INT_},
            {{INT_,    REAL_},   REAL_},

            {{REAL_,   BASE_},   BASE_},
            {{REAL_,   VAR_},    REAL_},
            {{REAL_,   ARRAY_},  BASE_},
            {{REAL_,   FUNC_},   BASE_},
            {{REAL_,   STRING_}, BASE_},
            {{REAL_,   NIL_},    BASE_},
            {{REAL_,   BOOL_},   REAL_},
            {{REAL_,   CHAR_},   REAL_},
            {{REAL_,   INT_},    REAL_},
            {{REAL_,   REAL_},   REAL_},
    };
    Map<IdentifierType, String> Type::typeToString = {
            {BASE_,   "base"},
            {VAR_,    "var"},
            {ARRAY_,  "array"},
            {FUNC_,   "func"},
            {STRING_, "string"},
            {NIL_,    "nil"},
            {BOOL_,   "bool"},
            {CHAR_,   "char"},
            {INT_,    "int"},
            {REAL_,   "double"},
    };

    SharedPtr<Type> Type::makeTypeInstance(IdentifierType requestedType) {
        switch (requestedType) {
            case BASE_:
                return std::make_shared<BASE_Type>();
            case VAR_:
                return std::make_shared<VAR_Type>();
            case ARRAY_:
                return std::make_shared<ARRAY_Type>();
            case FUNC_:
                return std::make_shared<FUNC_Type>();
            case STRING_:
                return std::make_shared<STRING_Type>();
            case NIL_:
                return std::make_shared<NIL_Type>();
            case BOOL_:
                return std::make_shared<BOOL_Type>();
            case CHAR_:
                return std::make_shared<CHAR_Type>();
            case INT_:
                return std::make_shared<INT_Type>();
            case REAL_:
                return std::make_shared<REAL_Type>();
        }
        return std::make_shared<NIL_Type>();
    }
}