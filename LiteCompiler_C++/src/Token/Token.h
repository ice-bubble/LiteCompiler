//
// Created by Ice-bubble on 24-4-21.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

/**
 * @brief 标记类型枚举，包括关键字、标识符（id）、数据类型、运算符等。
 **/
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
    KEYWORD_STRING,
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
    PLUS_ASSIGNMENT, // "+="
    MINUS, // "-"
    MINUS_ASSIGNMENT, // "-="
    MULTIPLY, // "*"
    MULTIPLY_ASSIGNMENT, // "*="
    DIVIDE, // "/"
    DIVIDE_ASSIGNMENT, // "/="
    AND, // "&"
    AND_ASSIGNMENT, // "&="
    LOGICAL_AND, // "&&"
    OR, // "|"
    OR_ASSIGNMENT, // "|="
    LOGICAL_OR, // "||"
    XOR, // "^"
    XOR_ASSIGNMENT, // "^="
    MOD, // "%"
    MOD_ASSIGNMENT, // "%="
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

/**
 * @brief Token类，表示词法分析过程中的标记。
 *        Token对象包含标记的类型和原始值。
 **/
class Token
{
public:
    /**
    * @brief Token类的构造函数
    * @param type 标记的类型
    * @param value 标记原始值（字符串类型存储）
    * @param line_n 标记所在的行号
    **/
    Token(TokenType type, const std::string &value, size_t line_n);

    /**
    * @brief 获取Token的类型
    * @return TokenType 标记类型
    **/
    TokenType getType() const;

    /**
    * @brief 获取Token的原始值
    * @return std::string 标记原始值（字符串类型存储）
    **/
    std::string getValue() const;

private:
    TokenType type; // Token类成员——标记类型
    std::string value; // Token类成员——标记原始值（字符串类型存储）
    size_t line_num; // 标记位置的行号
};

#endif // TOKEN_H
