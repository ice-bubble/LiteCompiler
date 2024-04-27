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


#define toVarString(var) #var       ///< 将变量名转为字符串


template<typename T>
using List = std::vector<T>;

template<typename Key, typename Value>
using Map = std::map<Key, Value>;

using String = std::string;

using Object = std::any;



// 使用 Map<int, std::string> 的形式来表示 std::map<int, std::string>




#endif //ROBIN_COMMON_H
