//
// Created by icelake on 24-4-23.
//

#ifndef LITECOMPILER_C_ERROR_H
#define LITECOMPILER_C_ERROR_H

#include "../LexicalAnalysis/Lexer.h"

/**
 * @brief 报告词法分析中的错误信息。
 * @param line 出现错误的行数
 * @param message 错误消息描述
 **/
void error(size_t line, std::string message);

#endif //LITECOMPILER_C_ERROR_H
