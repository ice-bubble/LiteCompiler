//
// Created by Ice-bubble on 24-4-21.
//

#ifndef LEXER_H
#define LEXER_H

#include "../Token/Token.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <map>

/**
 * @brief Lexer类，用于对输入字符串进行词法分析，生成标记序列。
 *        Lexer对象维护了输入字符串、当前位置等状态信息，并提供了词法分析所需的各种功能函数。
 **/
class Lexer
{
public:
    /**
     * @brief Lexer类的构造函数，用于初始化Lexer对象。
     * @param input 要进行词法分析的输入字符串
     **/
    Lexer(const std::string &input);

    /**
     * @brief 对输入的字符串进行词法分析，生成对应的标记序列。
     * @param tokens 词法分析得到的标记将存储在此向量中
     * @return bool 如果词法分析成功则返回true，否则返回false
     **/
    bool LexicalAnalyze(std::vector<Token> &tokens);

    /**
     * @brief 遍历map输出所有Keyword。
     **/
    static void printKeyword();

    /**
     * @brief 遍历map获取所有Keyword。
     * @return 返回所有待输出字符串按照格式拼接而成的整个字符串【含换行】
     **/
    static std::string getAllKeyword();

private:
    bool exist_error; // 是否存在词法错误，初始值为false
    std::string input; // 输入的内容
    size_t currentPos; // 当前所指向的元素位置
    size_t line_num; // 行号
    std::string *str_temp; // 比较字符串是的临时变量
    static std::map<std::string, TokenType> keywords; // map类型数据，关键字KEYWORD与TokenType关系映射表
    /**
     * @brief 返回当前字符流的下一个字符，但不消耗它。
     * @return char 下一个字符
     **/
    char peek() const;

    /**
     * @brief 返回当前字符流的下一个字符，但不消耗它。
     * @return char 下一个字符
     **/
    char peekNext() const;

    /**
     * @brief 消耗并返回当前字符流的下一个字符。
     * @return char 消耗的字符
     **/
    char advance();

    /**
     * @brief 检查当前字符流是否已到达末尾。
     * @return bool 如果已到达末尾则返回true，否则返回false
     **/
    bool isAtEnd() const;

    /**
     * @brief 检查给定的字符是否为字母或下划线，正则表达式描述：([a-zA-Z]|_)+。
     * @param c 要检查的字符
     * @return bool 如果是字母则返回true，否则返回false
     **/
    bool isAlpha(char c) const;

    /**
     * @brief 检查给定的字符是否为数字：[0-9]+。
     * @param c 要检查的字符
     * @return bool 如果是数字则返回true，否则返回false
     **/
    bool isDigit(char c) const;

    /**
     * @brief 跳过当前字符流中的空白字符。
     **/
    void skipWhitespace();

    /**
     * @brief 跳过当前字符流中的注释。
     * @return 单行注释返回true；多行注释返回true表示正常闭合，false表示多行注释未闭合
     **/
    bool skipComment();

    /**
     * @brief 解析标识符并返回相应的标记。
     * @return Token 解析得到的标识符标记
     **/
    Token parseIdentifier();

    /**
     * @brief 解析字符串并返回相应的标记。
     * @param start_ch 字符串开头的符号，用于后续判断是否是同一个符号闭合【这里字符串用单引号闭合或双引号闭合表示】
     * @return Token 解析得到的字符串标记
     **/
    Token parseString(char start_ch);

    /**
     * @brief 解析数字并返回相应的标记。
     * @return Token 解析得到的数字标记
     **/
    Token parseNumber();

    /**
     * @brief 解析符号并返回相应的标记。
     * @return Token 解析得到的符号标记
     **/
    Token parseSymbol();

    /**
     * @brief 检查给定的标识符是否为关键字，并返回相应的标记类型。
     * @param keyword 要检查的标识符
     * @return TokenType 关键字的标记类型，如果不是关键字则返回IDENTIFIER
     **/
    TokenType checkKeyword(const std::string &keyword) const; //声明为常量成员函数
};

#endif // LEXER_H
