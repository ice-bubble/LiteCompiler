/**
 * @file type.h
 * @brief Type 类定义相关
 * @date 24-5-15
 */

#ifndef ROBIN_TYPE_H
#define ROBIN_TYPE_H

#include <utility>

#include "../common.h"
#include "../token/token.h"


/**
 * @brief 用于区分不同的标识符类型的枚举体。
 */
enum IdentifierType {
    INT_,            ///< 整数类型
    REAL_,           ///< 实数类型
    CHAR_,           ///< 字符类型
    BOOL,            ///< 布尔类型
    ARRAY_,          ///< 数组类型
    FUNC_            ///< 函数类型
};

/**
 * @brief 所有类型的基类。
 */
class Type {
public:
    virtual ~Type() = default;
};

/**
 * @brief 整数类型类。
 */
class INT_Type : Type {
public:
    IdentifierType thisType;     ///< 具体的整数类型

    explicit INT_Type(IdentifierType thisType) : thisType(thisType) {}
};

/**
 * @brief 浮点数类型类。
 */
class REAL_Type : Type {
public:
    IdentifierType thisType;     ///< 具体的浮点数类型

    explicit REAL_Type(IdentifierType thisType) : thisType(thisType) {}
};

/**
 * @brief 字符类型类。
 */
class CHAR_Type : Type {
public:
    IdentifierType thisType;     ///< 具体的字符类型

    explicit CHAR_Type(IdentifierType thisType) : thisType(thisType) {}
};

/**
 * @brief 布尔类型类。
 */
class BOOL_Type : Type {
public:
    IdentifierType thisType;     ///< 具体的布尔类型

    explicit BOOL_Type(IdentifierType thisType) : thisType(thisType) {}
};

/**
 * @brief 函数类型类。
 */
class FUNC_Type : Type {
public:
    IdentifierType thisType;     ///< 具体的函数类型

    explicit FUNC_Type(IdentifierType thisType) : thisType(thisType) {}
};

/**
 * @brief 数组类型类。
 */
class ARRAY_Type : Type {
public:
    IdentifierType thisType;     ///< 具体的数组类型
    SharedPtr<Type> innerType;   ///< 数组中元素的类型
    size_t length;               ///< 数组的长度

    ARRAY_Type(IdentifierType thisType, SharedPtr<Type> innerType, size_t length)
            : thisType(thisType), innerType(std::move(innerType)), length(length) {}
};

#endif //ROBIN_TYPE_H
