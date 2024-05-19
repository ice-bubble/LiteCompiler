cmake_minimum_required(VERSION 3.28)
project(robin)

set(CMAKE_CXX_STANDARD 17)

add_executable(robin main.cpp
        src/token/token.cpp
        src/token/token.h
        src/common.h
        src/lexer/lexer.h
        src/lexer/lexer.cpp
        src/error/error.cpp
        src/error/error.h
        src/debug/debug.h
        src/debug/debug.cpp
        src/ast/type.h
        src/ast/production.h
        src/parser/parser.h
        src/parser/parser.cpp
        src/parser/slrtable.cpp
        src/parser/reduce.cpp
        src/ast/symbol.h
        src/ast/initAst.cpp
)
