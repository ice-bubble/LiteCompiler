//
// Created by Ice-bubble on 24-4-21.
//

#include "Lexer.h"
#include <stdexcept>
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string &input) : input(input), currentPos(0), line_num(1) {}

char Lexer::peek() const
{
    if (isAtEnd()) return '\0';
    return input[currentPos];
}

char Lexer::advance()
{
    if (!isAtEnd()) currentPos++;
    return input[currentPos - 1];
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

bool Lexer::isKeyword(const std::string& identifier) const
{
    return keywords.find(identifier) != keywords.end(); // 判断标识符是否在关键字集合中
}

void Lexer::skipWhitespace()
{
    while (!isAtEnd() && (peek() == ' ' || peek() == '\t' || peek() == '\n'))
    {
        if(peek()=='\n')line_num++;
        advance();
    }
}


void Lexer::skipComment()
{
    currentPos--;   // 进入函数时，制作指向触发注释符号位置的下一位，因此先回退再处理
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
        {
            // 多行注释
            advance(); // consume '*'
            while (true)
            {
                if (peek() == '*' && peek() == '/')
                {
                    advance(); // consume '*'
                    advance(); // consume '/'
                    break;
                }
                if (isAtEnd())
                {
                    // 未找到结束符，抛出错误
                    //throw std::runtime_error("Unterminated comment.");
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
    else if(peek() == '#') // '#'也认为是注释
    {
        while (!isAtEnd() && peek() != '\n') advance();
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
    if (isKeyword(identifier)) return Token(TokenType::KEYWORD, identifier); // 如果是关键字，将其标记为关键字类型
    else return Token(TokenType::IDENTIFIER, identifier); // 否则标记为普通标识符类型
}

Token Lexer::parseNumber()
{
    // 解析数字
    std::string number;
    bool has_exist_point =false;
    while (!isAtEnd() && (isDigit(peek()) || peek() == '.'))
    {
        if(peek()=='.')
        {
            if(!has_exist_point)
                has_exist_point=true;
            else
            {
                // Error
                advance();
                return Token(TokenType::INVALID, ".");
            }
        }
        number += peek();
        advance();
    }
    if(has_exist_point) return Token(TokenType::FLOAT, number);
    else return Token(TokenType::INTEGER, number);
}

Token Lexer::parseSymbol()
{
    // 解析符号和运算符
    char symbol = advance();
    switch (symbol)
    {
        case ';': return Token(TokenType::SEMICOLON, ";");
        case '(':return Token(TokenType::LEFT_PAREN, "(");
        case ')':return Token(TokenType::RIGHT_PAREN, ")");
        case '[':return Token(TokenType::LEFT_BRACKET, "[");
        case ']':return Token(TokenType::RIGHT_BRACKET, "]");
        case '{':return Token(TokenType::LEFT_BRACE, "{");
        case '}':return Token(TokenType::RIGHT_BRACE, "}");
        case '"':return Token(TokenType::D_MARKS, "\"");
        case '\'':return Token(TokenType::S_MARKS, "'");
        case '.':return Token(TokenType::MEMBER, ".");
        case '+':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::PLUS_FORWARD,"+=");
                }
                default:
                {
                    return Token(TokenType::PLUS, "+");
                };
            }
        }
        case '-':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::MINUS_FORWARD,"-=");
                }
                default:
                {
                    return Token(TokenType::MINUS, "-");
                };
            }
        }
        case '*':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::MULTIPLY_FORWARD,"*=");
                }
                default:
                {
                    return Token(TokenType::MULTIPLY, "*");
                };
            }
        }
        case '/':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::DIVIDE_FORWARD,"/=");
                }
                case '/':
                {
                    skipComment();
                    return Token(TokenType::EMPTY,"");
                }
                default:
                {
                    return Token(TokenType::DIVIDE, "/");
                };
            }
        }
        case '=':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::EQUAL,"==");
                }
                default:
                {
                    return Token(TokenType::ASSIGNMENT,"=");
                };
            }
        }
        case '&':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::AND_FORWARD,"&=");
                }
                case '&':
                {
                    advance();
                    return Token(TokenType::LOGICAL_AND,"&&");
                }
                default:
                {
                    return Token(TokenType::AND,"&");
                };
            }
        }
        case '|':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::OR_FORWARD,"|=");
                }
                case '|':
                {
                    advance();
                    return Token(TokenType::LOGICAL_OR,"||");
                }
                default:
                {
                    return Token(TokenType::OR,"|");
                };
            }
        }
        case '^':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::XOR_FORWARD,"^=");
                }
                default:
                {
                    return Token(TokenType::XOR,"^");
                };
            }
        }
        case '~':return Token(TokenType::NOT,"~");
        case '#':
        {
            skipComment();
            return Token(TokenType::EMPTY,"");
        }
        case ',':return Token(TokenType::COMMA,",");
        case '>':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::ABOVE_OR_EUQAL,">=");
                }
                default:
                {
                    return Token(TokenType::ABOVE,">");
                };
            }
        }
        case '<':
        {
            switch(peek())
            {
                case '=':
                {
                    advance();
                    return Token(TokenType::BELOW_OR_EUQAL,"<=");
                }
                default:
                {
                    return Token(TokenType::BELOW,"<");
                };
            }
        }
        default:
        {
            std::string invalid_string;
            invalid_string+=symbol;
            return Token(TokenType::INVALID,invalid_string);
        }
    }
}

bool Lexer::LexicalAnalyze(std::vector<Token> &tokens)
{
    while (!isAtEnd())
    {
        skipWhitespace();   // 跳过' '、'\n'、'\t'
        if (peek() >= 'a' && peek() <= 'z' || peek() >= 'A' && peek() <= 'Z' || peek() == '_')    // id
        {
            tokens.push_back(parseIdentifier());
        }
        else if(peek() >= '0' && peek() <= '9')
        {
            tokens.push_back(parseNumber());
        }
        else
        {
            tokens.push_back(parseSymbol());
        }
    }
    return true;
}