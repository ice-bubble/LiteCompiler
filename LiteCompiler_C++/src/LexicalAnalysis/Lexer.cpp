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
Lexer::Lexer(const std::string &input) : input(input), currentPos(0), line_num(1), exist_error(false) {}

// 初始化静态成员变量 keywords
std::map<std::string, TokenType> Lexer::keywords = {
    //{"and", TokenType::KEYWORD_AND},
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
    //{"or", TokenType::KEYWORD_OR},
    {"print", TokenType::KEYWORD_PRINT},
    {"read", TokenType::KEYWORD_READ},
    {"repeat", TokenType::KEYWORD_REPEAT},
    {"return", TokenType::KEYWORD_RETURN},
    {"string", TokenType::KEYWORD_STRING},
    //{"super", TokenType::KEYWORD_SUPER},
    //{"this", TokenType::KEYWORD_THIS},
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
    for (auto it: keywords)
        std::cout << "KEYWORD " << it.first << std::endl;
}

std::string Lexer::getAllKeyword()
{
    std::string AllKeyword_String;
    // 在 keywords 中查找关键字，并拼接进字符串
    for (auto it: keywords)
        AllKeyword_String += "KEYWORD " + it.first + '\n';
    return AllKeyword_String;
}

char Lexer::peek() const
{
    if (isAtEnd()) return '\0'; // 如果isAtENd()为真，说明全部数据读取完毕，返回'\0'表示读取过程结束
    return input[currentPos]; // 返回当前所指向的元素（char类型）
}

char Lexer::peekNext() const
{
    if (currentPos + 1 >= input.size()) return '\0'; // 判断是否到达输入末尾
    return input[currentPos + 1]; // 返回下一个字符
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
    currentPos--; // 进入函数时，当前指针指向触发注释符号位置的下一位，因此先回退再处理
    size_t start_line = line_num; // 存储注释开头所在行号，用于多行注释报错未闭合时能输出注释开头所在行号
    if (peek() == '/' && peekNext() == '/') ///< // 单行注释
    {
        advance();
        advance(); // consume '//'
        while (!isAtEnd() && peek() != '\n') advance();
        return true;
    }
    if (peek() == '#') ///< # 单行注释
    {
        advance(); // consume '#'
        while (!isAtEnd() && peek() != '\n') advance();
        return true;
    }
    ///< /**/ 多行注释
    advance();
    advance(); // consume '/*'
    while (true)
    {
        char ch = peek(); // consume '\n'
        if (ch == '\n')
        {
            line_num++;
        }
        if (peek() == '*' && peekNext() == '/')
        {
            advance();
            advance(); // consume '/*'
            return true;
        }
        if (isAtEnd())
        {
            error(start_line, "Unterminated comment.");
            exist_error = true;
            return false;
        }
        advance();
    }
}

Token Lexer::parseIdentifier()
{
    // 解析标识符和关键字
    std::string identifier;
    while (!isAtEnd() && (isAlpha(peek()) || isDigit(peek())))
    {
        identifier += peek();
        advance();
    }
    return Token(this->checkKeyword(identifier), identifier, line_num);
}


Token Lexer::parseString(char start_ch)
{
    std::string matched_str;
    if (start_ch == '\'')
    {
        while (peek() != '\'')
        {
            matched_str += advance();
            if (isAtEnd() || peek() == '\n') // 未找到闭合，Error
            {
                error(line_num, "missing terminating ' character ");
                exist_error = true;
                return Token(TokenType::INVALID, "'" + matched_str, line_num);
            }
        }

        advance(); // consume '
    }
    else if (start_ch == '"')
    {
        while (peek() != '"')
        {
            matched_str += advance();
            if (isAtEnd() || peek() == '\n') // 未找到闭合，Error
            {
                error(line_num, "missing terminating \" character.");
                exist_error = true;
                return Token(TokenType::INVALID, "\"" + matched_str, line_num);
            }
        }
        advance(); // consume "
    }
    return Token(TokenType::STRING, matched_str, line_num);
}

Token Lexer::parseNumber()
{
    // 解析数字
    std::string number;
    bool has_exist_point = false;
    if (peek() == '.') // 数字的第一个为"."，即".5"类型的实数
    {
        number += "0";
    }
    while (!isAtEnd() && (isDigit(peek()) || peek() == '.'))
    {
        if (peek() == '.')
        {
            if (!has_exist_point)
                has_exist_point = true;
            else
            {
                break; // 多个小数点情况，不是词法错误，直接结束本次数字的读取。进入下一个Token的识别
                /* 非词法报错，因此词法分析阶段不进行报错
                // Error
                number += advance();
                error(line_num, "Too many decimal points in number.");
                exist_error = true;
                return Token(TokenType::INVALID, number, line_num);
                */
            }
        }
        number += advance();
    }
    if (input[currentPos-1] == '.') // 如果数字结尾为"."，说明是形如"1."的浮点数，末尾加上0之后再输出
    {
        number += "0";
    }
    if (has_exist_point) return Token(TokenType::FLOAT, number, line_num);
    else return Token(TokenType::INTEGER, number, line_num);
}

