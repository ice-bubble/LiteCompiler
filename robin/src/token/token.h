//
// Created by icelake on 24-4-22.
//

#ifndef ROBIN_TOKEN_H
#define ROBIN_TOKEN_H

#include "../common.h"

namespace Token {
    enum TokenType {
        // Single-character tokens. 单字符词法
        TOKEN_LEFT_PAREN,       //左括号 (，用于表示代码中的分组或函数调用。
        TOKEN_RIGHT_PAREN,      //右括号 )，用于表示代码中的分组或函数调用。
        TOKEN_LEFT_BRACE,       //左花括号 {，用于表示代码中的代码块的开始。
        TOKEN_RIGHT_BRACE,      //右花括号 }，用于表示代码中的代码块的结束。
        TOKEN_LEFT_BRACKET,     //左方括号 [，用于表示数组下标访问或其他用途。
        TOKEN_RIGHT_BRACKET,    //右方括号 ]，用于表示数组下标访问或其他用途。
        TOKEN_COMMA,            //逗号 ,，用于分隔函数参数或数组元素等。
        TOKEN_DOT,              //点 .，用于访问对象的属性或方法。
        TOKEN_MINUS,            //减号 -，用于表示减法操作。
        TOKEN_PLUS,             //加号 +，用于表示加法操作。
        TOKEN_SEMICOLON,        //分号 ;，用于表示语句的结束。
        TOKEN_SLASH,            //斜杠 /，用于表示除法操作。
        TOKEN_STAR,             //星号 *，用于表示乘法操作。
        TOKEN_MOD,              //百分号 %，用于表示取模操作

        // One or two character tokens. 一或两字符词法
        TOKEN_NOT_EQUAL,       //双感叹号 !=，用于表示不等于比较操作。
        TOKEN_EQUAL,            //单个等号 =，用于赋值操作。
        TOKEN_EQUAL_EQUAL,      //双等号 ==，用于相等比较操作。
        TOKEN_GREATER,          // 大于号 >，用于大于比较操作。
        TOKEN_GREATER_EQUAL,    //大于等于号 >=，用于大于等于比较操作。
        TOKEN_LESS,             // 小于号 <，用于小于比较操作。
        TOKEN_LESS_EQUAL,       //小于等于号 <=，用于小于等于比较操作。

        // Literals. 字面量
        TOKEN_IDENTIFIER,       //标识符，用于表示变量名、函数名等
        TOKEN_STRING,           //字符串字面量，表示一串文本。
        TOKEN_INT,              //数字字面量，表示整数。
        TOKEN_REAL,             //数字字面量，表示浮点数。

        // Keywords. 关键字||三个逻辑运算也是符号
        TOKEN_AND,              //and &&
        TOKEN_BREAK,
        TOKEN_CLASS,
        TOKEN_CONTINUE,
        TOKEN_DOUBLE,
        TOKEN_ELSE,
        TOKEN_FALSE,
        TOKEN_FOR,
        TOKEN_FUNCTION,
        TOKEN_IF,
        TOKEN_INTEGER,
        TOKEN_NIL,
        TOKEN_NOT,              //not !
        TOKEN_OR,               //or ||
        TOKEN_PRINT,
        TOKEN_RETURN,
        TOKEN_SUPER,
        TOKEN_THIS,
        TOKEN_TRUE,
        TOKEN_VAR,
        TOKEN_WHILE,

        TOKEN_EOF           // 表示已经到达代码文件的末尾，用于解析器或编译器判断是否已经处理完所有的代码。
    };


    class Token {
    private:
        TokenType type;//type: 表示标记的类型，是一个枚举类型 TokenType 的实例。
        std::string lexeme;//lexeme: 表示标记在源代码中的文本形式，即标记的字符串表示。
        Object literal;//literal: 表示标记的字面量值，可以是任意类型的对象，用于表示标记的具体值。
        int line;//line: 表示标记在源代码中所在的行号。

    public:
        Token(TokenType type, std::string lexeme, Object literal, int line);

        std::string toString() const;

        std::string getLiteralString() const;
    };
}

#endif //ROBIN_TOKEN_H
