//
// Created by Ice-bubble on 24-4-21.
//
#include "../error/error.h"
#include "Lexer.h"
#include <stdexcept>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <map>

Lexer::Lexer(const std::string &input) : input(input), currentPos(0), line_num(1) {
    keywords = {
            {"and",      TokenType::KEYWORD_AND},
            {"break",    TokenType::KEYWORD_BREAK},
            {"class",    TokenType::KEYWORD_CLASS},
            {"continue", TokenType::KEYWORD_CONTINUE},
            {"double",   TokenType::KEYWORD_DOUBLE},
            {"else",     TokenType::KEYWORD_ELSE},
            {"false",    TokenType::KEYWORD_FALSE},
            {"for",      TokenType::KEYWORD_FOR},
            {"function", TokenType::KEYWORD_FUNCTION},
            {"if",       TokenType::KEYWORD_IF},
            {"integer",  TokenType::KEYWORD_INTEGER},
            {"nil",      TokenType::KEYWORD_NIL},
            {"not",      TokenType::KEYWORD_NOT},
            {"or",       TokenType::KEYWORD_OR},
            {"print",    TokenType::KEYWORD_PRINT},
            {"return",   TokenType::KEYWORD_RETURN},
            {"super",    TokenType::KEYWORD_SUPER},
            {"this",     TokenType::KEYWORD_THIS},
            {"true",     TokenType::KEYWORD_TRUE},
            {"var",      TokenType::KEYWORD_VAR},
            {"while",    TokenType::KEYWORD_WHILE}
    };

    /*
std::unordered_set<std::string> keywords = {
    "if",
    "else",
    "while",
    "for",
    "return",
    "integer",
    "double",
    "function",
    "read",
    "write",
    "repeat",
    "until",
    "do",
    "char"
};
*/
}

TokenType Lexer::checkKeyword(const std::string &keyword) {
    // 在 keywords 中查找关键字
    auto it = keywords.find(keyword);
    if (it != keywords.end()) {
        // 如果找到了，则返回对应的 TokenType
        return it->second;
    } else {
        // 否则返回 IDENTIFIER
        return TokenType::IDENTIFIER;
    }
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return input[currentPos];
}

char Lexer::advance() {
    if (!isAtEnd()) currentPos++;
    return input[currentPos - 1];
}

bool Lexer::isAtEnd() const {
    return currentPos >= input.size();
}

bool Lexer::isAlpha(char c) const {
    return std::isalpha(c) || c == '_';
}

bool Lexer::isDigit(char c) const {
    return std::isdigit(c);
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() && (peek() == ' ' || peek() == '\t' || peek() == '\n')) {
        if (peek() == '\n')line_num++;
        advance();
    }
}


void Lexer::skipComment() {
    currentPos--;   // 进入函数时，制作指向触发注释符号位置的下一位，因此先回退再处理
    // 略过注释
    if (peek() == '/') {
        advance(); // consume '/'
        if (peek() == '/') {
            // 单行注释
            while (!isAtEnd() && peek() != '\n') advance();
        } else if (peek() == '*') {// 多行注释
            advance();// consume '*'

            while (true) {
                char ch = peek(); // consume '\n'
                if (ch == '\n') {
                    line_num++;
                }
                if (peek() == '*' && peek() == '/') {
                    advance(); // consume '*'
                    advance(); // consume '/'
                    break;
                }
                if (isAtEnd()) {
                    error(line_num, "Unterminated comment.");
                    return;
                }
                advance();
            }
        } else {
            // 不是注释，回退 '/'
            currentPos--;
        }
    } else if (peek() == '#') // '#'也认为是注释
    {
        while (!isAtEnd() && peek() != '\n') advance();
    }
}

Token Lexer::parseIdentifier() {
    // 解析标识符和关键字
    std::string identifier;
    char first_char = peek();
    while (!isAtEnd() && (isAlpha(peek()) || isDigit(peek()))) {
        identifier += peek();
        advance();
    }
    return Token(this->checkKeyword(identifier), identifier);
}


Token Lexer::parseString() {

}

Token Lexer::parseNumber() {
    // 解析数字
    std::string number;
    bool has_exist_point = false;
    if (peek() == '.') // 数字的第一个为"."，即".5"类型的实数
    {
        number += "0";
    }
    while (!isAtEnd() && (isDigit(peek()) || peek() == '.')) {
        if (peek() == '.') {
            if (!has_exist_point)
                has_exist_point = true;
            else {
                // Error
                advance();
                return Token(TokenType::INVALID, ".");
            }
        }
        number += peek();
        advance();
    }
    if (has_exist_point) return Token(TokenType::FLOAT, number);
    else return Token(TokenType::INTEGER, number);
}

