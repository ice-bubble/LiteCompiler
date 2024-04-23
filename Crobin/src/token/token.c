//
// Created by icelake on 24-4-18.
//

#include "token.h"
#include "../memory/memory.h"

const char *tokenStrings[] = {
        "LEFT_PAREN",
        "RIGHT_PAREN",
        "LEFT_BRACE",
        "RIGHT_BRACE",
        "LEFT_BRACKET",
        "RIGHT_BRACKET",
        "COMMA",
        "DOT",
        "MINUS",
        "PLUS",
        "SEMICOLON",
        "SLASH",
        "STAR",
        "MOD",

        "NOT_EQUAL",
        "EQUAL",
        "EQUAL_EQUAL",
        "GREATER",
        "GREATER_EQUAL",
        "LESS",
        "LESS_EQUAL",

        "IDENTIFIER",
        "STRING",
        "INT",
        "REAL",

        "AND",
        "BREAK",
        "CLASS",
        "CONTINUE",
        "DOUBLE",
        "ELSE",
        "FALSE",
        "FOR",
        "FUNCTION",
        "IF",
        "INTEGER",
        "NIL",
        "NOT",
        "OR",
        "PRINT",
        "RETURN",
        "SUPER",
        "THIS",
        "TRUE",
        "VAR",
        "WHILE",

        "ERROR",
        "EOF"
};

const char *getTokenStrings(int tokentype) {
    return tokenStrings[tokentype];
}

void initTokenList(TokenList *tokenlist) {
    tokenlist->count = 0;
    tokenlist->capacity = 0;
    tokenlist->token = NULL;
}

void writeTokenList(TokenList *tokenlist, Token token) {
    if (tokenlist->capacity < tokenlist->count + 1) {
        int oldCapacity = tokenlist->capacity;
        tokenlist->capacity = GROW_CAPACITY(oldCapacity);
        tokenlist->token = GROW_ARRAY(Token, tokenlist->token, oldCapacity, tokenlist->capacity);
    }
    tokenlist->token[tokenlist->count] = token;
    tokenlist->count++;

}

void freeTokenList(TokenList *tokenlist) {
    FREE_ARRAY(Token, tokenlist->token, tokenlist->capacity);
    initTokenList(tokenlist);
}
