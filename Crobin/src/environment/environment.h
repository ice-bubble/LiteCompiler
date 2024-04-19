//
// Created by icelake on 24-4-19.
//

#ifndef CROBIN_ENVIRONMENT_H
#define CROBIN_ENVIRONMENT_H

#include "../token/token.h"


// 声明不完整的结构体
typedef struct SymbolTable SymbolTable;

// 定义完整的结构体
struct SymbolTable {
    SymbolTable *outer;
    TokenList tokenlist;
};

void initSymbolTable(SymbolTable *symboltable);

void writeSymbolTable(SymbolTable *symboltable, Token token);

void freeSymbolTable(SymbolTable *symboltable);


#endif //CROBIN_ENVIRONMENT_H
