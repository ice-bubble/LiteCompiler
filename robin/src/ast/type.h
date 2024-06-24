#ifndef ROBIN_TYPE_H
#define ROBIN_TYPE_H

#include "../common.h"
#include "../token/token.h"


namespace ast {

    enum IdentifierType {
        BASE_,           ///< 基础类型
        VAR_,            ///< 未确定类型
        ARRAY_,          ///< 数组类型
        FUNC_,           ///< 函数类型
        STRING_,         ///< 字符串类型
        NIL_,            ///< 空类型
        BOOL_,           ///< 布尔类型
        CHAR_,           ///< 字符类型
        INT_,            ///< 整数类型
        REAL_            ///< 实数类型
    };


    class Type {
    public:
        SharedPtr<Type> varType = nullptr;
        IdentifierType selfType = BASE_;
        String width = "0";
        String length = "0";

        Type() = default;//构造函数，类型为BASE_

        Type(const SharedPtr<Type> &varType, String width, String length);

        explicit Type(IdentifierType selfT);

        String toString();

        /**
         * 用于单个变量类型转化的Map
         */
        static Map<Pair<IdentifierType, IdentifierType>, IdentifierType> typeTransform;

        /**
         * 用于两个变量运算时类型转化的Map
         */
        static Map<Pair<IdentifierType, IdentifierType>, IdentifierType> typeForceTransform;

        /**
         * 将变量映射为字符串
         */
        static Map<IdentifierType, String> typeToString;

        /**
         * @param t1 第一种返回类型
         * @param t2 第二种返回类型
         * @param line 源代码行号
         * @brief 为函数定义选择合适的返回类型，对于某些情况会直接报错结束
         * @return 选择的合法返回类型
         */
        static SharedPtr<Type> chooseReturnType(SharedPtr<Type> t1, SharedPtr<Type> t2, size_t line);

        /**
         * @param t1 第一种类型
         * @param t2 第二种类型
         * @brief 判断两种类型是否相等
         * @return 两种类型相同返回1，否则返回0
         */
        static bool isSameType(SharedPtr<Type> t1, SharedPtr<Type> t2);
    };
}

#endif //ROBIN_TYPE_H
