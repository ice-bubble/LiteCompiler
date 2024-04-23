//
// Created by icelake on 24-4-14.
//

#include "debug.h"
#include <stdio.h>

void printTokenList(TokenList *tokenlist) {
    for (int i = 0; i < tokenlist->count; i++) {
        printf("line %04d ", tokenlist->token[i].line);
        printf("< %s , '%.*s' >\n",
               getTokenStrings(tokenlist->token[i].type),
               tokenlist->token[i].length,
               tokenlist->token[i].start);
    }
}

void printSymbolTable(SymbolTable *symboltable) {
    printf("    |===symbolTable===|\n");
    printTokenList(&symboltable->tokenlist);
}