Token Lexer::parseSymbol() {
    // 解析符号和运算符
    char symbol = advance();
    switch (symbol) {
        case ';':
            return Token(TokenType::SEMICOLON, ";");
        case '(':
            return Token(TokenType::LEFT_PAREN, "(");
        case ')':
            return Token(TokenType::RIGHT_PAREN, ")");
        case '[':
            return Token(TokenType::LEFT_BRACKET, "[");
        case ']':
            return Token(TokenType::RIGHT_BRACKET, "]");
        case '{':
            return Token(TokenType::LEFT_BRACE, "{");
        case '}':
            return Token(TokenType::RIGHT_BRACE, "}");
        case '"':
            return parseString();
        case '\'':
            return Token(TokenType::S_MARKS, "'");
        case '.': {
            if (isDigit(peek()))    // 是数字".5"类型
            {
                currentPos--;
                return parseNumber();     // 继续判断是否为数字
            }
            return Token(TokenType::MEMBER, ".");
        }

        case '+':
            if (peek() == '=') {
                advance();
                return Token(TokenType::PLUS_FORWARD, "+=");
            }
            return Token(TokenType::PLUS, "+");
        case '-':
            if (peek() == '=') {
                advance();
                return Token(TokenType::MINUS_FORWARD, "-=");
            }
            return Token(TokenType::MINUS, "-");
        case '*': {
            if (peek() == '=') {
                advance();
                return Token(TokenType::MULTIPLY_FORWARD, "*=");
            }
            return Token(TokenType::MULTIPLY, "*");
        }
        case '/': {
            switch (peek()) {
                case '=': {
                    advance();
                    return Token(TokenType::DIVIDE_FORWARD, "/=");
                }
                case '/': {
                    skipComment();
                    return Token(TokenType::EMPTY, "");
                }
                default: {
                    return Token(TokenType::DIVIDE, "/");
                };
            }
        }
        case '=': {
            if (peek() == '=') {
                advance();
                return Token(TokenType::EQUAL, "==");
            }
            return Token(TokenType::ASSIGNMENT, "=");

        }
        case '!': {
            if (peek() == '=') {
                advance();
                return Token(TokenType::NOT_EQUAL, "!=");
            }
            return Token(TokenType::LOGICAL_NOT, "!");
        }
        case '&': {
            switch (peek()) {
                case '=': {
                    advance();
                    return Token(TokenType::AND_FORWARD, "&=");
                }
                case '&': {
                    advance();
                    return Token(TokenType::LOGICAL_AND, "&&");
                }
                default: {
                    return Token(TokenType::AND, "&");
                };
            }
        }
        case '|': {
            switch (peek()) {
                case '=': {
                    advance();
                    return Token(TokenType::OR_FORWARD, "|=");
                }
                case '|': {
                    advance();
                    return Token(TokenType::LOGICAL_OR, "||");
                }
                default: {
                    return Token(TokenType::OR, "|");
                };
            }
        }
        case '^': {
            if (peek() == '=') {
                advance();
                return Token(TokenType::XOR_FORWARD, "^=");
            }
            return Token(TokenType::XOR, "^");
        }
        case '~':
            return Token(TokenType::NOT, "~");
        case '#': {
            skipComment();
            return Token(TokenType::EMPTY, "");
        }
        case ',':
            return Token(TokenType::COMMA, ",");
        case '>': {
            if (peek() == '=') {
                advance();
                return Token(TokenType::ABOVE_OR_EUQAL, ">=");
            }
            return Token(TokenType::ABOVE, ">");
        }
        case '<': {
            if (peek() == '<') {
                advance();
                return Token(TokenType::BELOW_OR_EUQAL, "<=");
            }
            return Token(TokenType::BELOW, "<");
        }
        default: {
            std::string invalid_string;
            invalid_string += symbol;
            error(line_num, "Unexpected character '" + invalid_string + "'.");
            return Token(TokenType::INVALID, invalid_string);
        }
    }
}

bool Lexer::LexicalAnalyze(std::vector<Token> &tokens) {
    while (!isAtEnd()) {
        skipWhitespace();   // 跳过' '、'\n'、'\t'
        if (isAtEnd()) return true;
        if (isAlpha(peek()))    // id
        {
            tokens.push_back(parseIdentifier());
        } else if (isDigit(peek())) {
            tokens.push_back(parseNumber());
        } else {
            tokens.push_back(parseSymbol());
        }
    }
    return true;
}