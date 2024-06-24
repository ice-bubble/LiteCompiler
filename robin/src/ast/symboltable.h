#ifndef ROBIN_SYMBOLTABLE_H
#define ROBIN_SYMBOLTABLE_H

#include "../common.h"
#include "type.h"

namespace ast {

    class Variable {
    public:
        String name;
        SharedPtr<Type> varType;
        IdentifierType returnType;
        List<SharedPtr<Type>> params;
        size_t paramCount = 0;
        String width;
        Object value;

        Variable(String name, const SharedPtr<Type> &varType, String width)
                : name(std::move(name)), varType(varType), width(width) {
            returnType = varType->selfType == IdentifierType::FUNC_ ? returnType = IdentifierType::VAR_
                                                                    : returnType = varType->selfType;
        }

    };

    class SymTab {
    public:
        SymTab *outer = nullptr;
        size_t offset = 0;

        SymTab() = default;

        /**
         * @param name 变量名
         * @param varType 变量类型
         * @param width 变量总宽度
         * @brief 以输入的参数构造一个变量，将变量插入符号表
         * @return 插入成功返回1，否则返回0
         */
        bool insert(const String &name, const SharedPtr<Type> &varType, String width) {
            if (varTab.find(name) != varTab.end()) {
                return false; // 插入失败，变量名已存在
            }

            auto thisVar = Variable(name, varType, width);
            offset += 8;
            varTab.insert(std::make_pair(name, thisVar));

            return true; // 插入成功
        }

        /**
         * @param name 变量名
         * @brief 在符号表中查找变量，返回变量在表中的指针
         * @return 返回变量在表中的指针
         */
        Variable *lookup(const String &name) {
            auto it = varTab.find(name);
            if (it != varTab.end()) return &(it->second);
            if (outer == nullptr) return nullptr;
            return outer->lookup(name);
        }

        /**
         * @param name 函数名
         * @param returnType 函数返回类型
         * @brief 修改符号表中一个函数的返回类型
         * @return 修改成功返回1，否则返回0
         */
        bool changeReturnType(const String &name, SharedPtr<Type> returnType) {
            auto thisVar = lookup(name);
            if (thisVar == nullptr) return false;
            thisVar->returnType = returnType->selfType;
            return true;
        }

        /**
         * @param thisTab 当前符号表
         * @brief 建立一个新符号表，其外层为当前符号表
         * @return 返回新建立的符号表的指针
         */
        static SymTab *genNewSymTab(SymTab *thisTab) {
            if (thisTab == nullptr) return nullptr;
            auto newTab = new SymTab;
            newTab->outer = thisTab;
            return newTab;
        }

        /**
         * @param thisTab 当前符号表
         * @brief 丢弃当前符号表，返回外层符号表
         * @return 返回当前符号表的外层符号表的指针
         */
        static SymTab *throwThisSymTab(SymTab *thisTab) {
            if (thisTab == nullptr) return nullptr;
            SymTab *outerTab = thisTab->outer;
            delete thisTab;
            return outerTab;
        }

    private:
        ///< 真正的符号表
        Map<String, Variable> varTab;
    };
}

#endif //ROBIN_SYMBOLTABLE_H
