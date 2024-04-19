//
// Created by icelake on 24-4-19.
//
#include <string.h>
#include "environment.h"

void initSymbolTable(SymbolTable *symboltable) {
    symboltable->outer = NULL;
    initTokenList(&symboltable->tokenlist);
}

void writeSymbolTable(SymbolTable *symboltable, Token token) {
    for (int i = 0; i < symboltable->tokenlist.count; i++) {
        Token tokenInList = symboltable->tokenlist.token[i];
        if (token.length != tokenInList.length)
            continue;
        if (!strncmp(token.start, tokenInList.start, token.length))
            return;
    }
    writeTokenList(&symboltable->tokenlist, token);
}

void freeSymbolTable(SymbolTable *symboltable) {
    freeTokenList(&symboltable->tokenlist);
}