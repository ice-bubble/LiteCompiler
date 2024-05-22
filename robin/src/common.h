/**
 * @file common.h
 * @brief 一些项目用到的宏定义和头文件存放在这里
 * @date 24-4-22
 */

#ifndef ROBIN_COMMON_H
#define ROBIN_COMMON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <vector>
#include <any>
#include <utility>
#include <memory>
#include <stack>


#define DEBUG                       ///< 启用此宏定义使得主函数#include<debug.h>

#define toVarString(var) #var       ///< 将变量名转为字符串

template<typename T>
using List = std::vector<T>;

template<typename Key, typename Value>
using Map = std::map<Key, Value>;

template<typename TYPE>
using SharedPtr = std::shared_ptr<TYPE>;

template<typename T1, typename T2>
using Pair = std::pair<T1, T2>;

template<typename Type>
using Stack = std::stack<Type>;

using String = std::string;

using StringView = std::string_view;

using Object = std::any;


#endif //ROBIN_COMMON_H
