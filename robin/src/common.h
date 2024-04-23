/**
 * @file common.h
 * @brief 一些项目用到的宏定义和头文件存放在这里
 * @author lzy
 * @date 24-4-22
 */

#ifndef ROBIN_COMMON_H
#define ROBIN_COMMON_H

#include <iostream>
#include <vector>
#include <string>
#include<map>
#include <vector>
#include <any>


#define DEBUG_FLAG                  ///< 启用此宏定义使得主函数#include<debug.h>
#define DEBUG_PRINT_TOKENLIST       ///< 启用此宏定义使得主函数打印tokenList

typedef std::any Object;

template<typename T>
using List = std::vector<T>;

#endif //ROBIN_COMMON_H
