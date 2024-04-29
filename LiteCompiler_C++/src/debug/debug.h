//
// Created by Ice-bubble on 24-4-21.
//

#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <vector>
#include "../Token/Token.h"
#include "../LexicalAnalysis/Lexer.h"

/*
*    注意！！输出到文件和输出到终端的输出函数是不同的，如有修改输出格式请一并修改其对应的函数
*    函数对应关系：
*    Debug::printTokens         <-->    Debug::getAllTokens
*    Debug::printSymbolTokens   <-->    Debug::getAllSymbolTokens
*    Lexer::printKeyword        <-->    Lexer::getAllKeyword
*/


/**
 * @brief Debug类，主要用于输出中间过程的内容
 */
class Debug
{
public:
     /**
     * @brief REPL（交互式解释器）循环。
     *
     * 用户可以在控制台输入代码，并对其进行词法分析,按下ctrl+C强制退出。
     *
     */
     static void repl();
    /**
     * @brief 输出标记向量中的所有标记。
     * @param tokens 要打印的标记向量（vector类型）
     **/
     static void printTokens(const std::vector<Token> &tokens);

    /**
     * @brief 输出标记向量中的KEYWORD和IDENTIFIER标记【其中相同的KEYWORD或IDENTIFIER标记只输出一次】。
     * @param tokens 要打印的标记向量（vector类型）
     **/
     static void printSymbolTokens(const std::vector<Token> &tokens);

    /**
     * @brief 输出标记向量中的所有标记。
     * @param tokens 要打印的标记向量（vector类型）
     * @return std::string类型的，所有待输出内容整合成的一个字符串【含换行】
     **/
     static std::string getAllTokens(const std::vector<Token> &tokens);

    /**
     * @brief 输出标记向量中的KEYWORD和IDENTIFIER标记【其中相同的KEYWORD或IDENTIFIER标记只输出一次】。
     * @param tokens 要打印的标记向量（vector类型）
     * @return std::string类型的，所有待输出内容整合成的一个字符串【含换行】
     **/
     static std::string getAllSymbolTokens(const std::vector<Token> &tokens);
};

std::vector<std::string> removeDuplicates(const std::vector<std::string> &input);
#endif // DEBUG_H
