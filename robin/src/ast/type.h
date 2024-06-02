

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
        String width;
        String length;

        virtual String toString() { return "type"; }

        static Map<Pair<IdentifierType, IdentifierType>, IdentifierType> typeTransform;

        static Map<IdentifierType, String> typeToString;

        static SharedPtr<Type> makeTypeInstance(ast::IdentifierType requestedType);

        static SharedPtr<Type> chooseReturnType(SharedPtr<Type> t1, SharedPtr<Type> t2, size_t line);

        Type() = default;

        Type(const SharedPtr<Type> &varType, String width, String length)
                : varType(varType), width(width), length(length) {}

        virtual ~Type() = default;
    };

    class BASE_Type : public Type {
    public:
        String toString() override { return "BASE_"; }

        BASE_Type() {
            width = "0";
            length = "0";
            selfType = BASE_;
        }
    };


    class INT_Type : public Type {
    public:
        String toString() override { return "INT_"; }

        INT_Type() {
            width = "8";
            length = "1";
            selfType = INT_;
        }
    };


    class REAL_Type : public Type {
    public:
        String toString() override { return "REAL_"; }

        REAL_Type() {
            width = "8";
            length = "1";
            selfType = REAL_;
        }
    };


    class CHAR_Type : public Type {
    public:
        String toString() override { return "CHAR_"; }

        CHAR_Type() {
            width = "1";
            length = "1";
            selfType = CHAR_;
        }
    };


    class STRING_Type : public Type {
    public:
        String toString() override { return "STRING_"; }

        STRING_Type() {
            width = "8";
            length = "1";
            selfType = STRING_;
        }
    };


    class BOOL_Type : public Type {
    public:
        String toString() override { return "BOOL_"; }

        BOOL_Type() {
            width = "1";
            length = "1";
            selfType = BOOL_;
        }
    };

    class FUNC_Type : public Type {
    public:
        IdentifierType returnType = NIL_;

        String toString() override { return "FUNC_"; }

        FUNC_Type() {
            width = "8";
            length = "1";
            selfType = FUNC_;
        }
    };


    class VAR_Type : public Type {
    public:
        String toString() override { return "VAR_"; }

        VAR_Type() {
            width = "8";
            length = "1";
            selfType = VAR_;
        }
    };

    class NIL_Type : public Type {
    public:
        String toString() override { return "NIL_"; }

        NIL_Type() {
            width = "8";
            length = "1";
            selfType = NIL_;
        }
    };

    class ARRAY_Type : public Type {
    public:
        String toString() override { return fmt::format("ARRAY_({},{})", length, varType->toString()); }

        ARRAY_Type(const SharedPtr<ast::Type> varType, String width, String length)
                : Type(varType, width, length) { selfType = ARRAY_; }

        ARRAY_Type()
                : Type(std::make_shared<VAR_Type>(), "8", "1") { selfType = ARRAY_; }
    };

}

#endif //ROBIN_TYPE_H
