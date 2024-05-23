//
// Created by icelake on 24-4-23.
//

#ifndef LITECOMPILER_C_ERROR_H
#define LITECOMPILER_C_ERROR_H

#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include "../Token/Token.h"

/**
 * @brief 报告错误信息。
 * @param line 出现错误的行数
 * @param message 错误消息描述
 **/
void error(size_t line, std::string message);

/**
 * @brief 报告错误信息。
 * @param line 出现错误的行数
 * @param message 错误消息描述
 * @param error_output 错误消息汇总
 **/
void error(size_t line, std::string message, std::string &error_output);

/**
 * @brief 报告语法分析中的错误信息。
 * @param currentState 当前状态
 * @param currentToken 当前Token
 * @param index 当前位于Token序列的位置
 * @param stateStack 状态栈
 * @param symbolStack 符号栈
 * @return bool类型，true表示可以继续分析，false表示终止分析
 **/
bool error(const int currentState, Token currentToken, std::stack<Token> &symbolStack, std::string &error_output);

#endif //LITECOMPILER_C_ERROR_H
