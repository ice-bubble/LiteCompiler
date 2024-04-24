/**
 * @file token.h
 * @brief Token类及相关函数的声明。
 * @author lzy
 * @date 24-4-22
 */

#ifndef ROBIN_TOKEN_H
#define ROBIN_TOKEN_H

#include "../common.h"

/**
 * @brief 命名空间，包含了token相关的类和函数。
 */
namespace Token {
    /**
     * @brief 用于区分不同token类型的枚举体，一种token对应一种成员。
     */
    enum TokenType {
        // Single-character tokens. 单字符词法
        TOKEN_LEFT_PAREN,       ///< 左括号 (，用于表示代码中的分组或函数调用。
        TOKEN_RIGHT_PAREN,      ///< 右括号 )，用于表示代码中的分组或函数调用。
        TOKEN_LEFT_BRACE,       ///< 左花括号 {，用于表示代码中的代码块的开始。
        TOKEN_RIGHT_BRACE,      ///< 右花括号 }，用于表示代码中的代码块的结束。
        TOKEN_LEFT_BRACKET,     ///< 左方括号 [，用于表示数组下标访问或其他用途。
        TOKEN_RIGHT_BRACKET,    ///< 右方括号 ]，用于表示数组下标访问或其他用途。
        TOKEN_COMMA,            ///< 逗号 ,，用于分隔函数参数或数组元素等。
        TOKEN_DOT,              ///< 点 .，用于访问对象的属性或方法。
        TOKEN_MINUS,            ///< 减号 -，用于表示减法操作。
        TOKEN_PLUS,             ///< 加号 +，用于表示加法操作。
        TOKEN_SEMICOLON,        ///< 分号 ;，用于表示语句的结束。
        TOKEN_SLASH,            ///< 斜杠 /，用于表示除法操作。
        TOKEN_STAR,             ///< 星号 *，用于表示乘法操作。
        TOKEN_MOD,              ///< 百分号 %，用于表示取模操作

        // One or two character tokens. 一或两字符词法
        TOKEN_NOT_EQUAL,       ///< 感叹号等号 !=，用于表示不等于比较操作。
        TOKEN_EQUAL,            ///< 单个等号 =，用于赋值操作。
        TOKEN_EQUAL_EQUAL,      ///< 双等号 ==，用于相等比较操作。
        TOKEN_GREATER,          ///< 大于号 >，用于大于比较操作。
        TOKEN_GREATER_EQUAL,    ///< 大于等于号 >=，用于大于等于比较操作。
        TOKEN_LESS,             ///< 小于号 <，用于小于比较操作。
        TOKEN_LESS_EQUAL,       ///< 小于等于号 <=，用于小于等于比较操作。

        // Literals. 字面量
        TOKEN_IDENTIFIER,       ///< 标识符，用于表示变量名、函数名等
        TOKEN_STRING,           ///< 字符串字面量，表示一串文本。
        TOKEN_INT,              ///< 数字字面量，表示整数。
        TOKEN_REAL,             ///< 数字字面量，表示浮点数。

        // Keywords. 关键字||三个逻辑运算也是符号
        TOKEN_AND,              ///< and &&
        TOKEN_BREAK,            ///< break
        TOKEN_CLASS,            ///< class
        TOKEN_CONTINUE,         ///< continue
        TOKEN_DO,               ///< do
        TOKEN_DOUBLE,           ///< double
        TOKEN_ELSE,             ///< else
        TOKEN_FALSE,            ///< false
        TOKEN_FOR,              ///< for
        TOKEN_FUNCTION,         ///< function
        TOKEN_IF,               ///< if
        TOKEN_INTEGER,          ///< integer
        TOKEN_NIL,              ///< nil
        TOKEN_NOT,              ///< not !
        TOKEN_OR,               ///< or ||
        TOKEN_PRINT,            ///< print
        TOKEN_READ,             ///< read
        TOKEN_REPEAT,           ///< repeat
        TOKEN_RETURN,           ///< return
        TOKEN_SUPER,            ///< super
        TOKEN_THIS,             ///< this
        TOKEN_TRUE,             ///< true
        TOKEN_UNTIL,            ///< until
        TOKEN_VAR,              ///< var
        TOKEN_WHILE,            ///< while
        TOKEN_WRITE,            ///< write

        TOKEN_EOF               ///< EOF,表示已经到达代码文件的末尾。
    };

     /**
      * @brief 用于记录一个token的信息。
      */
    class Token {
    private:
        TokenType type;           ///< type: 表示标记的类型，是一个枚举类型 TokenType 的实例。
        std::string lexeme;       ///< lexeme: 表示标记在源代码中的文本形式，即标记的字符串表示。
        Object literal;           ///< literal: 表示标记的字面量值，可以是任意类型的对象，用于表示标记的具体值。
        size_t line;              ///< line: 表示标记在源代码中所在的行号。

        static std::map<std::string, TokenType> keywords;  ///< 关键字字符串到标记类型(TokenType)的映射表。
        static std::vector<std::string> tokenStrings;      ///< 将TokenType枚举值映射到它们的字符串表示的向量。

    public:

        /**
         * @brief Token类的构造函数。
         * @param type Token的TokenType类型。
         * @param lexeme Token的词法单元文本形式。
         * @param literal Token的字面量值。
         * @param line Token所在的行号。
         * @return Token 返回构造的新对象
         */
        Token(TokenType type, std::string lexeme, Object literal,size_t line);

        /**
         * @brief 生成Token对象的字符串表示。
         * @return std::string Token对象的字符串表示。
         */
        std::string toString() const;

        /**
         * @brief 根据token类型获取字面量值的字符串表示。
         * @return  std::string 字面量值的字符串表示。
         */
        std::string getLiteralString() const;

        /**
         * @brief 根据关键字文本获取对应的 TokenType。
         * @note 对于不是关键字的文本，返回TOKEN_EOF
         * @param text 关键字文本。
         * @return TokenType 对应的 TokenType 值，如果关键字不存在则返回 TOKEN_EOF。
        */
        static TokenType getKeywordTypeInMap(const std::string& text);

       /**
        * @brief 根据 TokenType 获取对应的字符串表示。
        * @note 错误字符串:"Error: Invalid token type"
        * @param tokentype 要获取字符串的 TokenType。
        * @return std::string  TokenType 对应的字符串表示，如果 TokenType 无效则返回错误字符串。
        */
        static std::string gettokenStringInMap(TokenType tokentype);

    };
}

#endif //ROBIN_TOKEN_H