Token Lexer::parseSymbol()
{
    // 解析符号和运算符
    char symbol = advance();
    switch (symbol)
    {
        case ';':
            return Token(TokenType::SEMICOLON, ";", line_num);
        case '(':
            return Token(TokenType::LEFT_PAREN, "(", line_num);
        case ')':
            return Token(TokenType::RIGHT_PAREN, ")", line_num);
        case '[':
            return Token(TokenType::LEFT_BRACKET, "[", line_num);
        case ']':
            return Token(TokenType::RIGHT_BRACKET, "]", line_num);
        case '{':
            return Token(TokenType::LEFT_BRACE, "{", line_num);
        case '}':
            return Token(TokenType::RIGHT_BRACE, "}", line_num);
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
            return Token(TokenType::MEMBER, ".", line_num);
        }

        case '+':
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::PLUS_ASSIGNMENT, "+=", line_num);
            }
            if (peek() == '+')
            {
                advance();
                return Token(TokenType::PLUS_SELF, "++", line_num);
            }
            return Token(TokenType::PLUS, "+", line_num);
        case '-':
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::MINUS_ASSIGNMENT, "-=", line_num);
            }
            if (peek() == '-')
            {
                advance();
                return Token(TokenType::MINUS_SELF, "--", line_num);
            }
            return Token(TokenType::MINUS, "-", line_num);
        case '*':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::MULTIPLY_ASSIGNMENT, "*=", line_num);
            }
            return Token(TokenType::MULTIPLY, "*", line_num);
        }
        case '/':
        {
            switch (peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::DIVIDE_ASSIGNMENT, "/=", line_num);
                }
                case '/':
                {
                    if (!skipComment())
                        return Token(TokenType::INVALID, "Unterminated comment.", line_num);
                    return Token(TokenType::EMPTY, "", line_num);
                }
                case '*':
                {
                    if (!skipComment())
                        return Token(TokenType::INVALID, "Unterminated comment.", line_num);
                    return Token(TokenType::EMPTY, "", line_num);
                }
                default:
                {
                    return Token(TokenType::DIVIDE, "/", line_num);
                };
            }
        }
        case '=':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::EQUAL, "==", line_num);
            }
            return Token(TokenType::ASSIGNMENT, "=", line_num);
        }
        case '!':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::NOT_EQUAL, "!=", line_num);
            }
            return Token(TokenType::LOGICAL_NOT, "!", line_num);
        }
        case '&':
        {
            switch (peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::AND_ASSIGNMENT, "&=", line_num);
                }
                case '&':
                {
                    advance();
                    return Token(TokenType::LOGICAL_AND, "&&", line_num);
                }
                default:
                {
                    return Token(TokenType::AND, "&", line_num);
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
                    return Token(TokenType::OR_ASSIGNMENT, "|=", line_num);
                }
                case '|':
                {
                    advance();
                    return Token(TokenType::LOGICAL_OR, "||", line_num);
                }
                default:
                {
                    return Token(TokenType::OR, "|", line_num);
                };
            }
        }
        case '^':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::XOR_ASSIGNMENT, "^=", line_num);
            }
            return Token(TokenType::XOR, "^", line_num);
        }
        case '~':
            return Token(TokenType::NOT, "~", line_num);
        case '#':
        {
            if (!skipComment())
                return Token(TokenType::INVALID, "Unterminated comment.", line_num);
            return Token(TokenType::EMPTY, "", line_num);
        }
        case ',':
            return Token(TokenType::COMMA, ",", line_num);
        case '>':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::ABOVE_OR_EUQAL, ">=", line_num);
            }
            return Token(TokenType::ABOVE, ">", line_num);
        }
        case '<':
        {
            if (peek() == '<')
            {
                advance();
                return Token(TokenType::BELOW_OR_EUQAL, "<=", line_num);
            }
            return Token(TokenType::BELOW, "<", line_num);
        }
        case '%':
        {
            if (peek() == '=')
            {
                advance();
                return Token(TokenType::MOD_ASSIGNMENT, "%=", line_num);
            }
            return Token(TokenType::MOD, "%", line_num);
        }
        default:
        {
            std::string invalid_string;
            invalid_string += symbol;
            error(line_num, "Unexpected character '" + invalid_string + "'.");
            exist_error = true;
            return Token(TokenType::INVALID, invalid_string, line_num);
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
            if (exist_error)return false; // 存在词法错误情况下
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
    if (exist_error)return false; // 存在词法错误情况下
    return true;
}
