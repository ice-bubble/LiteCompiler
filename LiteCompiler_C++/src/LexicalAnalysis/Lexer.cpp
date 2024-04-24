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

/*构造函数中，当前所指向的元素位置currentPos初始化为0，行号line_num初始化为1，变量exist_error初始化为false*/
Lexer::Lexer(const std::string &input) : input(input), currentPos(0), line_num(1), exist_error(false){}

// 初始化静态成员变量 keywords
std::map<std::string, TokenType> Lexer::keywords = {
    {"and", TokenType::KEYWORD_AND},
    {"break", TokenType::KEYWORD_BREAK},
    {"char", TokenType::KEYWORD_CHAR},
    {"class", TokenType::KEYWORD_CLASS},
    {"continue", TokenType::KEYWORD_CONTINUE},
    {"do", TokenType::KEYWORD_DO},
    {"double", TokenType::KEYWORD_DOUBLE},
    {"else", TokenType::KEYWORD_ELSE},
    {"false", TokenType::KEYWORD_FALSE},
    {"for", TokenType::KEYWORD_FOR},
    {"function", TokenType::KEYWORD_FUNCTION},
    {"if", TokenType::KEYWORD_IF},
    {"integer", TokenType::KEYWORD_INTEGER},
    {"nil", TokenType::KEYWORD_NIL},
    {"null", TokenType::KEYWORD_NULL},
    {"not", TokenType::KEYWORD_NOT},
    {"or", TokenType::KEYWORD_OR},
    {"print", TokenType::KEYWORD_PRINT},
    {"read", TokenType::KEYWORD_READ},
    {"repeat", TokenType::KEYWORD_REPEAT},
    {"return", TokenType::KEYWORD_RETURN},
    {"super", TokenType::KEYWORD_SUPER},
    {"this", TokenType::KEYWORD_THIS},
    {"true", TokenType::KEYWORD_TRUE},
    {"until", TokenType::KEYWORD_UNTIL},
    {"var", TokenType::KEYWORD_VAR},
    {"while", TokenType::KEYWORD_WHILE},
    {"write", TokenType::KEYWORD_WRITE}
};

TokenType Lexer::checkKeyword(const std::string &keyword) const
{
    // 在 keywords 中查找关键字
    auto it = keywords.find(keyword);
    if (it != keywords.end())
    {
        // 如果找到了，则返回对应的 TokenType
        return it->second; // second对应map类型数据的第2个元素
    }
    // 否则，只是普通的id，返回 IDENTIFIER
    return TokenType::IDENTIFIER;
}

void Lexer::printKeyword()
{
    // 在 keywords 中查找关键字
    for(auto it:keywords){
        std::cout << "KEYWORD " << it.first << std::endl;
    }
    
}

char Lexer::peek() const
{
    if (isAtEnd()) return '\0'; // 如果isAtENd()为真，说明全部数据读取完毕，返回'\0'表示读取过程结束
    return input[currentPos]; // 返回当前所指向的元素（char类型）
}

char Lexer::advance()
{
    if (!isAtEnd()) currentPos++; // 如果isAtENd()为假，说明全部数据还未读取完毕，指针移向下一个元素
    return input[currentPos - 1]; // 返回指针+1前所指向的元素（char类型）
}

bool Lexer::isAtEnd() const
{
    return currentPos >= input.size();
}

bool Lexer::isAlpha(char c) const
{
    return std::isalpha(c) || c == '_';
}

bool Lexer::isDigit(char c) const
{
    return std::isdigit(c);
}

void Lexer::skipWhitespace()
{
    while (!isAtEnd() && (peek() == ' ' || peek() == '\t' || peek() == '\n'))
    {
        /* 跳过空格、换行、制表符，其中遇到换行时行数line_num++ */
        if (peek() == '\n')line_num++;
        advance();
    }
}


bool Lexer::skipComment()
{
    currentPos--; // 进入函数时，制作指向触发注释符号位置的下一位，因此先回退再处理
    // 略过注释
    if (peek() == '/')
    {
        advance(); // consume '/'
        if (peek() == '/')
        {
            // 单行注释
            while (!isAtEnd() && peek() != '\n') advance();
        }
        else if (peek() == '*')
        { // 多行注释
            advance(); // consume '*'

            while (true)
            {
                char ch = peek(); // consume '\n'
                if (ch == '\n')
                {
                    line_num++;
                }
                if (peek() == '*' && peek() == '/')
                {
                    advance(); // consume '*'
                    advance(); // consume '/'
                    break;
                }
                if (isAtEnd())
                {
                    error(line_num, "Unterminated comment.");
                    exist_error = true;
                    return false;
                }
                advance();
            }
        }
        else
        {
            // 不是注释，回退 '/'
            currentPos--;
        }
    }
    else if (peek() == '#') // '#'也认为是注释
    {
        while (!isAtEnd() && peek() != '\n') advance();
    }
    return true;
}

Token Lexer::parseIdentifier()
{
    // 解析标识符和关键字
    std::string identifier;
    char first_char = peek();
    while (!isAtEnd() && (isAlpha(peek()) || isDigit(peek())))
    {
        identifier += peek();
        advance();
    }
    return Token(this->checkKeyword(identifier), identifier);
}


