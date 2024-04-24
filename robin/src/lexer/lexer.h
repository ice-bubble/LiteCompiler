/**
 * @file lexer.h
 * @brief Lexer类及相关函数的声明。
 * @author lzy
 * @date 24-4-22
 */

#ifndef ROBIN_LEXER_H
#define ROBIN_LEXER_H

#include "../common.h"
#include "../token/token.h"

/**
 * @brief 命名空间，包含了用于词法分析的类和函数。
 */
namespace Lexer {

    /**
     * @brief 用于对源代码进行词法分析的 Lexer 类。
     */
    class Lexer {
    private:


        std::string source;                                       ///< 要进行词法分析的源代码字符串。
        size_t start = 0;                                         ///< 用于进行词法分析的起始索引。
        size_t current = 0;                                       ///< 当前用于词法分析的索引。
        size_t line = 1;                                          ///< 当前处理的行号。
        std::vector<Token::Token> tokens;                         ///< 从源代码生成的token列表。
    public:

        /**
         * @brief 使用给定的源代码字符串构造一个 Lexer 对象。
         * @param source 要进行词法分析的源代码字符串。
         * @return Lexer 返回构造的新对象
         */
        Lexer(std::string source);

        /**
        * @brief 对源代码进行词法分析，并返回标记列表。
        * @return 包含源代码标记的token列表。
        */
        std::vector<Token::Token> scanTokens();

    private:

        /**
         * @brief 扫描源代码，生成一个标记(token)。
         * @note 调用一次消费一个token。
         */
        void scanToken();

        /**
         * @brief 处理标识符标记。
         * @note 标识符是可以是一个关键字或者一个标识符。
         */
        void _identifier();

        /**
         * @brief 处理浮点数标记。
         */
        void _real();

        /**
         * @brief 处理数字标记。
         * @note 处理的对象可以是浮点数也可以是整数
         */
        void _number();

        /**
         * @brief 处理字符串标记。
         */
        void _string();

        /**
         * @brief 处理斜杠标记。
         * @note 斜杠开头有三种情况：
         * @note 1.单行注释
         * @note 2.多行注释
         * @note 3.除号
         */
        void slash();

        /**
         * @brief 匹配预期字符。
         * @param expected 预期的字符。
         * @return bool 如果匹配成功，则返回 true，否则返回 false。
         */
        bool match(char expected);

        /**
         * @brief 查看当前字符。
         * @return char 返回当前字符。
         */
        char peek();

        /**
         * @brief 查看下一个字符。
         * @return char 返回下一个字符。
         */
        char peekNext();

        /**
        * @brief 判断字符是否为字母或者下划线。
        * @param c 要判断的字符。
        * @return bool 如果是字母或者下划线，则返回 true，否则返回 false。
        */
        static bool isAlpha(char c);

        /**
         * @brief 判断字符是否为字母或数字或者下划线。
         * @param c 要判断的字符。
         * @return bool 如果是字母或数字或者下划线，则返回 true，否则返回 false。
         */
        static bool isAlphaNumeric(char c);

        /**
         * @brief 判断字符是否为数字。
         * @param c 要判断的字符。
         * @return bool 如果是数字，则返回 true，否则返回 false。
         */
        static bool isDigit(char c);

        /**
         * @brief 检查是否到达源代码末尾。
         * @return bool 如果已经到达末尾，则返回 true，否则返回 false。
         */
        bool isAtEnd();

        /**
         * @brief 向前移动当前索引，并返回移动前索引对应的字符（即当前索引对应的字符）。
         * @return char 索引移动前对应的字符（即当前索引对应的字符）。
         */
        char advance();

        /**
         * @brief 添加标记到标记列表。
         * @param type 标记类型。
         */
        void addToken(Token::TokenType type);

        /**
         * @brief 添加带字面量的标记到标记列表。
         * @param type 标记类型。
         * @param literal 标记字面量。
         */
        void addToken(Token::TokenType type, const Object &literal);
    };

}


#endif //ROBIN_LEXER_H
