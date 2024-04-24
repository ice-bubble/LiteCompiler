//
// Created by Ice-bubble on 24-4-21.
//

#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <vector>
#include "../Token/Token.h"
#include "../LexicalAnalysis/Lexer.h"

/**
 * @brief Debug类，主要用于输出中间过程的内容
 */
class Debug
{
public:
    /**
     * @brief 输出标记向量中的所有标记。
     * @param tokens 要打印的标记向量（vector类型）
     **/
    static void printTokens(const std::vector<Token> &tokens);

    /**
     * @brief 输出标记向量中的KEYWORD和IDENTIFIER标记【其中相同的IDENTIFIER标记只输出一次】。
     * @param tokens 要打印的标记向量（vector类型）
     **/
    static void printsymbolTokens(const std::vector<Token> &tokens);
};

std::vector<std::string> removeDuplicates(const std::vector<std::string> &input);
#endif // DEBUG_H
