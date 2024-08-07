#include "production.h"
#include "symbol.h"
#include "../token/token.h"
#include "../error/error.h"


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

    String Production::autoConversion(String originName, ast::IdentifierType originType,
                                      ast::IdentifierType expectType, size_t line, sema::Sema *semaAna) {
        auto realT = ast::Type::typeForceTransform[{originType, expectType}];
        if (realT != ast::IdentifierType::BASE_) {
            if (realT == originType) return originName;
            String tmpT = sema::Sema::genT();
            String code = fmt::format("{}=({}){}", tmpT, ast::Type::typeToString[realT], originName);
            semaAna->irCode.emplace_back(code);
            return tmpT;
        } else {
            String errorMsg = fmt::format("assignment from {} to {} is illegal",
                                          ast::Type::typeToString[originType], ast::Type::typeToString[expectType]);
            reportSemanticError(line, errorMsg);
        }
        return "";
    }

    Pair<String, ast::IdentifierType> Production::binaryOperation(String leftName, ast::IdentifierType leftType,
                                                                  String rightName, ast::IdentifierType rightType,
                                                                  String op, size_t line, sema::Sema *semaAna) {
        ast::IdentifierType leftT = ast::Type::typeTransform[{leftType, rightType}];
        ast::IdentifierType rightT = ast::Type::typeTransform[{rightType, leftType}];
        if (leftT != rightT || leftT == ast::IdentifierType::BASE_ || rightType == ast::IdentifierType::BASE_) {
            String errorMsg = fmt::format("operation between {} and {} is illegal",
                                          ast::Type::typeToString[leftType], ast::Type::typeToString[rightType]);
            reportSemanticError(line, errorMsg);
        } else {
            String tmpT1 = autoConversion(leftName, leftType, leftT, line, semaAna);
            String tmpT2 = autoConversion(rightName, rightType, rightT, line, semaAna);
            String tmpT3 = sema::Sema::genT();
            String code = fmt::format("{}={}{}{}", tmpT3, tmpT1, op, tmpT2);
            semaAna->irCode.emplace_back(code);
            return std::make_pair(tmpT3, leftT);
        }
        return std::make_pair("", ast::IdentifierType::BASE_);
    }


    void mergeUniqueIntoA(List<size_t> *a, List<size_t> *b) {
        // 使用unordered_set来存储唯一值
        Set<size_t> set(a->begin(), a->end());
        set.insert(b->begin(), b->end());

        // 将unordered_set转换回vector，并赋值给a
        a->assign(set.begin(), set.end());
    }
}
