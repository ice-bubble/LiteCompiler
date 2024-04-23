//
// Created by Ice-bubble on 24-4-21.
//

#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <vector>
#include "../Token/Token.h"

/**
 * @brief Debug类，主要用于输出中间过程的内容
 */
class Debug
{
public:
    /**
     * @brief 打印标记向量中的所有标记。
     * @param tokens 要打印的标记向量（vector类型）
     **/
    static void printTokens(const std::vector<Token> &tokens);
};

#endif // DEBUG_H
