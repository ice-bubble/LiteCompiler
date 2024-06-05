

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

        static Map<Pair<IdentifierType, IdentifierType>, IdentifierType> typeTransform;

        static Map<Pair<IdentifierType, IdentifierType>, IdentifierType> typeForceTransform;

        static Map<IdentifierType, String> typeToString;

        static SharedPtr<Type> chooseReturnType(SharedPtr<Type> t1, SharedPtr<Type> t2, size_t line);

        static bool isSameType(SharedPtr<Type> t1, SharedPtr<Type> t2);
    };
}

#endif //ROBIN_TYPE_H
