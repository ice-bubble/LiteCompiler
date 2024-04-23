//
// Created by Ice-bubble on 24-4-21.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// 定义标记类型【关键字、标识符（id）、运算符等】
enum class TokenType
{
    // KEYWORDS [字符串升序排列]
    KEYWORD_AND,
    KEYWORD_BREAK,
    KEYWORD_CHAR,
    KEYWORD_CLASS,
    KEYWORD_CONTINUE,
    KEYWORD_DO,
    KEYWORD_DOUBLE,
    KEYWORD_ELSE,
    KEYWORD_EOF,
    KEYWORD_FALSE,
    KEYWORD_FOR,
    KEYWORD_FUNCTION,
    KEYWORD_IF,
    KEYWORD_INTEGER,
    KEYWORD_NIL,
    KEYWORD_NOT,
    KEYWORD_NULL,
    KEYWORD_OR,
    KEYWORD_PRINT,
    KEYWORD_READ,
    KEYWORD_REPEAT,
    KEYWORD_RETURN,
    KEYWORD_SUPER,
    KEYWORD_THIS,
    KEYWORD_TRUE,
    KEYWORD_UNTIL,
    KEYWORD_VAR,
    KEYWORD_WHILE,
    KEYWORD_WRITE,

    // 标识符
    IDENTIFIER, // id

    // 数据类型
    INTEGER, // int
    FLOAT, // double、float
    STRING, // string（正常字符串）

    // 分号
    SEMICOLON, // ";"

    // 运算符
    ASSIGNMENT, // "="赋值运算符
    PLUS, // "+"
    PLUS_FORWARD, // "+="
    MINUS, // "-"
    MINUS_FORWARD, // "-="
    MULTIPLY, // "*"
    MULTIPLY_FORWARD, // "*="
    DIVIDE, // "/"
    DIVIDE_FORWARD, // "/="
    AND, // "&"
    AND_FORWARD, // "&="
    LOGICAL_AND, // "&&"
    OR, // "|"
    OR_FORWARD, // "|="
    LOGICAL_OR, // "||"
    XOR, // "^"
    XOR_FORWARD, // "^="
    NOT, // "~"，按位取反
    LOGICAL_NOT, // "!"，逻辑非
    NOT_EQUAL, //"!="
    EQUAL, // "=="
    ABOVE, // ">"
    BELOW, // "<"
    ABOVE_OR_EUQAL, // ">="
    BELOW_OR_EUQAL, // "<="
    LEFT_PAREN, // "("
    RIGHT_PAREN, // ")"
    LEFT_BRACKET, // "["
    RIGHT_BRACKET, // "]"
    LEFT_BRACE, // "{"
    RIGHT_BRACE, // "}"
    D_MARKS, // "
    S_MARKS, // '
    MEMBER, // "."
    MEMBER_PTR, // "->"
    COMMA, // ","

    EMPTY, // 空
    INVALID // 非法的标记【词法错误】
};

class Token
{
public:
    /**
    * @brief Token类的构造函数
    * @param type 标记的类型
    * @param value 标记原始值（字符串类型存储）
    **/
    Token(TokenType type, const std::string &value);

    /**
    * @brief Token类的构造函数
    * @return TokenType 标记类型
    **/
    TokenType getType() const;

    /**
    * @brief Token类的构造函数
    * @return std::string 标记原始值（字符串类型存储）
    **/
    std::string getValue() const;

private:
    TokenType type; // Token类成员——标记类型
    std::string value; // Token类成员——标记原始值（字符串类型存储）
};

#endif // TOKEN_H
