/**
 * @file error.cpp
 * @brief error函数的实现。
 * @author lzy
 * @date 24-4-22
 */

#include "error.h"

void error(size_t line, const String &message) {
    std::cerr << "[line: " << line << "] Error:" << message << std::endl;
}