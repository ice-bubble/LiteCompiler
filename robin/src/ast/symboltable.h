//
// Created by icelake on 24-5-29.
//

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
        SharedPtr<SymTab> outer = nullptr;
        size_t offset = 0;

        SymTab() = default;

        bool insert(const String &name, const SharedPtr<Type> &varType, String width) {
            if (varTab.find(name) != varTab.end()) {
                return false; // 插入失败，变量名已存在
            }

            auto thisVar = Variable(name, varType, width);
            offset += 8;
            varTab.insert(std::make_pair(name, thisVar));

            return true; // 插入成功
        }

        bool changeReturnType(String name, SharedPtr<Type> returnType) {
            auto thisVar = varTab.find(name);
            if (thisVar == varTab.end()) {
                return false;
            }
            thisVar->second.returnType=returnType->selfType;
            return true;
        }

        Variable *lookup(const String &name) {
            auto it = varTab.find(name);
            if (it != varTab.end()) return &(it->second);
            return nullptr;
        }

    private:
        Map<String, Variable> varTab;
    };
}

#endif //ROBIN_SYMBOLTABLE_H