Token Lexer::parseString(char start_ch)
{
    std::string matched_str;
    if(start_ch == '\'')
    {
        while(peek()!='\'')
            matched_str+=advance();
        advance(); // consume '
    }
    else if(start_ch == '"')
    {
        while(peek()!='"')
            matched_str+=advance();
        advance(); // consume "
    }
    return Token(TokenType::STRING, matched_str);
}

Token Lexer::parseNumber()
{
    // 解析数字
    std::string number;
    bool has_exist_point = false;
    bool has_exist_Alpha = false;
    if (peek() == '.') // 数字的第一个为"."，即".5"类型的实数
    {
        number += "0";
    }
    while (!isAtEnd() && (isDigit(peek()) || peek() == '.' || isAlpha(peek())))
    {
        if (peek() == '.')
        {
            if (!has_exist_point)
                has_exist_point = true;
            else
            {
                // Error
                number += advance();
                error(line_num, number);
                exist_error = true;
                return Token(TokenType::INVALID, number);
            }
        }
        if (isAlpha(peek()))
        {
            number += peek();
            advance();
            has_exist_Alpha = true;
        }
        else number += advance();
    }
    if (has_exist_Alpha)
    {
        error(line_num, number);
        exist_error = true;
        return Token(TokenType::INVALID, number);
    }
    if (has_exist_point) return Token(TokenType::FLOAT, number);
    else return Token(TokenType::INTEGER, number);
}

Token Lexer::parseSymbol()
{
    // 解析符号和运算符
    char symbol = advance();
    switch (symbol)
    {
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
        {
            return parseString(symbol);
            // return Token(TokenType::D_MARKS, "\"");
        }

        case '\'':
        {
            return parseString(symbol);
            // return Token(TokenType::S_MARKS, "'");
        }

        case '.':
        {
            if (isDigit(peek())) // 是数字".5"类型
            {
                currentPos--;
                return parseNumber(); // 继续判断是否为数字
            }
            return Token(TokenType::MEMBER, ".");
        }

        case '+':
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::PLUS_ASSIGNMENT, "+=");
            }
            return Token(TokenType::PLUS, "+");
        case '-':
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::MINUS_ASSIGNMENT, "-=");
            }
            return Token(TokenType::MINUS, "-");
        case '*':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::MULTIPLY_ASSIGNMENT, "*=");
            }
            return Token(TokenType::MULTIPLY, "*");
        }
        case '/':
        {
            switch (peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::DIVIDE_ASSIGNMENT, "/=");
                }
                case '/':
                {
                    if (!skipComment())
                        return Token(TokenType::INVALID, "Unterminated comment.");
                    return Token(TokenType::EMPTY, "");
                }
                default:
                {
                    return Token(TokenType::DIVIDE, "/");
                };
            }
        }
        case '=':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::EQUAL, "==");
            }
            return Token(TokenType::ASSIGNMENT, "=");
        }
        case '!':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::NOT_EQUAL, "!=");
            }
            return Token(TokenType::LOGICAL_NOT, "!");
        }
        case '&':
        {
            switch (peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::AND_ASSIGNMENT, "&=");
                }
                case '&':
                {
                    advance();
                    return Token(TokenType::LOGICAL_AND, "&&");
                }
                default:
                {
                    return Token(TokenType::AND, "&");
                };
            }
        }
        case '|':
        {
            switch (peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::OR_ASSIGNMENT, "|=");
                }
                case '|':
                {
                    advance();
                    return Token(TokenType::LOGICAL_OR, "||");
                }
                default:
                {
                    return Token(TokenType::OR, "|");
                };
            }
        }
        case '^':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::XOR_ASSIGNMENT, "^=");
            }
            return Token(TokenType::XOR, "^");
        }
        case '~':
            return Token(TokenType::NOT, "~");
        case '#':
        {
            if (!skipComment())
                return Token(TokenType::INVALID, "Unterminated comment.");
            return Token(TokenType::EMPTY, "");
        }
        case ',':
            return Token(TokenType::COMMA, ",");
        case '>':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::ABOVE_OR_EUQAL, ">=");
            }
            return Token(TokenType::ABOVE, ">");
        }
        case '<':
        {
            if (peek() == '<')
            {
                advance();
                return Token(TokenType::BELOW_OR_EUQAL, "<=");
            }
            return Token(TokenType::BELOW, "<");
        }
        case '%':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::MOD_ASSIGNMENT, "%=");
            }
            return Token(TokenType::MOD, "%");
        }
        default:
        {
            std::string invalid_string;
            invalid_string += symbol;
            error(line_num, "Unexpected character '" + invalid_string + "'.");
            exist_error = true;
            return Token(TokenType::INVALID, invalid_string);
        }
    }
}

bool Lexer::LexicalAnalyze(std::vector<Token> &tokens)
{
    while (!isAtEnd())
    {
        skipWhitespace(); // 跳过' '、'\n'、'\t'
        if (isAtEnd())
        {
            if (exist_error)return false; // 存在词法错误情况下【判断方式暂未添加】
            return true;
        }
        if (isAlpha(peek())) // id
        {
            tokens.push_back(parseIdentifier());
        }
        else if (isDigit(peek()))
        {
            tokens.push_back(parseNumber());
        }
        else
        {
            tokens.push_back(parseSymbol());
        }
    }
    if (exist_error)return false; // 存在词法错误情况下【判断方式暂未添加】
    return true;
}
