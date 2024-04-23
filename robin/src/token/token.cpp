//
// Created by icelake on 24-4-22.
//
#include "token.h"


namespace Token {

    std::vector<std::string> tokenStrings = {
            "LEFT_PAREN",
            "RIGHT_PAREN",
            "LEFT_BRACE",
            "RIGHT_BRACE",
            "LEFT_BRACKET",
            "RIGHT_BRACKET",
            "COMMA",
            "DOT",
            "MINUS",
            "PLUS",
            "SEMICOLON",
            "SLASH",
            "STAR",
            "MOD",

            "NOT_EQUAL",
            "EQUAL",
            "EQUAL_EQUAL",
            "GREATER",
            "GREATER_EQUAL",
            "LESS",
            "LESS_EQUAL",

            "IDENTIFIER",
            "STRING",
            "INT",
            "REAL",

            "AND",
            "BREAK",
            "CLASS",
            "CONTINUE",
            "DOUBLE",
            "ELSE",
            "FALSE",
            "FOR",
            "FUNCTION",
            "IF",
            "INTEGER",
            "NIL",
            "NOT",
            "OR",
            "PRINT",
            "RETURN",
            "SUPER",
            "THIS",
            "TRUE",
            "VAR",
            "WHILE",

            "EOF"
    };


    Token::Token(TokenType type, std::string lexeme, std::any literal, size_t line)
            : type{type}, lexeme{std::move(lexeme)}, literal{std::move(literal)}, line{line} {}


    std::string Token::toString() const {
        return "line:" + std::to_string(line) + " < " + tokenStrings[type] + " " + lexeme + " " + getLiteralString() +
               " >";
    }

    std::string Token::getLiteralString() const {
        switch (type) {
            case (TOKEN_IDENTIFIER):
                return "nil";
            case (TOKEN_STRING):
                return std::any_cast<std::string>(literal);
            case (TOKEN_REAL):
                return std::to_string(std::any_cast<double>(literal));
            case (TOKEN_INT):
                return std::to_string(std::any_cast<long>(literal));
            case (TOKEN_TRUE):
                return "true";
            case (TOKEN_FALSE):
                return "false";
            default:
                return "nil";
        }
    }

}