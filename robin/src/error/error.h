/**
 * @file error.h
 * @brief error函数的声明。
 * @date 24-4-22
 */

#ifndef ROBIN_ERROR_H
#define ROBIN_ERROR_H

#include "../common.h"

/**
 * @brief 使用给定的源代码行号和错误消息的描述打印错误消息
 * @param line 源代码行号
 * @param message 错误消息的描述
 */
void error(size_t line, const String& message);

#endif //ROBIN_ERROR_H
