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
#include <unordered_set>
#include <utility>
#include <memory>
#include <stack>
#include <type_traits>
#include "fmt/core.h"


//#define PRINT_TOKENLIST
//#define PRINT_PARSER_PROCESS

#define toVarString(var) #var       ///< 将变量名转为字符串

template<typename T>
using List = std::vector<T>;

template<typename Key, typename Value>
using Map = std::map<Key, Value>;

template<typename T>
using Set = std::unordered_set<T>;

template<typename TYPE>
using SharedPtr = std::shared_ptr<TYPE>;

template<typename TYPE>
using WeakPtr = std::weak_ptr<TYPE>;

template<typename T1, typename T2>
using Pair = std::pair<T1, T2>;

template<typename Type>
using Stack = std::stack<Type>;

using String = std::string;

using StringView = std::string_view;

using Object = std::any;


#endif //ROBIN_COMMON_H
